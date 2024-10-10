// DAW to MQTT Bridge plugin
// MQTT bridge that sends MQTT data on certain DAW events
// https://github.com/iUltimateLP

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

// Main JUCE editor class (responsible for rendering the GUI)
// This inherits the juce::Timer class to update this GUI on an interval (not really the fine english way but it's okay for this type of plugin)
class DAWMQTTBridgeAudioProcessorEditor : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    // Constructor and destructor
    DAWMQTTBridgeAudioProcessorEditor(DAWMQTTBridgeAudioProcessor&);
    ~DAWMQTTBridgeAudioProcessorEditor() override;

    // juce::AudioProcessorEditor interface
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    // juce::Timer interface
    void timerCallback() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DAWMQTTBridgeAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DAWMQTTBridgeAudioProcessorEditor)
};
