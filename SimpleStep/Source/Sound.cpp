/*
  ==============================================================================

    Sound.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "Sound.h"

/**
* Sound Constructor
* Constructs a Sound object with the given name and initializes its parameters.
*
* @param name The name of the sound
* @pre None
* @post A Sound object is created with the given name and initialized parameters
*/
Sound::Sound(juce::String name)
{
    // Initialize SoundName
    SoundName = name;

    // Initialize Patterns with default number of pages
    for (int index = 0; index < 4; ++index) {
        StepRow* newRow = new StepRow();
        Patterns.push_back(newRow);
    }

    // Initialize SoundParameters ValueTree with default parameters
    SoundParameters = juce::ValueTree("SoundProperties");
    SoundParameters.setProperty("Volume", 50, nullptr);
    SoundParameters.setProperty("Delay", 0.0f, nullptr);
    SoundParameters.setProperty("Pitch", 0.0f, nullptr);
}

/**
* Sound Constructor
* Constructs a Sound object with the given name, page amount, and step amount per page,
* and initializes its parameters.
*
* @param name The name of the sound
* @param PageAmount The number of pages
* @param StepAmount The number of steps per page
* @pre None
* @post A Sound object is created with the given name, page amount, step amount per page,
* and initialized parameters
*/
Sound::Sound(juce::String name, int PageAmount, int StepAmount)
{
    // Initialize SoundName
    SoundName = name;

    // Initialize Patterns with custom number of pages and steps per page
    for (int page = 0; page < PageAmount; ++page)
        Patterns.push_back(new StepRow(StepAmount));

    // Initialize SoundParameters ValueTree with default parameters
    SoundParameters = juce::ValueTree("SoundProperties");
    SoundParameters.setProperty("Volume", 50, nullptr);
    SoundParameters.setProperty("Delay", 0.0f, nullptr);
    SoundParameters.setProperty("Pitch", 0.0f, nullptr);
}

/**
* Sound Destructor
* Destroys the Sound object.
*
* @pre None
* @post The Sound object is destroyed
*/
Sound::~Sound()
{
    // Destructor implementation
}

/**
* GetSoundName function
* Returns the name of the sound.
*
* @pre None
* @post None
* @return The name of the sound
*/
juce::String Sound::getSoundName() {
    return SoundName;
}

/**
* SetSoundName function
* Sets the name of the sound.
*
* @param newName The new name for the sound
* @pre None
* @post The name of the sound is updated
*/
void Sound::setSoundName(juce::String newName)
{
    SoundName = newName;
    notifyObservers(3);
}



/**
* GetStepAt function
* Returns the Step object at the specified page and index.
*
* @param page The page index
* @param index The step index
* @pre None
* @post None
* @return A pointer to the Step object at the specified page and index
*/
Step* Sound::getStepAt(int page, int index)
{
    return Patterns[page]->getStepAt(index);
}

/**
* InitNewStep function
* Initializes a new step for each page in the Sound.
*
* @pre None
* @post A new step is initialized for each page in the Sound
*/
void Sound::initNewStep()
{
    for (StepRow* Pattern : Patterns)
        Pattern->initNewStep();
}

/**
* DeleteStep function
* Deletes a step for each page in the Sound.
*
* @pre None
* @post A step is deleted for each page in the Sound
*/
void Sound::deleteStep()
{
    for (StepRow* Pattern : Patterns)
        Pattern->deleteStep();
}

/**
* AddPage function
* Adds a new page to the Sound.
*
* @pre None
* @post A new page is added to the Sound
*/
void Sound::addPage()
{
    StepRow* newRow = new StepRow(Patterns[0]->getStepAmount());
    Patterns.push_back(newRow);
}

/**
* GetSize function
* Returns the number of pages in the Sound.
*
* @pre None
* @post None
* @return The number of pages in the Sound
*/
int Sound::getSize()
{
    return Patterns.size();
}

/**
* ResetAllSteps function
* Resets all steps in the Sound.
*
* @pre None
* @post All steps in the Sound are reset
*/
void Sound::resetAllSteps()
{
    for (StepRow* Pattern : Patterns)
        Pattern->resetAllSteps();
}

