#pragma once

// #include "custom_pybind_wrappers.h"
#include "PluginProcessor.h"

class PluginProcessorWrapper : public PluginProcessor
{
public:

    PluginProcessorWrapper(std::string newUniqueName, double sampleRate, int samplesPerBlock, std::string path);

    // void wrapperSetPatch(py::list listOfTuples);

    // py::list wrapperGetPatch();

    float wrapperGetParameter(int parameterIndex);

    std::string wrapperGetParameterName(int parameter);

    bool wrapperSetParameter(int parameter, float value);

    // bool wrapperSetAutomation(int parameterIndex, py::array input);

    int wrapperGetPluginParameterSize();

    // py::list getPluginParametersDescription();

};
