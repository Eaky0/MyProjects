/*
  ==============================================================================

    soundPlayer.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "SoundPlayer.h"

using namespace juce;

/**
* soundPlayer constructor
* Constructs a soundPlayer object.
*
* @pre None
* @post A soundPlayer object is created.
*/
soundPlayer::soundPlayer()
{
    formatManager.registerBasicFormats();
    transportSource.addChangeListener(this);    
    setAudioChannels(2, 2);
    startTimer(1000);

    Gain.setGainLinear(volume);

}

/**
* soundPlayer constructor
* Constructs a soundPlayer object from a file.
*
* @param file The file to initialize the sound player from
* @pre The file must exist and be valid
* @post A soundPlayer object is created and initialized with the file
*/
soundPlayer::soundPlayer(const File& file)
{
    initializeFromFile(file);
}



/**
* soundPlayer destructor
* Destructs a soundPlayer object.
*
* @pre None
* @post The soundPlayer object is destroyed.
*/
soundPlayer::~soundPlayer()
{
    shutdownAudio();
}


/**
* prepareToPlay function
* Prepares the sound player for playback.
*
* @param samplesPerBlockExpected The expected number of samples per block
* @param sampleRate The sample rate
* @pre None
* @post The sound player is prepared for playback
*/
void soundPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{    
    mSampleRate = sampleRate;
    SampleBlocks = samplesPerBlockExpected;

    calculateUpdateInterval(sampleRate);
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);

    if (rev)
    {
        reverb.setSampleRate(sampleRate);
    }

    if (swing) {
        Gain.prepare({ sampleRate, static_cast<uint32>(samplesPerBlockExpected), 2 });
    }

}

/**
* calculateUpdateInterval function
* Calculates the update interval based on sample rate and BPM.
*
* @param sampleRate The sample rate
* @pre None
* @post Update interval is calculated
*/
void soundPlayer::calculateUpdateInterval(double sampleRate)
{
    mUpdateInterval = (60.0 / bpm) * sampleRate;
}



/**
* getNextAudioBlock function
* Retrieves the next audio block.
*
* @param bufferToFill The buffer to fill with audio
* @pre None
* @post The buffer is filled with audio data
*/
void soundPlayer::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    const auto bufferSize = bufferToFill.numSamples;
    mTotalSamples += bufferSize;
    mSamplesRemaining = mTotalSamples % mUpdateInterval;

    if (readerSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
        return;
    }


    processAudioBlock(bufferToFill);
}


/**
* releaseResources function
* Releases the resources used by the sound player.
*
* @pre None
* @post Sound player resources are released
*/
void soundPlayer::releaseResources()
{
    transportSource.releaseResources();
}


/**
* changeListenerCallback function
* Handles change listener callback.
*
* @param source The change broadcaster
* @pre None
* @post Change listener callback is handled
*/
void soundPlayer::changeListenerCallback(ChangeBroadcaster* source)
{
    if (source == &transportSource)
    {
        if (transportSource.isPlaying())
            changeState(Playing);
        else
            changeState(Stopped);
    }
}

/**
* timerCallback function
* Handles timer callback.
*
* @pre None
* @post Timer callback is handled
*/
void soundPlayer::timerCallback()
{
    if (transportSource.isPlaying())
    {
        updateTimerDuringPlayback();



    }
    else
    {
        updateTimerWhenStopped();
    }
}


/**
* updateLoopState function
* Updates the loop state.
*
* @param shouldLoop Whether to enable looping or not
* @pre None
* @post Loop state is updated
*/
void soundPlayer::updateLoopState(bool shouldLoop)
{
    if (readerSource.get() != nullptr)
        readerSource->setLooping(shouldLoop);
}


/**
* openFile function
* Opens a file for playback.
*
* @param file The file to open
* @pre None
* @post The file is opened for playback
*/
void soundPlayer::openFile(const File& file)
{
    initializeFromFile(file);
}


/**
* play function
* Starts playback.
*
* @pre None
* @post Playback is started
*/
void soundPlayer::play()
{
    if (!initial) {
        updateLoopState(false);
        changeState(Playing);
    }
    else {
        initial = false;
    }

}

/**
* stop function
* Stops playback.
*
* @pre None
* @post Playback is stopped
*/
void soundPlayer::stop()
{
    changeState(Stopping);
}

/**
* setPitch function
* Sets the pitch of the playback.
*
* @param octave The pitch value
* @pre None
* @post The pitch of playback is set
*/
void soundPlayer::setPitch(float octave)
{
    if (octave != pitch) {
        pitch = octave;
        double newSampleRate = mSampleRate - (pitch * 5000);
        transportSource.prepareToPlay(SampleBlocks, newSampleRate);
    }
}

/**
* setDelay function
* Sets the delay value.
*
* @param delayValue The delay value
* @pre None
* @post The delay value is set
*/
void soundPlayer::setDelay(float delayValue)
{
    delay = delayValue;
}

