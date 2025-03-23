/*
  ==============================================================================

    SoundManager.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "SoundManager.h"

/**
* SoundManager constructor
* Constructs a SoundManager object.
*
* @pre None
* @post SoundManager object is constructed
*/
SoundManager::SoundManager()
{

    for (int i = 0; i < 20; i++) {
        Sounds.push_back(std::make_shared<Sound>("Empty"));
    }

    GlobalParameters = new juce::ValueTree("StepProperties");
    GlobalParameters->setProperty("BPM", 120.0f, nullptr);
    GlobalParameters->setProperty("Swing", 0.0f, nullptr);
    GlobalParameters->setProperty("Organic", 0.0f, nullptr);
    GlobalParameters->setProperty("Reverb", false, nullptr);
    GlobalParameters->setProperty("MasterVolume", 50, nullptr);

}

/**
* SoundManager destructor
* Destroys the SoundManager object.
*
* @pre None
* @post SoundManager object is destroyed
*/
SoundManager::~SoundManager()
{
    delete GlobalParameters;
}

/**
* incrementRows function
* Increments the number of rows.
*
* @pre None
* @post Number of rows is incremented
*/
void SoundManager::incrementRows()
{
    ++rows;
    notifyObservers(34);
    notifyObservers(7);
}

/**
* decrementRows function
* Decrements the number of rows.
*
* @pre None
* @post Number of rows is decremented
*/
void SoundManager::decrementRows()
{
    --rows;
    notifyObservers(34);
    notifyObservers(7);
}

/**
* getRows function
* Gets the number of rows.
*
* @return Number of rows
* @pre None
* @post None
*/
int SoundManager::getRows()
{
    return rows;
}

/**
* getGParam function
* Gets the value of a global parameter.
*
* @param Param The parameter to get
* @return The value of the parameter
* @pre None
* @post None
*/
float SoundManager::getGParam(Gparam Param)
{
    switch (Param) {
    case Gparam::BPM:
        return GlobalParameters->getProperty("BPM");
    case Gparam::SWING:
        return GlobalParameters->getProperty("Swing");
    case Gparam::ORGANIC:
        return GlobalParameters->getProperty("Organic");
    case Gparam::MASTERVOLUME:
        return GlobalParameters->getProperty("MasterVolume");
    default:
        break;
    }
}

/**
* setGParam function
* Sets the value of a global parameter.
*
* @param newValue The new value for the parameter
* @param Param The parameter to set
* @pre None
* @post The value of the parameter is updated
*/
void SoundManager::setGParam(float newValue, Gparam Param)
{
    switch (Param) {
    case Gparam::BPM:
        GlobalParameters->setProperty("BPM", newValue, nullptr);
        break;
    case Gparam::SWING:
        GlobalParameters->setProperty("Swing", newValue, nullptr);
        break;
    case Gparam::ORGANIC:
        GlobalParameters->setProperty("Organic", newValue, nullptr);
        break;
    case Gparam::MASTERVOLUME:
        GlobalParameters->setProperty("MasterVolume", newValue, nullptr);
        break;
    default:
        break;
    }
}

/**
* addNewSound function
* Adds a new sound.
*
* @pre None
* @post A new sound is added
*/
void SoundManager::addNewSound()
{
    if (rows < 20) {
        ++rows;

        notifyObservers(7);
    }
}

/**
* resetAllSteps function
* Resets all steps.
*
* @pre None
* @post All steps are reset
*/
void SoundManager::resetAllSteps() {

    for (std::shared_ptr<Sound> s : Sounds) {
        s->resetAllSteps();
    }
}

/**
* resetAllSounds function
* Resets all sounds.
*
* @pre None
* @post All sounds are reset
*/
void SoundManager::resetAllSounds() {

    for (std::shared_ptr<Sound> s : Sounds) {
        s->setSoundName("Empty");
    }
}

/**
* resetAllSettings function
* Resets all settings.
*
* @pre None
* @post All settings are reset
*/
void SoundManager::resetAllSettings()
{
    for (std::shared_ptr<Sound> s : Sounds) {
        s->resetAllParams();
    }
}

/**
* deleteSound function
* Deletes a sound.
*
* @pre None
* @post A sound is deleted
*/
void SoundManager::deleteSound()
{
    if (rows > 5) {

        Sounds[rows - 1]->setSoundName("Empty");
        Sounds[rows - 1]->resetAllSteps();
        Sounds[rows - 1]->resetAllParams();

        --rows;
        notifyObservers(8);

    }
}

/**
* incrementSteps function
* Increments the number of steps.
*
* @pre None
* @post Number of steps is incremented
*/
void SoundManager::incrementSteps()
{
    if (StepAmount < 16) {
        ++StepAmount;

        for (std::shared_ptr<Sound> s : Sounds) {
            s->initNewStep();
        }

        notifyObservers(1);
        notifyObservers(32);
    }
}

