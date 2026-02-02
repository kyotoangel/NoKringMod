/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
	
//==============================================================================
/**
*/
class NoKringModAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    NoKringModAudioProcessorEditor (NoKringModAudioProcessor&);
    ~NoKringModAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    NoKringModAudioProcessor& audioProcessor;
    juce::Slider DepthSlider;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> depthAttachment;
    juce::Colour bg_color = juce::Colours::pink;
    juce::Image logoImage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (NoKringModAudioProcessorEditor)
};
