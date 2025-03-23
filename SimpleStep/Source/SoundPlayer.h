/*
  ==============================================================================

    soundPlayer.h

    This is the class that is responsible for managing how every sound needs to be played.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Sound.h"
#include <thread>
using namespace juce;

enum TransportState
{
    Stopped,
    Starting,
    Playing,
    Stopping
};

class soundPlayer : public AudioAppComponent,
                    public ChangeListener,
                    public Timer,
                    public AudioSource
{
public:
    soundPlayer();
    soundPlayer(const File& file);
    ~soundPlayer() override;

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void calculateUpdateInterval(double sampleRate);
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void timerCallback() override;

    void updateLoopState(bool shouldLoop);
    void openFile(const File& file);
    void play();
    void stop();
    void setPitch(float octave);
    void setDelay(float delayValue);
    void setBpm(int newBpm);
    void setPlayAt(double startTimeInSeconds);
    double getPlayAt() const;
    void setStopAtTime(double endTimeInSeconds);
    double getStopAtTime() const;
    void setVolume(float newVolume);
    void applyReverb(juce::ValueTree* reverbParams, bool Reverb, bool Locked);
    void applyFilters(juce::ValueTree filterParams, bool lowPassStatus, bool highPassStatus);
    void applyGain(bool activationReached);
    void changeState(TransportState newState);
    
    AudioSource* getAudioSource() { return this; }

    void setSound(Sound * s);
    Sound * getCurrentSound();

    bool Playingstatus() const;
private:
    void initializeFromFile(const File& file);
    void processAudioBlock(const AudioSourceChannelInfo& bufferToFill);
    void updateTimerDuringPlayback();
    void updateTimerWhenStopped();

    int mTotalSamples{ 0 };
    int mUpdateInterval{ 0 };
    int mSamplesRemaining{ 0 };
    double mSampleRate{44100};
    int SampleBlocks;
    double bpm = 60.0; // Default BPM: 1-200
    AudioFormatManager formatManager;
    std::unique_ptr<AudioFormatReaderSource> readerSource;
    AudioTransportSource transportSource;
    TransportState state = Stopped;
    std::unique_ptr<Sound> CurrentPlayingSound;
    Reverb reverb;
    Reverb::Parameters ReverbParams;
    
    //the filters
    juce::IIRFilter LowPassFilter;
    juce::IIRFilter HighPassFilter;

    juce::dsp::Gain<float> Gain;
    

    //booleans to see if a filter is on
    bool lowPass = false;
    bool highPass = false;

    float volume = 1;
    bool rev = false; // reverb
    bool swing = false; // swing
    float delay = 0;
    double playAtTime = 0; // Time at which playback should start in seconds
    double stopAtTime = 1.0f; // Time at which playback should stop in seconds
    bool initial = true;
    float pitch{ 0.0f };

    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(soundPlayer)
};
