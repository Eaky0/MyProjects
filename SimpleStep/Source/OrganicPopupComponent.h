/*
  ==============================================================================

    OrganicPopupComponent.h

    A popup that displays options to apply organics to the sequence.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
 * OrganicPopupComponent
 * This component provides a user interface for applying organic changes to sound steps.
 */
class OrganicPopupComponent : public juce::Component
{
public:
    // Function to be called when the apply button is pressed
    std::function<void()> onApply;
    OrganicPopupComponent();
    /**
     * Destructor for OrganicPopupComponent.
     */
    ~OrganicPopupComponent() override = default;
    void paint(juce::Graphics& g) override;
    void resized() override;
    double getOrganicSliderValue() const;
    int getSelectedAlgorithm() const;
    juce::String getInfluenceSounds() const;
    bool isRandomChangeEnabled() const;
    bool shouldSaveChanges() const;

private:
    void applyColorScheme();

    // UI components
    juce::Label algorithmLabel;
    juce::ComboBox comboBox;
    juce::Label influenceLabel;
    juce::TextEditor textEditor;
    juce::Label randomChangeLabel;
    juce::ToggleButton randomChangeCheckbox;
    juce::Label organicSliderLabel;
    juce::Slider organicSlider;
    juce::TextButton organicApplyButton;
    juce::ToggleButton saveChangesCheckbox;

    juce::TextButton algorithmHelpButton;
    juce::TextButton influenceHelpButton;
    juce::TextButton randomChangeHelpButton;
    juce::TextButton organicSliderHelpButton;

    juce::TooltipWindow tooltipWindow;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OrganicPopupComponent)
};
