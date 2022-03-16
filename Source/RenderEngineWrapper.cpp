#include "RenderEngineWrapper.h"

RenderEngineWrapper::RenderEngineWrapper(double sr, int bs) :
    RenderEngine(sr, bs)
{
}

/// @brief
// std::shared_ptr<OscillatorProcessor>
// RenderEngineWrapper::makeOscillatorProcessor(const std::string& name, float freq)
// {
//     return std::shared_ptr<OscillatorProcessor>{new OscillatorProcessor{ name, freq }};
// }

/// @brief
std::shared_ptr<PluginProcessorWrapper>
RenderEngineWrapper::makePluginProcessor(const std::string& name, const std::string& path)
{
    return std::shared_ptr<PluginProcessorWrapper>{new PluginProcessorWrapper{ name, mySampleRate, myBufferSize, path }};
}

/// @brief
// std::shared_ptr<PlaybackProcessor>
// RenderEngineWrapper::makePlaybackProcessor(const std::string& name, py::array data)
// {
//     return std::shared_ptr<PlaybackProcessor>{new PlaybackProcessor{ name, data }};
// }

#ifdef BUILD_DAWDREAMER_RUBBERBAND
/// @brief
std::shared_ptr<PlaybackWarpProcessor>
RenderEngineWrapper::makePlaybackWarpProcessor(const std::string& name, py::array data)
{
    return std::shared_ptr<PlaybackWarpProcessor>{new PlaybackWarpProcessor{ name, data, mySampleRate }};
}
#endif

// std::shared_ptr<FilterProcessor>
// RenderEngineWrapper::makeFilterProcessor(const std::string& name, const std::string& mode, float freq, float q, float gain) {

//     float validFreq = std::fmax(.0001f, freq);
//     float validQ = std::fmax(.0001f, q);
//     float validGain = std::fmax(.0001f, gain);

//     return std::shared_ptr<FilterProcessor>{new FilterProcessor{ name, mode, validFreq, validQ, validGain }};
// }

// std::shared_ptr<CompressorProcessor>
// RenderEngineWrapper::makeCompressorProcessor(const std::string& name, float threshold = 0.f, float ratio = 2.f, float attack = 2.f, float release = 50.f) {

//     // ratio must be >= 1.0
//     // attack and release are in milliseconds
//     float validRatio = std::fmax(1.0f, ratio);
//     float validAttack = std::fmax(0.f, attack);
//     float validRelease = std::fmax(0.f, release);
//     return std::shared_ptr<CompressorProcessor>{new CompressorProcessor{ name, threshold, validRatio, validAttack, validRelease }};
// }


// std::shared_ptr<AddProcessor>
// RenderEngineWrapper::makeAddProcessor(const std::string& name, std::vector<float> gainLevels) {
//     return std::shared_ptr<AddProcessor>{new AddProcessor{ name, gainLevels }};
// }


// std::shared_ptr<ReverbProcessor>
// RenderEngineWrapper::makeReverbProcessor(const std::string& name, float roomSize = 0.5f, float damping = 0.5f, float wetLevel = 0.33f,
//     float dryLevel = 0.4f, float width = 1.0f) {
//     return std::shared_ptr<ReverbProcessor>{new ReverbProcessor{ name, roomSize, damping, wetLevel, dryLevel, width }};
// }

// std::shared_ptr<PannerProcessor>
// RenderEngineWrapper::makePannerProcessor(const std::string& name, std::string& rule, float pan) {

//     float safeVal = std::fmax(-1.f, pan);
//     safeVal = std::fmin(1.f, pan);

//     return std::shared_ptr<PannerProcessor>{new PannerProcessor{ name, rule, safeVal }};
// }

// std::shared_ptr<DelayProcessor>
// RenderEngineWrapper::makeDelayProcessor(const std::string& name, std::string& rule, float delay, float wet) {
//     float safeDelay = std::fmax(0.f, delay);

//     float safeWet = std::fmin(1.f, std::fmax(0.f, wet));

//     return std::shared_ptr<DelayProcessor>{new DelayProcessor{ name, rule, safeDelay, safeWet }};
// }

/// @brief
// std::shared_ptr<SamplerProcessor>
// RenderEngineWrapper::makeSamplerProcessor(const std::string& name, py::array data)
// {
//     return std::shared_ptr<SamplerProcessor>{new SamplerProcessor{ name, data, mySampleRate, myBufferSize }};
// }

#ifdef BUILD_DAWDREAMER_FAUST
std::shared_ptr<FaustProcessor>
RenderEngineWrapper::makeFaustProcessor(const std::string& name)
{
    return std::shared_ptr<FaustProcessor>{new FaustProcessor{ name, mySampleRate, myBufferSize }};
}
#endif

