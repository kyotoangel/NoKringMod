/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================

NoKringModAudioProcessorEditor::NoKringModAudioProcessorEditor (NoKringModAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // config slider
    DepthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    DepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(DepthSlider);
    
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
                                                                                             audioProcessor.treeState, "depth", DepthSlider
                                                                                             );
    // --------------------------
    addAndMakeVisible(audioProcessor.mainWaveViewer);
    audioProcessor.mainWaveViewer.setColours(bg_color, juce::Colours::white);
    setSize (400, 200);
}

NoKringModAudioProcessorEditor::~NoKringModAudioProcessorEditor()
{
}

//==============================================================================
void NoKringModAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (bg_color);
}

void NoKringModAudioProcessorEditor::resized()
{
    // On place le slider au centre (X, Y, Largeur, Hauteur)
    // Pour l'instant on le met manuellement, plus tard on utilisera tes coordonnées Figma
    DepthSlider.setBounds (150, 100, 100, 120);
    audioProcessor.mainWaveViewer.setBounds(0, 0, 400, 100);
}
