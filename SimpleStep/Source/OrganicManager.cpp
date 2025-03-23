/*
  ==============================================================================

    OrganicManager.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "OrganicManager.h"

/**
 * OrganicManager
 * Constructor for OrganicManager. Initializes the algorithms and creates a SoundManager.
 *
 * @pre None
 * @post Algorithms are set and SoundManager is initialized.
 */
OrganicManager::OrganicManager() {
    setAlgorithms();
    SoundM = std::make_shared<SoundManager>();
}

/**
 * ~OrganicManager
 * Destructor for OrganicManager.
 *
 * @pre None
 * @post Any resources used by OrganicManager are cleaned up.
 */
OrganicManager::~OrganicManager()
{
}

void OrganicManager::setOrganicView(OrganicPopupComponent* popup)
{
    popupREF = popup;
}

/**
 * setSMPtr
 * Sets the SoundManager pointer.
 *
 * @param s Pointer to the SoundManager.
 * @pre None
 * @post The SoundManager pointer is updated.
 */
void OrganicManager::setSMPtr(SoundManager* s)
{
    SoundM.reset(s);
}

/**
 * setAlgorithms
 * Initializes the algorithms used by the OrganicManager.
 *
 * @pre None
 * @post The delay, pitch, volume, and swing algorithms are initialized.
 */
void OrganicManager::setAlgorithms()
{
    delayAlg = std::make_unique<DelayAlgorithm>();
    pitchAlg = std::make_unique<PitchAlgorithm>();
    volumeAlg = std::make_unique<VolumeAlgorithm>();
    swingAlg = std::make_unique<SwingAlgorithm>();
}

/**
 * calculateAmountActive
 * Calculates the number of active steps for each sound.
 *
 * @return A vector containing the number of active steps for each sound.
 * @pre SoundManager is properly initialized.
 * @post Returns a vector with the count of active steps for each sound.
 */
std::vector<int> OrganicManager::calculateAmountActive()
{
    std::vector<int> temp;
    DBG("active steps");
    for (int i = 0; i < SoundM->getRows(); i++) {
        Sound* sound = SoundM->getSoundAt(i);
        int counter = 0;
        for (int page = 0; page < SoundM->getPages(); ++page) {
            for (int x = 0; x < SoundM->getSteps(); x++) {
                Step* step = sound->getStepAt(page, x);
                if (step->getStatus() == true) {
                    counter++;
                }
            }
        }
        DBG(counter);
        temp.push_back(counter);
    }
    return temp;
}

/**
 * calcChancetoChange
 * Calculates the chance to change a step based on the number of active steps.
 *
 * @param totalSteps The total number of steps.
 * @param activeSteps The number of active steps.
 * @return A boolean indicating whether a step should be changed.
 * @pre None
 * @post Returns true if the step should be changed, false otherwise.
 */
float OrganicManager::calcChancetoChange(int totalSteps, int activeSteps)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);
    float randomValue = dis(gen);

    float chance = ((float)(totalSteps - activeSteps) / (float)totalSteps);
    return randomValue < chance;
}

/**
 * contains
 * Checks if a vector contains a specific value.
 *
 * @param vec The vector to check.
 * @param value The value to look for.
 * @return A boolean indicating whether the vector contains the value.
 * @pre None
 * @post Returns true if the vector contains the value, false otherwise.
 */
