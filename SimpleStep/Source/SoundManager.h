/*
  ==============================================================================

    SoundManager.h

    This class is responsible for the general logic of incrementing pages and steps. 
    It is also responsible for changing and handing out data to other classes.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "Sound.h"

#pragma once

class SoundManager : public AbstractObservable
{
public:
	SoundManager();
	~SoundManager();
    void incrementRows();
    void decrementRows();
    int getRows();

    int getPageCount();

    float getGParam(Gparam Param);
    void setGParam(float newValue, Gparam Param);


    void addNewSound();
    void resetAllSteps();
    void resetAllSounds();
    void resetAllSettings();
    void deleteSound();

    void AddStepColumn();
    void DeleteStepColumn();

    void incrementSteps();
    void decrementSteps();
    int getSteps();

    void addPage();
    void deletePage();

    int getPages();
    int getCurrentPage();

    std::vector<Step*> getNextSteps(int page, int index);
    std::vector<std::shared_ptr<Sound>> getSounds();
    std::vector<Step*> getStepColumn(int page, int index);

    void Break();
    bool isReverbed() { return GlobalParameters->getProperty("Reverb"); }
    void setReverbStatus(bool s);

    int getCurrentPlayingColumn();
    int getCurrentPlayingPage();

    void incrementCurrentPage();
    void decrementCurrentPage();

    void changeToolTipStatus(bool status);
    bool getToolTipStatus();


    Sound* getSoundAt(int index);

private:
    int StepAmount = 16;
    int Pages = 1;
    int CurrentPage = 1;
    std::vector<std::shared_ptr<Sound>> Sounds;
    int rows = 10;
    int CurrentColumn;
    int CurrentPlayingPage;
    bool toolTipStatus = false;
    juce::ValueTree * GlobalParameters;

};

