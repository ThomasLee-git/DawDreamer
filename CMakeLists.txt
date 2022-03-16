# Generated on 2022-3-16 14:45:46 by version 0.9.0 of mulle-xcode-to-cmake
# Command line:
#    mulle-xcode-to-cmake -l c++ export DawDreamer.xcodeproj


cmake_minimum_required (VERSION 3.4)
project( "dawdreamer" CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# ###
# Build for mulle-objc (https://mulle-objc.github.io/):
#
#    mulle-sde init -m foundation/objc-porter executable
#    mulle-sde craft
#
# [mulle-clang >= 8.0.0.0 and mulle-objc >= 0.15 required]
#

if( NOT DEPENDENCY_DIR)
   set( DEPENDENCY_DIR "$ENV{DEPENDENCY_DIR}")
endif()
if( NOT DEPENDENCY_DIR)
   set( DEPENDENCY_DIR "${PROJECT_SOURCE_DIR}/dependency")
endif()
if( EXISTS "${DEPENDENCY_DIR}")
   if( NOT ADDICTION_DIR)
      get_filename_component( ADDICTION_DIR "${DEPENDENCY_DIR}" DIRECTORY)
      set( ADDICTION_DIR "${ADDICTION_DIR}/addiction")
   endif()
   set( CMAKE_FIND_FRAMEWORK "LAST")
   include_directories( BEFORE SYSTEM
      ${DEPENDENCY_DIR}/include
      ${ADDICTION_DIR}/include
   )
   set( CMAKE_FRAMEWORK_PATH
      ${DEPENDENCY_DIR}/Frameworks
      ${ADDICTION_DIR}/Frameworks
      ${CMAKE_FRAMEWORK_PATH}
   )
   set( CMAKE_LIBRARY_PATH
      ${DEPENDENCY_DIR}/lib
      ${ADDICTION_DIR}/lib
      ${CMAKE_LIBRARY_PATH}
   )
   set( SKIP_FIND_FOUNDATION_LIBRARY ON)
   execute_process( COMMAND mulle-sde stash-dir
                    OUTPUT_VARIABLE MULLE_SOURCETREE_STASH_DIR)
   string( STRIP "${MULLE_SOURCETREE_STASH_DIR}" MULLE_SOURCETREE_STASH_DIR)
   execute_process( COMMAND mulle-sde linkorder --stash-dir "${MULLE_SOURCETREE_STASH_DIR}" --startup --simplify --output-format cmake
                    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}"
                    OUTPUT_VARIABLE MULLE_SDE_LINKER_FLAGS
                    RESULT_VARIABLE RVAL)
   if( NOT ${RVAL} EQUAL 0)
      message( FATAL_ERROR "Failed to procure linkorder from mulle-sde. Old version ?")
   endif()
   message( STATUS "MULLE_SDE_LINKER_FLAGS=\"${MULLE_SDE_LINKER_FLAGS}\"")
else()
   message( STATUS "Not a mulle-sde build (\"${DEPENDENCY_DIR}\" does not exist)")
endif()


#
# Platform specific definitions
#

if( APPLE)
   # # CMAKE_OSX_SYSROOT must be set for CMAKE_OSX_DEPLOYMENT_TARGET (cmake bug)
   # if( NOT CMAKE_OSX_SYSROOT)
   #    set( CMAKE_OSX_SYSROOT "/" CACHE STRING "SDK for OSX" FORCE)   # means current OS X
   # endif()
   #
   # # baseline set to 10.6 for rpath
   # if( NOT CMAKE_OSX_DEPLOYMENT_TARGET)
   #   set(CMAKE_OSX_DEPLOYMENT_TARGET "10.6" CACHE STRING "Deployment target for OSX" FORCE)
   # endif()

   set( CMAKE_POSITION_INDEPENDENT_CODE FALSE)
   set( CMAKE_INSTALL_RPATH "@rpath/../lib")

   set( BEGIN_ALL_LOAD "-all_load")
   set( END_ALL_LOAD)
else()
   set( CMAKE_POSITION_INDEPENDENT_CODE TRUE)

   if( WIN32)
   # windows
   else()
   # linux / gcc
      set( BEGIN_ALL_LOAD "-Wl,--whole-archive")
      set( END_ALL_LOAD "-Wl,--no-whole-archive")
      set( CMAKE_INSTALL_RPATH "\$ORIGIN/../lib")
   endif()
endif()


##
## DawDreamer - Dynamic Library Files
##

# uncomment this for mulle-objc to search libraries first
# set( CMAKE_FIND_FRAMEWORK "LAST")

# set( GLOBAL_RESOURCES
# RecentFilesMenuTemplate.nib
# )

# set( RESOURCES
#    ${GLOBAL_RESOURCES}
# )

