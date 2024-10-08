#include "PluginProcessor.h"
#include "PluginEditor.h"

static const std::vector<mrta::ParameterInfo> ParameterInfos
{
    { Param::ID::Frequency,     Param::Name::Frequency,   "Off", "On", true },
    { Param::ID::Structure,     Param::Name::Structure,     "", 1.f, 1.f, 10.f, 0.1f, 1.f },
    { Param::ID::Brightness,    Param::Name::Brightness, "Hz", 1000.f, 20.f, 20000.f, 1.f, 0.3f },
    { Param::ID::Damping,       Param::Name::Damping, "", 0.f, 0.f, 1.f, 0.001f, 1.f },
    { Param::ID::Position,      Param::Name::Position,      { "LPF12", "HPF12", "BPF12", "LPF24", "HPF24", "BPF24" }, 3 },
    // { Param::ID::PostGain,  Param::Name::PostGain,  "dB", 0.0f, -60.f, 12.f, 0.1f, 3.8018f },
};

//   STRUCTURE (0.0f, 0.9995f);
//   BRIGHTNESS (0.0f, 1.0f);
//   DAMPING, (0.0f, 1.0f);
//   POSITION (0.0f, 1.0f);
//  

MainProcessor::MainProcessor() :
    parameterManager(*this, ProjectInfo::projectName, ParameterInfos)
{
    parameterManager.registerParameterCallback(Param::ID::Frequency,
    [this] (float value, bool /*forced*/)
    {
        resonator.setFrequency(value);
    });

    parameterManager.registerParameterCallback(Param::ID::Structure,
    [this] (float value, bool /*forced*/)
    {
        resonator.setStructure(value);
    });

    parameterManager.registerParameterCallback(Param::ID::Brightness,
    [this] (float value, bool /*forced*/)
    {
        resonator.setBrightness(value);
    });

    parameterManager.registerParameterCallback(Param::ID::Damping,
    [this] (float value, bool /*forced*/)
    {
        resonator.setDamping(value);
    });

    parameterManager.registerParameterCallback(Param::ID::Position,
    [this] (float value, bool /*forced*/)
    {
        resonator.setPosition(value);
    });

    // parameterManager.registerParameterCallback(Param::ID::PostGain,
    // [this] (float value, bool forced)
    // {
    //     DBG(Param::Name::PostGain + ": " + juce::String { value });
    //     float dbValue { 0.f };
    //     if (value > -60.f)
    //         dbValue = std::pow(10.f, value * 0.05f);

    //     if (forced)
    //         outputGain.setCurrentAndTargetValue(dbValue);
    //     else
    //         outputGain.setTargetValue(dbValue);
    // });
}

MainProcessor::~MainProcessor()
{
}

void MainProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::uint32 numChannels { static_cast<juce::uint32>(std::max(getMainBusNumInputChannels(), getMainBusNumOutputChannels())) };
    // resonator.prepare({ sampleRate, static_cast<juce::uint32>(samplesPerBlock), numChannels });
    // outputGain.reset(sampleRate, 0.01f);
    parameterManager.updateParameters(true);
}

void MainProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& /*midiMessages*/)
{
    juce::ScopedNoDenormals noDenormals;
    parameterManager.updateParameters();

    {
        juce::dsp::AudioBlock<float> audioBlock(buffer.getArrayOfWritePointers(), buffer.getNumChannels(), buffer.getNumSamples());
        juce::dsp::ProcessContextReplacing<float> ctx(audioBlock);
        // filter.process(ctx);
    }

    // outputGain.applyGain(buffer, buffer.getNumSamples());
}

void MainProcessor::releaseResources()
{
    // filter.reset();
}

void MainProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    parameterManager.getStateInformation(destData);
}

void MainProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    parameterManager.setStateInformation(data, sizeInBytes);
}

juce::AudioProcessorEditor* MainProcessor::createEditor()
{
    return new MainProcessorEditor(*this);
}

//==============================================================================
const juce::String MainProcessor::getName() const { return JucePlugin_Name; }
bool MainProcessor::acceptsMidi() const { return false; }
bool MainProcessor::producesMidi() const { return false; }
bool MainProcessor::isMidiEffect() const { return false; }
double MainProcessor::getTailLengthSeconds() const { return 0.0; }
int MainProcessor::getNumPrograms() { return 1; }
int MainProcessor::getCurrentProgram() { return 0; }
void MainProcessor::setCurrentProgram (int) { }
const juce::String MainProcessor::getProgramName(int) { return {}; }
void MainProcessor::changeProgramName(int, const juce::String&) { }
bool MainProcessor::hasEditor() const { return true; }
//==============================================================================

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MainProcessor();
}
