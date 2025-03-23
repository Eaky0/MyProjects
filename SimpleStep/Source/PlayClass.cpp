/*
  ==============================================================================

    Player.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "PlayClass.h"

/**
* Player
* Constructor for the Player class. Initializes the Player object with a SoundManager and a FilterManager.
*
* @pre None.
* @post A Player object is created with a SoundManager and a FilterManager.
*
*/
Player::Player() : Thread("Sequence Player Thread") {
    SoundM = std::make_shared<SoundManager>();
    FilterM = std::make_shared<FilterManager>();
}

/**
* initializePlayerPool
* Initializes the sound player pool for playing sequences.
*
* @pre None.
* @post The sound player pool is initialized with a certain number of sound players.
*
*/
void Player::initializePlayerPool()
{
    isPoolInitializing = true;
    if (soundPlayers.size() > SoundM->getRows())
    {
        isPoolReady = true;
        isPoolInitializing = false;
        return;
    }
    int poolSize = SoundM->getRows() * 1.5;
    for (int i = 0; i < poolSize; ++i) {
        soundPlayers.add(new soundPlayer());
    }
    currentPlayerIndex = 0;
    isPoolReady = true;
    isPoolInitializing = false;
}

/**
* initializePlayerPoolAsync
* Initializes the sound player pool asynchronously.
*
* @pre None.
* @post The sound player pool is initialized asynchronously.
*
*/
void Player::initializePlayerPoolAsync()
{
    std::thread(&Player::initializePlayerPool, this).detach();
}

/**
* ~Player
* Destructor for the Player class. Stops the sequence playback.
*
* @pre None.
* @post The Player object is destructed and sequence playback is stopped.
*
*/
Player::~Player()
{
    stopSequence();
}

/**
* addSoundPlayer
* Adds a new sound player to the sound player pool.
*
* @pre None.
* @post A new sound player is added to the sound player pool.
*
*/
void Player::addSoundPlayer()
{
    soundPlayers.add(new soundPlayer());
    soundTracks = SoundM->getSounds();
}

/**
* DeleteSoundPlayer
* Deletes the last sound player from the sound player pool.
*
* @pre None.
* @post The last sound player is removed from the sound player pool.
*
*/
void Player::DeleteSoundPlayer() {
    soundPlayers.remove(soundPlayers.size() - 1);
    soundTracks = SoundM->getSounds();
}

/**
* resetSoundPlayers
* Clears the sound player pool.
*
* @pre None.
* @post The sound player pool is cleared.
*
*/
void Player::resetSoundPlayers()
{
    soundPlayers.clear();
}


void Player::setModels(SoundManager* sound, ReverbManager * audio, FilterManager* filterManager)
{
    SoundM.reset(sound);
    ReverbM.reset(audio);
    FilterM.reset(filterManager);
    // for (int i = 0; i < SoundM->getRows(); ++i) {
    //     soundPlayers.add(new soundPlayer());
    // }
}

/**
* playSequence
* Starts playing the sequence, continuously updating the sound player pool with the current sequence steps.
*
* @pre None.
* @post The sequence starts playing, and the sound player pool is updated with the current sequence steps.
*
*/
void Player::playSequence()
{
    Running = true;
    if (!isThreadRunning()) {
        startThread();
    }
}


/**
* run
* Thread function that runs the sequence player, continuously updating the sound player pool with the current sequence steps.
*
* @pre None.
* @post The sequence player runs and updates the sound player pool with the current sequence steps.
*
*/
void Player::run() {
    setupPlayers();
    int counter = 0;
    int currentPage = 0;
    auto steps = SoundM->getNextSteps(currentPage, counter);
    int prev_Stepsize = steps.size();
    std::vector<float> data{ 0.0f, 0.0f, 0.0f, 0.0f };
    int RythmReplayIndex = 0;

    while (!threadShouldExit()) {
        steps = SoundM->getNextSteps(currentPage, counter++);
        data = std::vector<float> { 0.0f, 0.0f, 0.0f, 0.0f };

        if (prev_Stepsize == steps.size() - 1) {
            addSoundPlayer();
        }

        if (prev_Stepsize == steps.size() + 1) {
            DeleteSoundPlayer();
        }

        if (counter >= SoundM->getSteps()) {
            counter = 0;
            ++currentPage;
            if (currentPage > (SoundM->getPages() - 1)) {
                currentPage = 0;
            }
            
        }

        try {
            for (int i = 0; i < steps.size() && i < soundPlayers.size(); ++i) {
                if (steps[i]->getStatus() && soundTracks[i]->getSoundName() != "Empty") {
                    soundPlayers[currentPlayerIndex]->openFile(SearchFile(soundTracks[i]->getSoundName()));
                    soundPlayers[currentPlayerIndex]->setSound(soundTracks[i].get());
                    soundPlayers[currentPlayerIndex]->setVolume(steps[i]->getVolume() / 50);
                    soundPlayers[currentPlayerIndex]->setDelay(steps[i]->getDelay());
                    soundPlayers[currentPlayerIndex]->applyFilters(FilterM->getParams(), FilterM->getLowPassStatus(), FilterM->getHighPassStatus());
                    //soundPlayers[currentPlayerIndex]->setBpm(30);
                    soundPlayers[currentPlayerIndex]->applyReverb(ReverbM->GetParams(), SoundM->isReverbed(), steps[i]->getLockState(Gparam::REVERB));
                    soundPlayers[currentPlayerIndex]->setPitch(steps[i]->getPitch());
                    
                    
                    //Swing Interference
                    float Swing = SoundM->getGParam(Gparam::SWING);
                    if (Swing > 0.0f) {
                        
                        DelayAlgorithm del;

                        if (Swing > 7.0f)
                            soundPlayers[currentPlayerIndex]->setDelay(del.calculateDelay(bpm, 7.0f, 1));
                        else
                            soundPlayers[currentPlayerIndex]->setDelay(del.calculateDelay(bpm, Swing, 1));

                        if (Swing > 3.0f) {
                            soundPlayers[currentPlayerIndex]->applyGain(true);
                            soundPlayers[currentPlayerIndex]->setVolume(steps[i]->getVolume() / 50);
                            if (Swing > 6.0f) {
                                RythmReplayIndex = CalculateRythm(Swing);
                                soundPlayers[RythmReplayIndex]->play();  
                                sleep(getIntervalFromBPM() / 2);
                                
                            }
                        }
                        else {
                            soundPlayers[currentPlayerIndex]->applyGain(false);
                        }
                    }

                    soundPlayers[currentPlayerIndex]->play();
                    currentPlayerIndex = (currentPlayerIndex + 1) % soundPlayers.size();

                    data[0] += steps[i]->getVolume();
                    data[1] += 1;
                    data[2] += steps[i]->getPitch();
                    data[3] += 1;

                }
            }
            std::vector<float> GraphData{ (data[0] / data[1]), (data[2]/ data[3]) };
            notifyObservers(GraphData);
        }
        catch (...) { DBG("Error Found?"); }
        std::unique_lock<std::mutex> lock(mutex);
        if (cv.wait_for(lock, std::chrono::milliseconds(getIntervalFromBPM()), [this] { return threadShouldExit(); })) {
            break;
        }

        prev_Stepsize = steps.size();
    }
    cleanupPlayers();
}



