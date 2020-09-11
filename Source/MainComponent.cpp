#define _CRT_SECURE_NO_WARNINGS
#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    addAndMakeVisible(&playButton);
    playButton.setButtonText("Play");
    playButton.onClick = [this] { playButtonClicked(); };
    playButton.setColour(juce::TextButton::buttonColourId, juce::Colours::green);
    playButton.setEnabled(true);

    addAndMakeVisible(&stopButton);
    stopButton.setButtonText("Stop");
    stopButton.onClick = [this] { stopButtonClicked(); };
    stopButton.setColour(juce::TextButton::buttonColourId, juce::Colours::red);
    stopButton.setEnabled(true);

    setSize (800, 600);

    formatManager.registerBasicFormats();
    auto* reader1 = formatManager.createReaderFor(soundFile1);
    if (reader1 != nullptr) {
        std::unique_ptr <juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader1, true));
        transportSource1.setSource(newSource.get(), 0, nullptr, reader1->sampleRate);
        readerSource1.reset(newSource.release());
    }

    auto* reader2 = formatManager.createReaderFor(soundFile2);
    if (reader2 != nullptr) {
        std::unique_ptr <juce::AudioFormatReaderSource> newSource(new juce::AudioFormatReaderSource(reader2, true));
        transportSource2.setSource(newSource.get(), 0, nullptr, reader2->sampleRate);
        readerSource2.reset(newSource.release());
    }


    audioMixer.addInputSource(&transportSource1, true);
    audioMixer.addInputSource(&transportSource2, true);

    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    audioMixer.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    audioMixer.getNextAudioBlock(bufferToFill);
}

void MainComponent::releaseResources()
{
    audioMixer.releaseResources();
}

//==============================================================================
void MainComponent::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    // You can add your drawing code here!
}

void MainComponent::resized()
{
    playButton.setBounds(10, 40, getWidth() - 20, 20);
    stopButton.setBounds(10, 70, getWidth() - 20, 20);
}

void MainComponent::playButtonClicked() {
    transportSource1Gain = transportSource1.getGain();
    DBG(transportSource1Gain);
    transportSource1.setGain(0.05);
    DBG("test message");
    transportSource1.start();
    transportSource2.start();
}

void MainComponent::stopButtonClicked() {
    transportSource1.stop();
    transportSource2.stop();
}