/**
* setBpm function
* Sets the BPM (beats per minute).
*
* @param newBpm The BPM value
* @pre None
* @post The BPM is set
*/
void soundPlayer::setBpm(int newBpm)
{
    bpm = newBpm;
    calculateUpdateInterval(mSampleRate);
}

/**
* setPlayAt function
* Sets the time to start playback.
*
* @param startTimeInSeconds The time to start playback in seconds
* @pre None
* @post The time to start playback is set
*/
void soundPlayer::setPlayAt(double startTimeInSeconds)
{
    playAtTime = startTimeInSeconds;
}

/**
* getPlayAt function
* Retrieves the time to start playback.
*
* @return The time to start playback in seconds
* @pre None
* @post The time to start playback is retrieved
*/
double soundPlayer::getPlayAt() const
{
    return playAtTime;
}

/**
* setStopAtTime function
* Sets the time to stop playback.
*
* @param endTimeInSeconds The time to stop playback in seconds
* @pre None
* @post The time to stop playback is set
*/
void soundPlayer::setStopAtTime(double endTimeInSeconds)
{
    stopAtTime = endTimeInSeconds;
}

/**
* getStopAtTime function
* Retrieves the time to stop playback.
*
* @return The time to stop playback in seconds
* @pre None
* @post The time to stop playback is retrieved
*/
double soundPlayer::getStopAtTime() const
{
    return stopAtTime;
}


/**
* Playingstatus function
* Checks the playing status of the sound player.
*
* @return True if the sound player is playing, false otherwise
* @pre None
* @post Playing status of the sound player is checked
*/
bool soundPlayer::Playingstatus() const {
    return transportSource.isPlaying();
}

/**
* setVolume function
* Sets the volume of the sound player.
*
* @param newVolume The volume value
* @pre None
* @post The volume of the sound player is set
*/
void soundPlayer::setVolume(float newVolume)
{
    volume = newVolume;
}

/**
* applyFilters function
* Applies filters to the audio.
*
* @param filterParams The parameters for the filters
* @param lowPassStatus Whether to enable low-pass filter
* @param highPassStatus Whether to enable high-pass filter
* @pre None
* @post Filters are applied to the audio
*/
void soundPlayer::applyFilters(juce::ValueTree filterParams, bool lowPassStatus, bool highPassStatus)
{
    lowPass = lowPassStatus;
    highPass = highPassStatus;

    //define the params
    double lowPassFreq = (double)filterParams.getProperty("LowFrequency");
    double highPassFreq = (double)filterParams.getProperty("HighFrequency");
    double lowQ = (double)filterParams.getProperty("LowQ");
    double highQ = (double)filterParams.getProperty("HighQ");

    juce::IIRCoefficients newLowCo = juce::IIRCoefficients().makeLowPass(mSampleRate, lowPassFreq, lowQ);
    juce::IIRCoefficients newHighCo = juce::IIRCoefficients().makeHighPass(mSampleRate, highPassFreq, highQ);

    DBG("LowPass Coefficients: " << newLowCo.coefficients[0] << ", " << newLowCo.coefficients[1] << ", " << newLowCo.coefficients[2]);
    DBG("HighPass Coefficients: " << newHighCo.coefficients[0] << ", " << newHighCo.coefficients[1] << ", " << newHighCo.coefficients[2]);
    DBG("Sample rate " << mSampleRate);

    LowPassFilter.setCoefficients(newLowCo);
    HighPassFilter.setCoefficients(newHighCo);
}


/**
* applyReverb function
* Applies reverb effect to the audio.
*
* @param reverbParams The parameters for the reverb effect
* @param Reverb Whether to enable reverb effect
* @param Locked Whether the reverb effect is locked
* @pre None
* @post Reverb effect is applied to the audio
*/
void soundPlayer::applyReverb(juce::ValueTree * reverbParams, bool Reverb, bool Locked)
{
        ReverbParams.roomSize = reverbParams->getProperty("Roomsize");
        ReverbParams.damping = reverbParams->getProperty("Damping");
        ReverbParams.wetLevel = reverbParams->getProperty("Wet");
        ReverbParams.dryLevel = reverbParams->getProperty("Dry");
        ReverbParams.width = reverbParams->getProperty("Width");
        reverb.setParameters(ReverbParams);
        if (!Locked) {
            rev = Reverb;
        }
        else {
            rev = false;
        }



}


/**
* applyGain function
* Applies gain to the audio.
*
* @param activationReached Whether the gain activation condition is reached
* @pre None
* @post Gain is applied to the audio
*/
void soundPlayer::applyGain(bool activationReached) {
    swing = activationReached;
}

