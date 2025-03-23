/*
  ==============================================================================

    StepGridComponent.h

    This class contains all the rows and creates a grid layout.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundView.h"
#include "StepView.h"
#include "SoundLibraryView.h"
#include "GridInfoPanel.h"
#include "StepPatternPanel.h"

class StepGridComponent  : public juce::Viewport, public AbstractObserver
{
public:
    StepGridComponent();
    ~StepGridComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void setModels(SoundManager* sound, Player * play, SoundLibrary* lib);
    void update(int id) override;
    void update(juce::File file) override {};
    void update(std::vector<float> data) override {};

private:

    void RefreshPatterns();

    juce::Component contentComponent;

    juce::OwnedArray<StepPatternPanel> StepGrid;
    std::shared_ptr<SoundManager> SoundM;
    SoundLibraryView SoundLib;
    GridInfoPanel GridInfo;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StepGridComponent)
};
