#include "PluginProcessorWrapper.h"


PluginProcessorWrapper::PluginProcessorWrapper(std::string newUniqueName, double sampleRate, int samplesPerBlock, std::string path) :
    PluginProcessor(newUniqueName, sampleRate, samplesPerBlock, path)
{
}

// void
// PluginProcessorWrapper::wrapperSetPatch(py::list listOfTuples)
// {
//     PluginPatch patch = customBoost::listOfTuplesToPluginPatch(listOfTuples);
//     PluginProcessor::setPatch(patch);
// }

// py::list
// PluginProcessorWrapper::wrapperGetPatch()
// {
//     return customBoost::pluginPatchToListOfTuples(PluginProcessor::getPatch());
// }

float
PluginProcessorWrapper::wrapperGetParameter(int parameterIndex)
{
    if (!myPlugin) {
        std::cout << "Please load the plugin first!" << std::endl;
        return 0.;
    }

    if (parameterIndex >= myPlugin->AudioProcessor::getNumParameters()) {
        std::cout << "Parameter not found for index: " << parameterIndex << std::endl;
        return 0.;
    }

    return ProcessorBase::getAutomationVal(std::to_string(parameterIndex), 0);
}

std::string
PluginProcessorWrapper::wrapperGetParameterName(int parameter)
{
    return myPlugin->getParameterName(parameter).toStdString();
}

bool
PluginProcessorWrapper::wrapperSetParameter(int parameter, float value)
{
    if (!myPlugin) {
        std::cout << "Please load the plugin first!" << std::endl;
        return false;
    }

    std::string paramID = std::to_string(parameter);

    return ProcessorBase::setAutomationVal(paramID, value);
}

// bool
// PluginProcessorWrapper::wrapperSetAutomation(int parameterIndex, py::array input) {
//     return PluginProcessorWrapper::setAutomation(std::to_string(parameterIndex), input);
// }

int
PluginProcessorWrapper::wrapperGetPluginParameterSize()
{
    return int(PluginProcessor::getPluginParameterSize());
}

// py::list
// PluginProcessorWrapper::getPluginParametersDescription()
// {
//     py::list myList;

//     if (myPlugin != nullptr) {

//         //get the parameters as an AudioProcessorParameter array
//         const Array<AudioProcessorParameter*>& processorParams = myPlugin->getParameters();
//         for (int i = 0; i < myPlugin->AudioProcessor::getNumParameters(); i++) {

//             int maximumStringLength = 64;

//             std::string theName = (processorParams[i])->getName(maximumStringLength).toStdString();
//             std::string currentText = processorParams[i]->getText(processorParams[i]->getValue(), maximumStringLength).toStdString();
//             std::string label = processorParams[i]->getLabel().toStdString();

//             py::dict myDictionary;
//             myDictionary["index"] = i;
//             myDictionary["name"] = theName;
//             myDictionary["numSteps"] = processorParams[i]->getNumSteps();
//             myDictionary["isDiscrete"] = processorParams[i]->isDiscrete();
//             myDictionary["label"] = label;
//             myDictionary["text"] = currentText;

//             myList.append(myDictionary);
//         }
//     }
//     else
//     {
//         std::cout << "Please load the plugin first!" << std::endl;
//     }

//     return myList;
// }