bool
RenderEngineWrapper::loadGraphWrapper(py::object dagObj) {

    if (!py::isinstance<py::list>(dagObj)) {
        return false;
    }

    DAG* buildingDag = new DAG();

    for (py::handle theTuple : dagObj) {  // iterators!

        if (!py::isinstance<py::tuple>(theTuple) && !py::isinstance<py::list>(theTuple)) {
            std::cout << "Error: load_graph. Received graph that is not a list." << std::endl;
            return false;
        }
        py::list castedTuple = theTuple.cast<py::list>();

        if (castedTuple.size() != 2) {
            std::cout << "Error: load_graph. Each tuple in the graph must be size 2." << std::endl;
            return false;
        }

        //if (!py::isinstance<ProcessorBase*>(castedTuple[0])) {
        // std::cout << "Error: load_graph. First argument in tuple wasn't a Processor object." << std::endl;
        //    return false;
        //}
        if (!py::isinstance<py::list>(castedTuple[1])) {
            std::cout << "Error: load_graph. Something was wrong with the list of inputs." << std::endl;
            return false;
        }

        py::list listOfStrings = castedTuple[1].cast<py::list>();

        std::vector<std::string> inputs;

        for (py::handle potentialString : listOfStrings) {
            if (!py::isinstance<py::str>(potentialString)) {
                std::cout << "Error: load_graph. Something was wrong with the list of inputs." << std::endl;
                return false;
            }

            inputs.push_back(potentialString.cast<std::string>());
        }

        DAGNode dagNode;
        try {
            dagNode.processorBase = castedTuple[0].cast<ProcessorBase*>();
        }
        catch (std::exception&) {
            std::cout << "Error: load_graph. First argument in tuple wasn't a Processor object." << std::endl;
            return false;
        }

        dagNode.inputs = inputs;

        buildingDag->nodes.push_back(dagNode);
    }

    return RenderEngine::loadGraph(*buildingDag);
}

// lxd
py::array_t<float>
RenderEngineWrapper::getAudioFramesFromProcessor(const ProcessorBase* processor)
{
    const auto& record_buffer = processor->recordBuffer();

    size_t num_channels = record_buffer.getNumChannels();
    size_t num_samples = record_buffer.getNumSamples();

    py::array_t<float, py::array::c_style> arr({(int)num_channels, (int)num_samples});

    auto ra = arr.mutable_unchecked();

    for (size_t i = 0; i < num_channels; i++)
    {
        for (size_t j = 0; j < num_samples; j++)
        {
            ra(i, j) = record_buffer.getSample(i, j);
        }
    }

    return arr;
}

py::array_t<float>
RenderEngineWrapper::getAutomationNumpy(std::string pluginName, std::string parameterName)
{
    auto processor = getProcessorByName(pluginName);
    std::vector<float> data = processor->getAutomation(parameterName);

    py::array_t<float, py::array::c_style> arr({(int)data.size()});

    auto ra = arr.mutable_unchecked();

    for (size_t i = 0; i < data.size(); i++)
    {
        ra(i) = data[i];
    }

    return arr;
}

bool RenderEngineWrapper::setAutomation(std::string pluginName, std::string parameterName, py::array_t<float> input)
{
    try
    {
        auto processor = getProcessorByName(pluginName);
        auto parameter = (AutomateParameterFloat *)processor->parameters().getParameter(parameterName); // todo: why do we have to cast to AutomateParameterFloat instead of AutomateParameter

        if (parameter)
        {
            float* input_ptr = (float*)input.data();
            auto tmp_automation = std::vector<float>(input.shape(0), 0.f);

            for (int x = 0; x < input.shape(0); x++) {
                tmp_automation[x] = *(input_ptr++);
            }
            return parameter->setAutomation(tmp_automation);
        }
        else
        {
            std::cerr << "Failed to find parameter: " << parameterName << std::endl;
            return false;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << "Failed to set '" << parameterName << "' automation: " << e.what() << std::endl;
        return false;
    }

    return true;
}

py::array_t<float>
RenderEngineWrapper::getAudioFrames()
{
    auto& main_processor_graph = mainProcessorGraph();
    auto nodes = main_processor_graph->getNodes();
    
    if (nodes.size() == 0) {
        // NB: For some reason we can't initialize the array as shape (2, 0)
        py::array_t<float, py::array::c_style> arr({ 2, 1 });
        arr.resize({ 2, 0 });

        return arr;
    }
    
    auto node = nodes.getLast();
    
    auto processor = dynamic_cast<ProcessorBase*>(node->getProcessor());
    if (processor) {
        auto uniqueName = processor->getUniqueName();
        return getAudioFramesForName(uniqueName);
    }

    // NB: For some reason we can't initialize the array as shape (2, 0)
    py::array_t<float, py::array::c_style> arr({ 2, 1 });
    arr.resize({ 2, 0 });

    return arr;
}

ProcessorBase* RenderEngineWrapper::getProcessorByName(std::string& name) {
    auto& main_processor_graph = mainProcessorGraph();
    auto nodes = main_processor_graph->getNodes();
    for (auto& node : nodes) {
        auto processor = dynamic_cast<ProcessorBase*>(node->getProcessor());
        if (processor) {
            if (std::strcmp(processor->getUniqueName().c_str(), name.c_str()) == 0) {
                return processor;
            }
        }
    }
    return nullptr;
}

py::array_t<float>
RenderEngineWrapper::getAudioFramesForName(std::string& name)
{
    auto processor = getProcessorByName(name);
    if (processor) {
        return getAudioFramesFromProcessor(processor);
    }
    // lxd
    std::cerr << "processor name " << name  << " not found, return empty" << std::endl;

    // NB: For some reason we can't initialize the array as shape (2, 0)
    py::array_t<float, py::array::c_style> arr({ 2, 1 });
    arr.resize({ 2, 0 });

    return arr;
}