/**
* GetStepParamValue function
* Returns the value of a parameter for a step at the specified page and index.
*
* @param page The page index
* @param index The step index
* @param P The parameter type
* @pre None
* @post None
* @return The value of the specified parameter for the step
*/
float Sound::getStepParamValue(int page, int index, Sparam P)
{
    return Patterns[page]->getParamValue(index, P);
}

/**
* SetStepParamValue function
* Sets the value of a parameter for a step at the specified page and index.
*
* @param page The page index
* @param index The step index
* @param newValue The new value for the parameter
* @param P The parameter type
* @pre None
* @post The value of the specified parameter for the step is updated
*/
void Sound::setStepParamValue(int page, int index, float newValue, Sparam P)
{
    Patterns[page]->setParamValue(index, newValue, P);
}

/**
* SetSoundParam function
* Sets the value of a parameter for all steps on a specific page of the Sound.
*
* @param page The page index
* @param NewValue The new value for the parameter
* @param P The parameter type
* @pre None
* @post The value of the specified parameter for all steps on the page is updated
*/
void Sound::setSoundParam(int page, float NewValue, Sparam P)
{
    switch (P) {
    case Sparam::VOLUME:
        SoundParameters.setProperty("Volume", NewValue, nullptr);
        break;
    case Sparam::PITCH:
        SoundParameters.setProperty("Pitch", NewValue, nullptr);
        break;
    case Sparam::DELAY:
        SoundParameters.setProperty("Delay", NewValue, nullptr);
        break;
    default:
        break;
    }

    Patterns[page]->setSoundParam(NewValue, P);
}

/**
* ApplyGain function
* Applies gain to the Sound based on SwingValue and Strength.
*
* @param SwingValue The swing value
* @param Strength The strength value
* @pre None
* @post Gain is applied to the Sound
*/
void Sound::applyGain(int SwingValue, int Strength) {
    VolumeAlgorithm vol;

    if (SwingValue > 3.0f) {
        for (auto Pattern : Patterns) {
            Pattern->setSoundParam(vol.calculateGain(SwingValue, Strength), Sparam::VOLUME);
        }
    }
}


/**
* ResetAllParams function
* Resets all parameters for all steps in the Sound.
*
* @pre None
* @post All parameters for all steps in the Sound are reset
*/
void Sound::resetAllParams()
{
    for (int page = 0; page < Patterns.size(); ++page) {
        setSoundParam(page, 50, Sparam::VOLUME);
        setSoundParam(page, 0, Sparam::PITCH);
        setSoundParam(page, 0, Sparam::DELAY);
    }
}

/**
* ApplyVolumeMultiplier function
* Applies a volume multiplier to all steps in the Sound.
*
* @param multiplier The volume multiplier
* @pre None
* @post Volume is multiplied for all steps in the Sound
*/
void Sound::applyVolumeMultiplier(float multiplier)
{
    int stepAmount = Patterns[0]->getStepAmount();
    int pageAmount = Patterns.size();

    for (int page = 0; page < pageAmount; page++) {
        for (int i = 0; i < stepAmount; ++i) {
            Step* step = getStepAt(page, i);

            float currentVolume = step->getVolume();

            float newVolume = currentVolume * multiplier;

            if (newVolume > 100) {
                newVolume = 100;
            }

            step->setVolume(newVolume);
        }
    }
}

/**
* GetSoundParam function
* Returns the value of the specified parameter for the Sound.
*
* @param P The parameter type
* @pre None
* @post None
* @return The value of the specified parameter for the Sound
*/
float Sound::getSoundParam(Sparam P)
{
    switch (P) {
    case Sparam::VOLUME:
        return SoundParameters.getProperty("Volume");
    case Sparam::PITCH:
        return SoundParameters.getProperty("Pitch");
    case Sparam::DELAY:
        return SoundParameters.getProperty("Delay");
    default:
        break;
    }
}

/**
* SetLock function
* Sets the lock status for a specific parameter across all steps in the Sound.
*
* @param filter The parameter to lock
* @param lock The lock status
* @pre None
* @post The lock status for the specified parameter is set across all steps in the Sound
*/
void Sound::setLock(Gparam filter, bool lock)
{
    for (StepRow* s : Patterns) {
        s->setLock(filter, lock);
    }
}
