#pragma once

#include <random>
#include <array>
#include <iomanip>
#include <sstream>
#include <string>

#include "AllProcessors.h"
#include "ProcessorBase.h"

class DAGNode {
public:
    ProcessorBase* processorBase;
    std::vector<std::string> inputs;
};

class DAG {
public:
    std::vector<DAGNode> nodes;
};

class RenderEngine : AudioPlayHead
{
public:
    RenderEngine(double sr, int bs);
    ~RenderEngine();
    // RenderEngine(const RenderEngine&) = delete;

    bool loadGraph(DAG dagNodes);
    
    bool render (const double renderLength);

    void setBPM(double bpm);

    bool getCurrentPosition(CurrentPositionInfo& result) override;
    bool canControlTransport() override;
    void transportPlay(bool shouldStartPlaying) override;
    void transportRecord(bool shouldStartRecording) override;
    void transportRewind() override;
    inline std::unique_ptr<juce::AudioProcessorGraph>& mainProcessorGraph() {return myMainProcessorGraph;}
    const juce::AudioSampleBuffer& getAudioFromProcessor(const ProcessorBase* processor);
    const juce::AudioSampleBuffer& getAudio();

protected:

    double mySampleRate;
    int myBufferSize;
    double myBPM = 120.;
    std::unordered_map<std::string, int> m_UniqueNameToSlotIndex;
    std::unordered_map<std::string, std::vector<std::string>> m_UniqueNameToInputs;
    
    bool connectGraph();

private:

    std::unique_ptr<juce::AudioProcessorGraph> myMainProcessorGraph;
    juce::ReferenceCountedArray<juce::AudioProcessorGraph::Node> slots;

    CurrentPositionInfo myCurrentPositionInfo;
};
