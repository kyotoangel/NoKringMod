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
    // chargement de l'image de logo
    logoImage = juce::ImageCache::getFromMemory(BinaryData::logo_png, BinaryData::logo_pngSize);
    // config slider
    DepthSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    DepthSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 20);
    addAndMakeVisible(DepthSlider);
    
    depthAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
                                                                                             audioProcessor.treeState, "depth", DepthSlider
                                                                                             );
    // --------------------------
    addAndMakeVisible(audioProcessor.mainWaveViewer);
    audioProcessor.mainWaveViewer.setColours(bg_color, juce::Colours::black);
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
    
    if (logoImage.isValid())
        {
            // On définit la taille que l'image doit avoir à l'écran
            int imgW = 125;
            int imgH = 75;
            int margin = 10; // Espace par rapport au bord

            // Calcul de la position : x = marge, y = hauteur totale - hauteur image - marge
            int xPos = margin;
            int yPos = getHeight() - imgH - margin;

            g.drawImageWithin (logoImage,
                               xPos, yPos, imgW, imgH,
                               juce::RectanglePlacement::onlyReduceInSize | juce::RectanglePlacement::centred);
        }
}

void NoKringModAudioProcessorEditor::resized()
{
    // On place le slider au centre (X, Y, Largeur, Hauteur)
    // Pour l'instant on le met manuellement, plus tard on utilisera tes coordonnées Figma
    DepthSlider.setBounds (150, 100, 100, 120);
    audioProcessor.mainWaveViewer.setBounds(0, 0, 400, 100);
}