include_directories(/Users/thomas/miniconda3/envs/daw/include/python3.10)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/modules)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/modules/juce_audio_processors/format_types/VST3_SDK)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/JUCE/modules/juce_audio_processors/format_types/VST3_SDK)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/pybind11/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/faust/architecture)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/faust/compiler)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/faust/compiler/utils)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libsamplerate/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/libsamplerate/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/rubberband)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/kissfft)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/portable_endian/include)


set( SOURCES
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/BinaryData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_audio_basics.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_audio_devices.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_audio_formats.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_audio_processors.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_core.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_cryptography.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_data_structures.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_dsp.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_events.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_graphics.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_gui_basics.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_gui_extra.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_opengl.mm
${CMAKE_CURRENT_SOURCE_DIR}/JuceLibraryCode/include_juce_video.mm
# ${CMAKE_CURRENT_SOURCE_DIR}/Source/FaustProcessor.cpp
# ${CMAKE_CURRENT_SOURCE_DIR}/Source/FilterProcessor.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/PluginProcessor.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/PluginProcessorWrapper.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/ProcessorBase.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/RenderEngine.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/RenderEngineWrapper.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/Sampler/Source/DataModels/DataModel.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/Sampler/Source/DataModels/MPESettingsDataModel.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/Sampler/Source/SamplerAudioProcessor.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/Sampler/Source/SamplerAudioProcessorEditor.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/custom_pybind_wrappers.cpp
${CMAKE_CURRENT_SOURCE_DIR}/Source/source.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/RubberBandStretcher.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/StretchCalculator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/StretcherChannelData.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/StretcherImpl.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/StretcherProcess.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/audiocurves/CompoundAudioCurve.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/audiocurves/ConstantAudioCurve.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/audiocurves/HighFrequencyAudioCurve.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/audiocurves/PercussiveAudioCurve.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/audiocurves/SilentAudioCurve.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/audiocurves/SpectralDifferenceAudioCurve.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/base/Profiler.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/dsp/AudioCurveCalculator.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/dsp/FFT.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/dsp/Resampler.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/kissfft/kiss_fft.c
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/kissfft/kiss_fftr.c
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/rubberband-c.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/speex/resample.c
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/system/Allocators.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/system/Thread.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/system/VectorOpsComplex.cpp
${CMAKE_CURRENT_SOURCE_DIR}/thirdparty/rubberband/src/system/sysutils.cpp
)

set( STATIC_DEPENDENCIES
)

if( NOT SKIP_FIND_AVFOUNDATION_LIBRARY)
   find_library( AVFOUNDATION_LIBRARY AVFoundation)
   message( STATUS "AVFOUNDATION_LIBRARY is ${AVFOUNDATION_LIBRARY}")
endif()
if( NOT SKIP_FIND_AVKIT_LIBRARY)
   find_library( AVKIT_LIBRARY AVKit)
   message( STATUS "AVKIT_LIBRARY is ${AVKIT_LIBRARY}")
endif()
if( NOT SKIP_FIND_ACCELERATE_LIBRARY)
   find_library( ACCELERATE_LIBRARY Accelerate)
   message( STATUS "ACCELERATE_LIBRARY is ${ACCELERATE_LIBRARY}")
endif()
if( NOT SKIP_FIND_AUDIO_TOOLBOX_LIBRARY)
   find_library( AUDIO_TOOLBOX_LIBRARY AudioToolbox)
   message( STATUS "AUDIO_TOOLBOX_LIBRARY is ${AUDIO_TOOLBOX_LIBRARY}")
endif()
if( NOT SKIP_FIND_AUDIO_UNIT_LIBRARY)
   find_library( AUDIO_UNIT_LIBRARY AudioUnit)
   message( STATUS "AUDIO_UNIT_LIBRARY is ${AUDIO_UNIT_LIBRARY}")
endif()
if( NOT SKIP_FIND_CARBON_LIBRARY)
   find_library( CARBON_LIBRARY Carbon)
   message( STATUS "CARBON_LIBRARY is ${CARBON_LIBRARY}")
endif()
if( NOT SKIP_FIND_COCOA_LIBRARY)
   find_library( COCOA_LIBRARY Cocoa)
   message( STATUS "COCOA_LIBRARY is ${COCOA_LIBRARY}")
endif()
if( NOT SKIP_FIND_CORE_AUDIO_LIBRARY)
   find_library( CORE_AUDIO_LIBRARY CoreAudio)
   message( STATUS "CORE_AUDIO_LIBRARY is ${CORE_AUDIO_LIBRARY}")
endif()
if( NOT SKIP_FIND_CORE_AUDIO_KIT_LIBRARY)
   find_library( CORE_AUDIO_KIT_LIBRARY CoreAudioKit)
   message( STATUS "CORE_AUDIO_KIT_LIBRARY is ${CORE_AUDIO_KIT_LIBRARY}")
