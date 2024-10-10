// DAW to MQTT Bridge plugin
// MQTT bridge that sends MQTT data on certain DAW events
// https://github.com/iUltimateLP

#pragma once

#include <JuceHeader.h>

// This is the JUCE AudioProcessor class that handles processing of the audio data
// This plugin doesn't really do any audio processing besides reading playhead info, so most of the functionality is unused
class DAWMQTTBridgeAudioProcessor  : public juce::AudioProcessor
{
public:
    // Constructor and destructor
    DAWMQTTBridgeAudioProcessor();
    ~DAWMQTTBridgeAudioProcessor() override;

public:
    // Returns the cached position info
    juce::AudioPlayHead::PositionInfo getCachedPositionInfo() const;
    
public:
    // juce::AudioProcessor interface
    void prepareToPlay(double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

#ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported(const BusesLayout& layouts) const override;
#endif

    void processBlock(juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram(int index) override;
    const juce::String getProgramName(int index) override;
    void changeProgramName(int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation(juce::MemoryBlock& destData) override;
    void setStateInformation(const void* data, int sizeInBytes) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DAWMQTTBridgeAudioProcessor)

    // This is a cached copy of the current position info so it can be read from the editor (which is not necessarily inside the processBlock() scope) 
    juce::AudioPlayHead::PositionInfo _cachedPositionInfo;
};