/**
* changeState function
* Changes the state of the sound player.
*
* @param newState The new state of the sound player
* @pre None
* @post State of the sound player is changed
*/
void soundPlayer::changeState(TransportState newState)
{
    if (state != newState)
    {
        state = newState;

        switch (state)
        {
        case Stopped:
            transportSource.setPosition(0.0);
            break;

        case Starting:            
            transportSource.setPosition(-playAtTime + delay);
            break;

        case Playing:
            transportSource.setPosition(-playAtTime + delay);
            transportSource.start();
            break;

        case Stopping:
            transportSource.stop();
            break;
        }
    }
}

/**
* setSound function
* Sets the current sound to be played.
*
* @param s The sound to set
* @pre None
* @post The current sound is set
*/
void soundPlayer::setSound(Sound* s)
{
    
    if (CurrentPlayingSound == nullptr) {
        CurrentPlayingSound = std::make_unique<Sound>("Empty");
    }

    if (CurrentPlayingSound.get() != s) {
        if (s != nullptr) {
            CurrentPlayingSound.release();
            CurrentPlayingSound.reset(s);
        }
        else {
            CurrentPlayingSound.release();
            CurrentPlayingSound = nullptr;
            transportSource.setSource(nullptr);
        }
    }
}


/**
* getCurrentSound function
* Retrieves the current sound being played.
*
* @return The current sound being played
* @pre None
* @post The current sound is retrieved
*/
Sound* soundPlayer::getCurrentSound()
{
    return CurrentPlayingSound.get();
}


/**
* initializeFromFile function
* Initializes the sound player from a file.
*
* @param file The file to initialize from
* @pre None
* @post The sound player is initialized from the file
*/
void soundPlayer::initializeFromFile(const File& file)
{
    auto* reader = formatManager.createReaderFor(file);

    if (reader != nullptr)
    {

        std::unique_ptr<AudioFormatReaderSource> newSource(new AudioFormatReaderSource(reader, true));
        transportSource.setSource(newSource.get(), 0, nullptr, reader->sampleRate);
        readerSource.reset(newSource.release());

        // Calculate the duration of the audio file
        double durationInSeconds = 0.0;
        if (reader->lengthInSamples > 0 && reader->sampleRate > 0)
        {
            durationInSeconds = (double)reader->lengthInSamples / reader->sampleRate;
            DBG("Duration of the audio file: " + String(durationInSeconds) + " seconds");
        }
    }
}

/**
* processAudioBlock function
* Processes the audio block.
*
* @param bufferToFill The buffer to fill with audio data
* @pre None
* @post The audio block is processed
*/
void soundPlayer::processAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    double playbackPosition = transportSource.getCurrentPosition();
    const int NumChannels = bufferToFill.buffer->getNumChannels();
    const int NumSamples = bufferToFill.buffer->getNumSamples();

    if ((stopAtTime != -1 && playbackPosition >= stopAtTime))
    {
        changeState(Stopping);
        for (int channel = 0; channel < bufferToFill.buffer->getNumChannels(); ++channel)
        {
            float* channelData = bufferToFill.buffer->getWritePointer(channel);
            for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
            {
                channelData[sample] = 0.0f;
            }
        }
        return; 
    }
    transportSource.getNextAudioBlock(bufferToFill);

    if (swing) {
        Gain.setGainLinear(volume);
        dsp::AudioBlock<float> block(*bufferToFill.buffer);
        dsp::ProcessContextReplacing<float> context(block);
        Gain.process(context);
    }

    if (rev)
    {
        reverb.processStereo(bufferToFill.buffer->getWritePointer(0), bufferToFill.buffer->getWritePointer(1), bufferToFill.buffer->getNumSamples());
    }



    for (int channel = 0; channel < NumChannels; ++channel)
    {

        float* channelData = bufferToFill.buffer->getWritePointer(channel);

        for (int sample = 0; sample < NumSamples; ++sample)
        {
            channelData[sample] *= volume;
        }

        if (lowPass) {
            LowPassFilter.processSamples(channelData, bufferToFill.numSamples);
        }
        if (highPass) {
            HighPassFilter.processSamples(channelData, bufferToFill.numSamples);
        }
    }


}



/**
* updateTimerDuringPlayback function
* Updates the timer during playback.
*
* @pre None
* @post The timer is updated during playback
*/
void soundPlayer::updateTimerDuringPlayback()
{
    RelativeTime position(transportSource.getCurrentPosition());

    auto minutes = ((int)position.inMinutes()) % 60;
    auto seconds = ((int)position.inSeconds()) % 60;
    auto millis = ((int)position.inMilliseconds()) % 1000;

    auto positionString = String::formatted("%02d:%02d:%03d", minutes, seconds, millis);
}

/**
* updateTimerWhenStopped function
* Updates the timer when playback is stopped.
*
* @pre None
* @post The timer is updated when playback is stopped
*/
void soundPlayer::updateTimerWhenStopped()
{
    if (!transportSource.isPlaying() && transportSource.getCurrentPosition() >= playAtTime)
    {
        play();
        stopTimer(); // Stop the timer once it's time to play
    }
}