endif()
if( NOT SKIP_FIND_CORE_MIDI_LIBRARY)
   find_library( CORE_MIDI_LIBRARY CoreMIDI)
   message( STATUS "CORE_MIDI_LIBRARY is ${CORE_MIDI_LIBRARY}")
endif()
if( NOT SKIP_FIND_CORE_MEDIA_LIBRARY)
   find_library( CORE_MEDIA_LIBRARY CoreMedia)
   message( STATUS "CORE_MEDIA_LIBRARY is ${CORE_MEDIA_LIBRARY}")
endif()
if( NOT SKIP_FIND_FOUNDATION_LIBRARY)
   find_library( FOUNDATION_LIBRARY Foundation)
   message( STATUS "FOUNDATION_LIBRARY is ${FOUNDATION_LIBRARY}")
endif()
if( NOT SKIP_FIND_IOKIT_LIBRARY)
   find_library( IOKIT_LIBRARY IOKit)
   message( STATUS "IOKIT_LIBRARY is ${IOKIT_LIBRARY}")
endif()
if( NOT SKIP_FIND_OPEN_GL_LIBRARY)
   find_library( OPEN_GL_LIBRARY OpenGL)
   message( STATUS "OPEN_GL_LIBRARY is ${OPEN_GL_LIBRARY}")
endif()
if( NOT SKIP_FIND_QUARTZ_CORE_LIBRARY)
   find_library( QUARTZ_CORE_LIBRARY QuartzCore)
   message( STATUS "QUARTZ_CORE_LIBRARY is ${QUARTZ_CORE_LIBRARY}")
endif()
if( NOT SKIP_FIND_WEB_KIT_LIBRARY)
   find_library( WEB_KIT_LIBRARY WebKit)
   message( STATUS "WEB_KIT_LIBRARY is ${WEB_KIT_LIBRARY}")
endif()

set( DEPENDENCIES
${ACCELERATE_LIBRARY}
${AUDIO_TOOLBOX_LIBRARY}
${AUDIO_UNIT_LIBRARY}
${AVFOUNDATION_LIBRARY}
${AVKIT_LIBRARY}
${CARBON_LIBRARY}
${COCOA_LIBRARY}
${CORE_AUDIO_LIBRARY}
${CORE_AUDIO_KIT_LIBRARY}
${CORE_MEDIA_LIBRARY}
${CORE_MIDI_LIBRARY}
${FOUNDATION_LIBRARY}
${IOKIT_LIBRARY}
${OPEN_GL_LIBRARY}
${QUARTZ_CORE_LIBRARY}
${WEB_KIT_LIBRARY}
)


##
## DawDreamer - Dynamic Library
##

add_library(dawdreamer SHARED
${SOURCES}
${PUBLIC_HEADERS}
${PROJECT_HEADERS}
${PRIVATE_HEADERS}
${RESOURCES}
)

target_compile_options(dawdreamer PUBLIC -fPIC)

target_compile_definitions(dawdreamer PUBLIC DEBUG=1 _DEBUG=1 SAMPLER_SKIP_UI HAVE_LIBSAMPLERATE HAVE_VDSP USE_PTHREADS JucePlugin_Build_VST=0 JucePlugin_Build_VST3=0 JucePlugin_Build_AU=0 JucePlugin_Build_AUv3=0 JucePlugin_Build_RTAS=0 JucePlugin_Build_AAX=0 JucePlugin_Build_Standalone=0 JucePlugin_Build_Unity=0)

target_link_directories(dawdreamer PUBLIC /Users/thomas/miniconda3/envs/daw/lib)
target_link_directories(dawdreamer PUBLIC /Users/thomas/git/DawDreamer/thirdparty/libsamplerate/build_release/src)
target_link_directories(dawdreamer PUBLIC /Volumes/ramdisk/Faust-2.37.3/lib)

message("lxd: ${BEGIN_ALL_LOAD}")
message("lxd: ${STATIC_DEPENDENCIES}")
message("lxd: ${END_ALL_LOAD}")
message("lxd: ${DEPENDENCIES}")
message("lxd: ${MULLE_SDE_LINKER_FLAGS}")

target_link_libraries( dawdreamer
${BEGIN_ALL_LOAD}
${STATIC_DEPENDENCIES}
${END_ALL_LOAD}
${DEPENDENCIES}
${MULLE_SDE_LINKER_FLAGS}
   samplerate
   faust
)

target_link_options(dawdreamer PUBLIC
"LINKER:-undefined,dynamic_lookup")

# install( TARGETS dawdreamer DESTINATION "lib")
# install( FILES ${PUBLIC_HEADERS} DESTINATION "include/DawDreamer---Dynamic-Library")
