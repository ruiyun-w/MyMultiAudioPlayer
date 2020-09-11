#pragma once

#include <JuceHeader.h>
#include <dbg.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent : public juce::AudioAppComponent
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const juce::AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (juce::Graphics& g) override;
    void resized() override;

private:
    //==============================================================================
    juce::AudioFormatManager formatManager;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource1;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource2;
    juce::AudioTransportSource transportSource1;
    juce::AudioTransportSource transportSource2;
    juce::MixerAudioSource audioMixer;

    juce::File soundFile1 = juce::File("C:\\Users\\lion\\JUCE\\audio\\sijige.wav");
    juce::File soundFile2 = juce::File("C:\\Users\\lion\\JUCE\\audio\\lei.wav");
    juce::TextButton playButton;
    juce::TextButton stopButton;

    void playButtonClicked();

    void stopButtonClicked();

    float transportSource1Gain;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
