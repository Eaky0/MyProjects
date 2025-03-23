/*
  ==============================================================================

    StepPatternPanel.h

    This class contains a sound and all the steps of one row.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once
#include "SoundView.h"
#include "StepView.h"
#include "SoundManager.h"
#include "Sound.h"

class StepPatternPanel : public juce::Component,  public AbstractObserver
{
public:
	StepPatternPanel(juce::String SoundName, int id, SoundLibraryView * SL);
    StepPatternPanel(juce::String SoundName, int id, SoundLibraryView* SL, int StepAmount, int PageAmount);


	~StepPatternPanel();

    void paint(juce::Graphics&) override;
    void resized() override;
    void setModels(SoundManager* sound);
    void update(int id) override;
    void update(juce::File file) override {};
    void update(std::vector<float> data) override {};

    void setSoundMessage();
    void nextPage();
    void prevPage();
    void RefreshStepVisibility();

private:
    SoundView SoundButton;
    juce::Array<juce::Array<std::shared_ptr<StepView>>> Steps;
    std::shared_ptr<SoundLibraryView> SoundLib;
    std::shared_ptr<SoundManager> SoundM;
    int PatternID;

};


