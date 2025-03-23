/*
  ==============================================================================

    MainComponent.h

    This is the main view of the code and contains the subclasses of the main view.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "GridSettingComponent.h"
#include "PagesComponent.h"
#include "StepGridComponent.h"
#include "GraphComponent.h"
#include "GlobalSettingComponent.h"
#include "MenuView.h"
#include "Project.h"
#include "LoadingComponent.h"

//==============================================================================

class MainComponent : public juce::Component
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

    bool keyPressed(const juce::KeyPress& key) override;

    void showMainUI(); // Method to show the main UI

private:

    //==============================================================================
    GridSettingComponent Settings;
    StepGridComponent StepPattern;
    PagesComponent PageLayout;
    GraphComponent GraphView;
    GlobalSettingComponent GlobalSettings;
    MenuView Toolbar;
    std::unique_ptr<Project> Proj;

    std::unique_ptr<LoadingComponent> loadingComponent;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};


