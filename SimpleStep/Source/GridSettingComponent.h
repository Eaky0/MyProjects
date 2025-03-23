/*
  ==============================================================================

    GridSettingComponent.h

    This class bundles the general utility components for the step sequencer.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "StepsPanel.h"
#include "PagesPanel.h"
#include "RowsPanel.h"
#include "StepGridComponent.h"

//==============================================================================
/*
*/
class GridSettingComponent  : public juce::Component
{
public:
    GridSettingComponent();
    ~GridSettingComponent() override;

    StepsPanel* getStepsPanel();
    PagesPanel* getPagesPanel();
    RowsPanel* getRowsPanel();

    void setModels(SoundManager * sound);
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    StepsPanel StepAmount;
    PagesPanel PageAmount;
    RowsPanel RowAmount;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GridSettingComponent)
};
