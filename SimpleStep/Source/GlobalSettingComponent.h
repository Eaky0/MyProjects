/*
  ==============================================================================

    GlobalSettingComponent.h

    Contains the global settings view.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundManager.h"
#include "AbstractObserver.h"
#include "IOClass.h"
#include "OrganicManager.h"
#include "ReverbManager.h"
#include "SavedDataPopupComponent.h"
#include "FilterManager.h"
#include "Utilities.h"

//==============================================================================
/**
*/

class GlobalSettingComponent :
    public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::ComboBox::Listener,
    public AbstractObserver
{
public:
    GlobalSettingComponent();
    ~GlobalSettingComponent() override;

    void paint(juce::Graphics&) override;
    void resized() override;

    void setModels(SoundManager* sound, IOManager* IO, OrganicManager * organic, ReverbManager * reverb, FilterManager* filterM);
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    //void textEditorReturnKeyPressed(juce::TextEditor& editor) override;
    void comboBoxChanged(juce::ComboBox* comboBox) override;
    void changeToolTipStatus(bool status);
    bool areTooltipsEnabled() const { return showToolTips; };

    void update(int id) override;
    void update(juce::File file) override {};
    void update(std::vector<float> data) override {};

private:
    void createSwingComponents();
    void createOrganicComponents();
    void createBPMComponents();
    void createReverbComponents();
    void createRecentDropdownMenu();
    void createChangesButton();
    void createFilterComponents();
    void createMasterVolumeSlider();

    void changeReverbColor();
    void changeBPMText();

    void applyBPM();
    void hideComponents();
    void showOrganicPopup();
    void updatecontent();
    void showOrganicDataPopup(const juce::File dataFile);

    //the tooltip window that we'll use for showing info
    juce::TooltipWindow tooltipWindow;
    bool showToolTips = true;

    // bpm - textfield - min:1 - max:200
    juce::TextButton bpmButton;
    juce::Slider bpmEditor;
    //juce::TextButton bpmapplyButton;
    // swing - slider - min:0 - max:10
    juce::TextButton swingButton;
    juce::Slider swingSlider;
    juce::TextButton swingApplyButton;
    // reverb - button + Window
    juce::TextButton reverbButton;
    std::unique_ptr<juce::AlertWindow> reverbWindow;
    std::unique_ptr<juce::Component> reverbContainer;

    juce::Label RoomSizeLabel;
    juce::Slider RoomSizeSlider;

    juce::Label DampingLabel;
    juce::Slider DampingSlider;

    juce::Label DryLabel;
    juce::Slider DrySlider;

    juce::Label WetLabel;
    juce::Slider WetSlider;

    juce::Label WidthLabel;
    juce::Slider WidthSlider;

    // filters: low- and high-pass
    juce::TextButton filtersButton;
    std::unique_ptr<juce::AlertWindow> FilterSettings;
    std::unique_ptr <juce::Component> FilterContainer;
    //labels
    juce::Label lowPassLabel;
    juce::Label lowPassFreqLabel;
    juce::Label lowPassQLabel;
    juce::Label highPassLabel;
    juce::Label highPassFreqLabel;
    juce::Label highPassQLabel;

    juce::ToggleButton lowPassOnOffButton;
    juce::ToggleButton highPassOnOffButton;
    //frequency slider - min: - max:
    juce::Slider lowPassFreqSlider;
    juce::Slider highPassFreqSlider;
    //frequency slider - min: - max:
    juce::Slider lowPassQSlider;
    juce::Slider highPassQSlider;
    
    // organic - slider - min:0 - max:10
    juce::TextButton organicButton;
    juce::Slider organicSlider;
    juce::TextButton organicApplyButton;
    
    // recente generaties van organic - 3 items max
    juce::ComboBox recentDropdownMenu;
    
    // see changes button - button - open .txt
    juce::TextButton changesButton;

    //slider for the master volume
    juce::Slider masterVolumeSlider;
    juce::Label masterVolumeLabel;

    std::shared_ptr<SoundManager> SoundM;
    std::shared_ptr<IOManager> IOMan;
    std::shared_ptr<FilterManager> FilterM;
    std::shared_ptr<OrganicManager> OrgMan;
    std::shared_ptr<ReverbManager> RevMan;

    PopUpMenuLookAndFeel PopUpMenuDesign;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GlobalSettingComponent)

};