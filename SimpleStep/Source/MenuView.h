/*
  ==============================================================================

    MenuView.h

    This is the view of GlobalSettings.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlayClass.h"
#include "IOClass.h"
#include "GlobalSettingComponent.h"
#include "Utilities.h"
#include "CustomDirectoryComponent.h"

using namespace juce;

//==============================================================================
/*
*/
class MenuView : public juce::Component,
    public juce::Button::Listener, public AbstractObserver
{
public:
    void setModels(Player* audio, IOManager* io, GlobalSettingComponent *globalSettings);

    MenuView();
    ~MenuView() override;

    void paint(juce::Graphics& g) override;
    void resized() override;

    void buttonClicked(juce::Button* button) override; 
    void SpacebarPressed(const juce::KeyPress& key);

    void showAlertWindow();
    void update(int id) override;
    void update(juce::File file) override{};
    void update(std::vector<float> data) override {};

private:
    std::shared_ptr<Player> AudioManager;
    std::shared_ptr<IOManager> ioManager;
    GlobalSettingComponent *globalSettings;

    void openAddSoundDialog();
    void openLoadProjectDialog();
    void createComponents();
    void openFileMenu();
    void openClearMenu();
    void openSettingsMenu();

    juce::TextButton fileButton;
    juce::TextButton clearButton;
    std::unique_ptr<IconButton> recordButton;
    std::unique_ptr<IconButton> startStopButton;
    juce::TextButton settingsButton;
    juce::String mProjectName;
    PopUpMenuLookAndFeel PopUpMenuDesign;


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MenuView)
};

