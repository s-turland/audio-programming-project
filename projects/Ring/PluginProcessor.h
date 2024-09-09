#pragma once

#include <JuceHeader.h>
#include "Resonator.h"

namespace Param
{
    namespace ID
    {
        static const juce::String Frequency { "frequency" };
        static const juce::String Structure { "structure" };
        static const juce::String Brightness { "brightness" };
        static const juce::String Damping { "damping" };
        static const juce::String Position { "position" };
        // static const juce::String PostGain { "post_gain" };
    }

    namespace Name
    {
        static const juce::String Frequency { "Frequency" };
        static const juce::String Structure { "Structure" };
        static const juce::String Brightness { "Brightness" };
        static const juce::String Damping { "Damping" };
        static const juce::String Position { "Position" };
        // static const juce::String PostGain { "Post-Gain" };
    }
}

class MainProcessor : public juce::AudioProcessor
{
public:
    MainProcessor();
    ~MainProcessor() override;

    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

    mrta::ParameterManager& getParameterManager() { return parameterManager; }

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    const juce::String getName() const override;
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    //==============================================================================

private:
    mrta::ParameterManager parameterManager;

    DSP::Resonator resonator;

    // juce::dsp::LadderFilter<float> filter;
    // juce::SmoothedValue<float> outputGain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainProcessor)
};
