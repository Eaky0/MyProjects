/*
  ==============================================================================
    
    Player.h

    The `Player` class contains the logic for playing a sound file. It handles 
    the complex code for manipulating buffers to produce sound.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once
#include "AbstractObservable.h"
#include "SoundManager.h"
#include "SoundPlayer.h"
#include "ReverbManager.h"
#include <atomic>
#include <thread>
#include <vector>
#include "FilterManager.h"
#include "DelayAlgorithm.h"
#include "VolumeAlgorithm.h"

class Player : public AbstractObservable, public Thread
{
public:
    Player();
    ~Player();
    void addSoundPlayer();
    void DeleteSoundPlayer();
    void resetSoundPlayers();
    void setModels(SoundManager* sound, ReverbManager* audio, FilterManager* filterManager);
    void playSequence();
    void stopSequence();
    bool isRunning();
    bool isPlayerPoolReady() const;
    void changeSoundPlayerSource(Sound* newSource);
    void setUpSoundPlayerSource(Sound* newSource);

    void resetSteps() { SoundM->resetAllSteps(); };
    void resetSounds() { SoundM->resetAllSounds(); };
    void resetSettings() { SoundM->resetAllSettings(); };
    void run() override;
    void initializePlayerPoolAsync();
    int CalculateRythm(int swingvalue);

    std::shared_ptr<ReverbManager> getReverbManager() const { return ReverbM; }
    std::shared_ptr<FilterManager> getFilterManager() const { return FilterM; }

private:
    int getIntervalFromBPM();
    void setupPlayers();
    void cleanupPlayers();
    void initializePlayerPool();
    bool NoSounds();
    juce::File SearchFile(juce::String sound);

    juce::Array<soundPlayer*> soundPlayers;

    std::vector<std::shared_ptr<Sound>> soundTracks;
    std::shared_ptr<SoundManager> SoundM;
    std::shared_ptr<ReverbManager> ReverbM;
    std::shared_ptr<FilterManager> FilterM;
    std::atomic<bool> Running{ false };
    std::atomic<bool> isPoolReady{ false };
    std::atomic<bool> isPoolInitializing{ false };
    double bpm = 120.0;

    int currentPlayerIndex = 0;
    CriticalSection lock;
    std::mutex mutex;
    std::condition_variable cv;
};
