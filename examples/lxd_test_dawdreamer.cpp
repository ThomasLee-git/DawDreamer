#include "PluginProcessor.h"
#include "RenderEngine.h"

#include <chrono>
#include <memory>
#include <string>
#include <thread>

bool save_wav(const std::string &wav_path,
              const juce::AudioSampleBuffer &buffer) {

  juce::File file(wav_path);
  file.deleteFile();

  juce::WavAudioFormat format;
  std::unique_ptr<juce::AudioFormatWriter> writer;

  writer.reset(format.createWriterFor(new juce::FileOutputStream(file), 44100,
                                      buffer.getNumChannels(), 24, {}, 0));

  if (writer != nullptr) {
    writer->writeFromAudioSampleBuffer(buffer, 0, buffer.getNumSamples());
    return true;
  } else {
    std::cerr << "failed saving wav file at " << wav_path << std::endl;
    return false;
  }
}

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "usage: lxd_test_dawdreamer midi_path fxp_path wav_path";
    return -1;
  }
  using namespace std::chrono_literals;
  const double time_to_render = 20.0;
  const double sample_rate = 44100;
  const int block_buffer_size = 512;
  const std::string midi_path = argv[1];
  const std::string plugin_name = "vst";
  const std::string plugin_path = "/Library/Audio/Plug-Ins/VST/LABS.vst";
  const std::string preset_path = argv[2];
  const std::string wav_path = argv[3];

  // make plugin processor
  auto vst_plugin = std::make_unique<PluginProcessor>(
      plugin_name, sample_rate, block_buffer_size, plugin_path);
  // load preset
  if (!vst_plugin->loadPreset(preset_path)) {
    std::cerr << "failed loading preset " << preset_path << std::endl;
    return -1;
  }
  // add sleep here
  std::this_thread::sleep_for(100ms);
  // load midi
  if (!vst_plugin->loadMidi(midi_path)) {
    std::cerr << "faild loading midi " << midi_path << std::endl;
    return -2;
  }
  // wrap plugin in dag_node
  DAGNode node;
  node.processorBase = dynamic_cast<ProcessorBase *>(vst_plugin.get());
  // make render engine
  auto render_engine =
      std::make_unique<RenderEngine>(sample_rate, block_buffer_size);
  // make plugin dag
  auto plugin_dag = std::make_unique<DAG>();
  plugin_dag->nodes.clear();
  plugin_dag->nodes.push_back(node);
  // load graph
  render_engine->loadGraph(*plugin_dag);
  // render
  if (!render_engine->render(time_to_render)) {
    std::cerr << "failed rendering audio" << std::endl;
    return -3;
  }
  // get audio
  const auto &audio = render_engine->getAudio();
  // save
  if (save_wav(wav_path, audio)) {
    return 0;
  } else {
    return -4;
  }
}