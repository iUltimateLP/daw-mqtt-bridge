// DAW to MQTT Bridge plugin
// MQTT bridge that sends MQTT data on certain DAW events
// https://github.com/iUltimateLP

#include "PluginProcessor.h"
#include "PluginEditor.h"

// GUI update interval (in milliseconds)
static const int GUIUpdateInterval = 10.0f;

DAWMQTTBridgeAudioProcessorEditor::DAWMQTTBridgeAudioProcessorEditor(DAWMQTTBridgeAudioProcessor& p)
    : AudioProcessorEditor(&p), audioProcessor(p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);

    // Start a timer for the GUI update interval
    startTimer(GUIUpdateInterval);
}

DAWMQTTBridgeAudioProcessorEditor::~DAWMQTTBridgeAudioProcessorEditor()
{

}

void DAWMQTTBridgeAudioProcessorEditor::paint(juce::Graphics& g)
{
    // Fill background
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    // Set foreground text settings
    g.setColour(juce::Colours::white);
    g.setFont(juce::FontOptions(15.0f));
    
    g.drawFittedText("DAW to MQTT Bridge", getLocalBounds(), juce::Justification::centredTop, 1);
    
    // Cast the audio processor to our own instance so we can read our info
    if (DAWMQTTBridgeAudioProcessor* Processor = dynamic_cast<DAWMQTTBridgeAudioProcessor*>(getAudioProcessor()))
    {
        // Get the cached position info
        juce::AudioPlayHead::PositionInfo positionInfo = Processor->getCachedPositionInfo();

        // Format a string with the position info
        juce::String str;
        str << "Time: ";
        str <<(positionInfo.getTimeSignature().hasValue() ? positionInfo.getTimeSignature()->numerator : 0);
        str << "/";
        str <<(positionInfo.getTimeSignature().hasValue() ? positionInfo.getTimeSignature()->denominator : 0);
        str << " PPQ: ";
        str <<(positionInfo.getPpqPosition().hasValue() ? *positionInfo.getPpqPosition() : 0);
        str << " Seconds: ";
        str <<(positionInfo.getTimeInSeconds().hasValue() ? *positionInfo.getTimeInSeconds() : 0);
        str << " Is Playing? ";
        str <<(positionInfo.getIsPlaying() ? "Yes" : "No");
        str << " Is Recording? ";
        str <<(positionInfo.getIsRecording() ? "Yes" : "No");
        
        g.drawFittedText(str, getLocalBounds(), juce::Justification::centred, 1);    
    }
    else
    {
        g.drawFittedText("Invalid processor", getLocalBounds(), juce::Justification::centred, 1);
    }
}

void DAWMQTTBridgeAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor.
}

void DAWMQTTBridgeAudioProcessorEditor::timerCallback()
{
    // When the timer elapses, force a GUI repaint
    repaint();
}
