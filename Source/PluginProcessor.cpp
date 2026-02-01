/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <algorithm>
#include <juce_core/juce_core.h>

//==============================================================================
NoKringModAudioProcessor::NoKringModAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo())
                       .withOutput ("Output", juce::AudioChannelSet::stereo())
                       .withInput("Sidechain", juce::AudioChannelSet::stereo()))
#endif
{
}

NoKringModAudioProcessor::~NoKringModAudioProcessor()
{
}

//==============================================================================
const juce::String NoKringModAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool NoKringModAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool NoKringModAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool NoKringModAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double NoKringModAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int NoKringModAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int NoKringModAudioProcessor::getCurrentProgram()
{
    return 0;
}

void NoKringModAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String NoKringModAudioProcessor::getProgramName (int index)
{
    return {};
}

void NoKringModAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void NoKringModAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Alignement sample rates
    currentSampleRate = sampleRate;
}

void NoKringModAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool NoKringModAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Main output : UNIQUEMENT mono ou stereo
    auto mainOut = layouts.getMainOutputChannelSet();
    if (mainOut != juce::AudioChannelSet::mono()
     && mainOut != juce::AudioChannelSet::stereo())
        return false;

    // Main input doit matcher output (sauf synthé)
    #if ! JucePlugin_IsSynth
    if (layouts.getMainInputChannelSet() != mainOut)
        return false;
    #endif

    // Sidechain OK : disabled OU mono OU stereo
    // Check if there is a second input bus (sidechain) using public members
    if (layouts.inputBuses.size() > 1) {
        auto sidechain = layouts.getChannelSet(true, 1);
        if (!sidechain.isDisabled()
         && sidechain != juce::AudioChannelSet::mono()
         && sidechain != juce::AudioChannelSet::stereo())
            return false;
    }

    return true;
}
#endif

void NoKringModAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    //DBG("Samples/Block : " << buffer.getNumSamples());
    //DBG("Total Input Channels : " << getTotalNumInputChannels());
    //DBG("Bus count : " << getBusCount(true));
    
    auto mainBus = getBusBuffer(buffer, true, 0); // bus principal
    auto* mainL = mainBus.getWritePointer(0);
    auto* mainR = mainBus.getWritePointer(1);
    auto sidechainBus = getBusBuffer(buffer, true, 1); // bus signal carrier (sidechain)
    auto* sidechainL = sidechainBus.getWritePointer(0);
    auto* sidechainR = sidechainBus.getWritePointer(1);

    // avoid feedback loops
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
        
        // obtention des 2 canaux carrier
        float sidechainSampleL = sidechainL[sample];
        float sidechainSampleR = sidechainR[sample];
        
        // rectification des signaux sample par sample pour pouvoir multiplier l'entrée par la carrier rectifiée instantanément
        float rectifiedL = std::fmaxf(1.0f - std::fabs(sidechainSampleL), 0);
        float rectifiedR = std::fmaxf(1.0f - std::fabs(sidechainSampleR), 0);
        
        // output : multiplication du main par le carrier rectifié
        mainL[sample] *= rectifiedL;
        mainR[sample] *= rectifiedR;
    }
}

//==============================================================================
bool NoKringModAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* NoKringModAudioProcessor::createEditor()
{
    return new NoKringModAudioProcessorEditor (*this);
}

//==============================================================================
void NoKringModAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void NoKringModAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new NoKringModAudioProcessor();
}