/**
* CalculateRythm
* Calculates the rhythm index based on the swing value.
*
* @param swingvalue The swing value used to calculate the rhythm index.
* @pre None.
* @post The rhythm index is calculated based on the swing value.
* @return The calculated rhythm index.
*
*/
int Player::CalculateRythm(int swingvalue) {
   return (currentPlayerIndex + (11 - swingvalue)) % soundPlayers.size();
}


/**
* getIntervalFromBPM
* Calculates the interval between beats based on the BPM (Beats Per Minute) value.
*
* @pre None.
* @post The interval between beats is calculated based on the BPM value.
* @return The interval between beats in milliseconds.
*
*/
int Player::getIntervalFromBPM() {
    return 60000 / static_cast<int>(SoundM->getGParam(Gparam::BPM));
}

/**
* setupPlayers
* Waits until the sound player pool is ready, then initializes the players.
*
* @pre None.
* @post The sound player pool is initialized.
*
*/
void Player::setupPlayers() {
    while (!isPoolReady) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    soundTracks = SoundM->getSounds();
}

/**
* NoSounds
* Checks if any of the sound players are playing a sound.
*
* @pre None.
* @post None.
* @return True if no sound players are currently playing a sound, false otherwise.
*
*/
bool Player::NoSounds() {
    for (auto player : soundPlayers) {
        if (player->getCurrentSound() != nullptr) {
            return false;
        }
    }
    return true;
}

/**
* SearchFile
* Searches for a sound file in the application's sound library directory.
*
* @param sound The name of the sound file to search for.
* @pre None.
* @post None.
* @return The file object corresponding to the searched sound file, or an empty file object if not found.
*
*/
juce::File Player::SearchFile(juce::String sound)
{
    juce::File Exporter = juce::File::getCurrentWorkingDirectory();
    DBG("Current Working Directory: " << Exporter.getFullPathName());
    juce::File LibDirectory;
    juce::File Workspace;
    juce::File Builds;
    //MacOS
    if (Exporter.getFullPathName() == "/")
    {
        Exporter = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();
        DBG("Adjusted Working Directory: " << Exporter.getFullPathName());

        LibDirectory = Exporter.getChildFile("Sound Library");
        DBG("Resources Directory: " << LibDirectory.getFullPathName());

    }
    else {
        Builds = Exporter.getParentDirectory();
        DBG("Current Working Directory: " << Builds.getFullPathName());


        Workspace = Builds.getParentDirectory();
        DBG("Current Working Directory: " << Workspace.getFullPathName());

        LibDirectory = Workspace.getChildFile("Sound Library");
        DBG("Resources Directory: " << LibDirectory.getFullPathName());
    }

    if (LibDirectory.isDirectory())
    {
        juce::DirectoryIterator iter(LibDirectory, false);
        while (iter.next())
        {
            juce::File file = iter.getFile();
            if (file.getFileNameWithoutExtension() == sound) {
                return file;
            }
        }
    }
    else
    {
        DBG("Directory Sound Library was not found!");
    }

    return juce::File();
}

/**
* stopSequence
* Stops the sequence player and all associated sound players.
*
* @pre None.
* @post The sequence player and associated sound players are stopped.
*
*/
void Player::stopSequence()
{
    signalThreadShouldExit();
    cv.notify_all();
    waitForThreadToExit(-1);

    Running = false;

    for (auto player : soundPlayers)
    {
        player->stop();
    }
    // cleanupPlayers();
}

/**
* cleanupPlayers
* Cleans up the sound player pool.
*
* @pre None.
* @post The sound player pool is cleaned up.
*
*/
void Player::cleanupPlayers() {
    SoundM->Break();
}

/**
* isRunning
* Checks if the sequence player is currently running.
*
* @pre None.
* @post None.
* @return True if the sequence player is running, false otherwise.
*
*/
bool Player::isRunning()
{
    return Running;
}

/**
* isPlayerPoolReady
* Checks if the sound player pool is ready.
*
* @pre None.
* @post None.
* @return True if the sound player pool is ready, false otherwise.
*
*/
bool Player::isPlayerPoolReady() const
{
    return isPoolReady;
}