template <typename T>
bool contains(const std::vector<T>& vec, const T& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

/**
 * OurAlgorithm
 * Applies a custom algorithm to modify the steps of the sounds.
 *
 * @param steps A vector of steps to be modified.
 * @pre SoundManager and algorithms are properly initialized.
 * @post The specified steps are modified according to the custom algorithm.
 */
void OrganicManager::OurAlgorithm(std::vector<int> steps)
{
    int totalsteps = (int)SoundM->getPages() * (int)SoundM->getSteps();
    int organicValue = (int)SoundM->getGParam(Gparam::ORGANIC);
    int numSounds = SoundM->getRows();
    int numSteps = SoundM->getSteps();
    int numPages = SoundM->getPages();

    auto arrayofactive = calculateAmountActive();
    bool stepsgotChance = popupREF->isRandomChangeEnabled();

    for (int i = 0; i < numSounds; i++) {
        Sound* sound = SoundM->getSoundAt(i);
        if (sound->getSoundName() != "Empty" && (steps.empty() || contains(steps, i))) {
            for (int page = 0; page < numPages; ++page) {
                for (int x = 0; x < numSteps; x++) {
                    bool changeit = calcChancetoChange(totalsteps, arrayofactive[i]);
                    Step* step = sound->getStepAt(page, x);

                    if (step->getStatus() == true && (changeit || !stepsgotChance) && !step->getLockState(Gparam::ORGANIC)) {
                        float currentVolume = (float)step->getVolume();
                        step->setVolume(volumeAlg->calculateNewValue(currentVolume, organicValue));

                        float currentPitch = step->getPitch();
                        step->setPitch(pitchAlg->calculateNewValue(currentPitch, organicValue));

                        float currentDelay = step->getDelay();
                        step->setDelay(delayAlg->calculateDelay(SoundM->getGParam(Gparam::BPM), organicValue, 1));
                        step->setManipulationstat(true);
                    }
                    else {
                        step->setManipulationstat(false);
                    }
                }
            }
        }
    }
}

/**
 * LOGAlgorithm
 * Applies a logarithmic algorithm to modify the steps of the sounds.
 *
 * @param steps A vector of steps to be modified.
 * @pre SoundManager and algorithms are properly initialized.
 * @post The specified steps are modified according to the logarithmic algorithm.
 */
void OrganicManager::LOGAlgorithm(std::vector<int> steps)
{
    int totalsteps = (int)SoundM->getPages() * (int)SoundM->getSteps();
    int organicValue = (int)SoundM->getGParam(Gparam::ORGANIC);
    int numSounds = SoundM->getRows();
    int numSteps = SoundM->getSteps();
    int numPages = SoundM->getPages();

    auto arrayofactive = calculateAmountActive();
    bool stepsgotChance = popupREF->isRandomChangeEnabled();

    for (int i = 0; i < numSounds; i++) {
        Sound* sound = SoundM->getSoundAt(i);
        if (sound->getSoundName() != "Empty" && (steps.empty() || contains(steps, i))) {
            for (int page = 0; page < numPages; ++page) {
                for (int x = 0; x < numSteps; x++) {
                    bool changeit = calcChancetoChange(totalsteps, arrayofactive[i]);
                    Step* step = sound->getStepAt(page, x);

                    if (step->getStatus() == true && (changeit || !stepsgotChance) && !step->getLockState(Gparam::ORGANIC)) {
                        float currentVolume = (float)step->getVolume();
                        step->setVolume(volumeAlg->calculateNewLogValue(currentVolume, organicValue));

                        float currentPitch = step->getPitch();
                        step->setPitch(pitchAlg->calculateNewLogValue(currentPitch, organicValue));

                        float currentDelay = step->getDelay();
                        step->setDelay(delayAlg->calculateLogDelay(SoundM->getGParam(Gparam::BPM), organicValue, 1));
                        step->setManipulationstat(true);
                    }
                    else {
                        step->setManipulationstat(false);
                    }
                }
            }
        }
    }
}

/**
 * getStepsToChange
 * Retrieves the steps to be changed based on user input.
 *
 * @return A vector of steps to be changed.
 * @pre None
 * @post Returns a vector of steps to be changed based on the user input.
 */
std::vector<int> OrganicManager::getStepsToChange()
{
    std::vector<int> steps;
    juce::String input = popupREF->getInfluenceSounds();

    if (input == "all" || input == "") {
        return steps;
    }

    std::istringstream stream(input.toStdString());
    std::string token;
    while (std::getline(stream, token, ',')) {
        token.erase(token.begin(), std::find_if(token.begin(), token.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
        token.erase(std::find_if(token.rbegin(), token.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base());

        try {
            int step = std::stoi(token);
            steps.push_back(step + 1);
        }
        catch (const std::invalid_argument&) {
            continue;
        }
    }

    return steps;
}

/**
 * applyOrganic
 * Applies the organic algorithm to the selected steps.
 *
 * @pre SoundManager and algorithms are properly initialized.
 * @post The selected steps are modified according to the selected algorithm.
 */
void OrganicManager::applyOrganic()
{
    std::vector<int> steps = getStepsToChange();
    int alg = popupREF->getSelectedAlgorithm();

    switch (alg) {
    case 1:
        break;
    case 2:
        OurAlgorithm(steps);
        break;
    case 3:
        LOGAlgorithm(steps);
        break;
    default:
        break;
    }
}