/**
* decrementSteps function
* Decrements the number of steps.
*
* @pre None
* @post Number of steps is decremented
*/
void SoundManager::decrementSteps()
{
    if (StepAmount > 4) {
        --StepAmount;
        for (std::shared_ptr<Sound> s : Sounds) {
            s->deleteStep();
        }

        notifyObservers(2);
        notifyObservers(32);
    }
}

/**
* getSteps function
* Gets the number of steps.
*
* @return Number of steps
* @pre None
* @post None
*/
int SoundManager::getSteps()
{
    return StepAmount;
}

/**
* getPageCount function
* Gets the page count.
*
* @return Page count
* @pre None
* @post None
*/
int SoundManager::getPageCount()
{
    return Pages;
}

/**
* addPage function
* Adds a page.
*
* @pre None
* @post A page is added
*/
void SoundManager::addPage()
{
    if (Pages < 4) {
        Pages++;
        notifyObservers(10);
        notifyObservers(11);
        notifyObservers(33);
    }
}

/**
* deletePage function
* Deletes a page.
*
* @pre None
* @post A page is deleted
*/
void SoundManager::deletePage()
{

    if (Pages > 1) {
        Pages--;

        if (CurrentPage > Pages) {
            decrementCurrentPage();
        }

        notifyObservers(10);
        notifyObservers(12);
        notifyObservers(33);
    }
}

/**
* getPages function
* Gets the number of pages.
*
* @return Number of pages
* @pre None
* @post None
*/
int SoundManager::getPages() {
    return Pages;
}

/**
* getCurrentPage function
* Gets the current page.
*
* @return Current page
* @pre None
* @post None
*/
int SoundManager::getCurrentPage()
{
    return CurrentPage;
}

/**
* getNextSteps function
* Gets the next steps.
*
* @param page The page index
* @param index The step index
* @return Vector of Step pointers
* @pre None
* @post None
*/
std::vector<Step*> SoundManager::getNextSteps(int page, int index)
{
    CurrentColumn = index % StepAmount;
    CurrentPlayingPage = page;
    notifyObservers(4);
    return getStepColumn(page, CurrentColumn);
}

/**
* getStepColumn function
* Gets a step column.
*
* @param page The page index
* @param index The step index
* @return Vector of Step pointers
* @pre None
* @post None
*/
std::vector<Step*> SoundManager::getStepColumn(int page, int index)
{
    std::vector<Step*> Column;
    for (auto Sound : Sounds)
    {
        Column.push_back(Sound->getStepAt(page, index));
    }
    return Column;
}

/**
* Break function
* Notify the observers of a break.
*
* @pre None
* @post None
*/
void SoundManager::Break() { notifyObservers(5); }


/**
* Sets the status of the reverb effect.
* Updates the corresponding property in the global parameters with the provided status value.
* Notifies the observers about the change in the reverb status.
*
* @param s The new status of the reverb effect (true for active, false for inactive).
* @pre The SoundManager instance must be properly initialized.
* @post The reverb status property is updated in the global parameters, and observers are notified.
* @return None.
*
*/
void SoundManager::setReverbStatus(bool s)
{
    GlobalParameters->setProperty("Reverb", s, nullptr);
    notifyObservers(31);
}

/**
* getSounds function
* Gets the sounds.
*
* @return Vector of shared pointers to Sound objects
* @pre None
* @post None
*/
std::vector<std::shared_ptr<Sound>> SoundManager::getSounds()
{
    return Sounds;
}

/**
* getCurrentPlayingColumn function
* Gets the current playing column.
*
* @return Current playing column index
* @pre None
* @post None
*/
int SoundManager::getCurrentPlayingColumn()
{
    return CurrentColumn;
}

/**
* getCurrentPlayingPage function
* Gets the current playing page.
*
* @return Current playing page index
* @pre None
* @post None
*/
int SoundManager::getCurrentPlayingPage()
{
    return CurrentPlayingPage;
}

/**
* incrementCurrentPage function
* Increments the current page.
*
* @pre None
* @post Current page is incremented
*/
void SoundManager::incrementCurrentPage()
{
    if (CurrentPage < Pages) {
        ++CurrentPage;
        notifyObservers(13);
    }
}

/**
* decrementCurrentPage function
* Decrements the current page.
*
* @pre None
* @post Current page is decremented
*/
void SoundManager::decrementCurrentPage()
{
    if (CurrentPage > 1) {
        --CurrentPage;
        notifyObservers(14);
    }
}

/**
* changeToolTipStatus function
* Changes the tooltip status.
*
* @param status The new tooltip status
* @pre None
* @post Tooltip status is updated
*/
void SoundManager::changeToolTipStatus(bool status)
{
    toolTipStatus = status;
}

/**
* getToolTipStatus function
* Gets the tooltip status.
*
* @return Tooltip status
* @pre None
* @post None
*/
bool SoundManager::getToolTipStatus()
{
    return toolTipStatus;
}

/**
* getSoundAt function
* Gets a sound at a given index.
*
* @param index The index of the sound
* @return Pointer to Sound object
* @pre None
* @post None
*/
Sound* SoundManager::getSoundAt(int index)
{
    return Sounds[index].get();
}
