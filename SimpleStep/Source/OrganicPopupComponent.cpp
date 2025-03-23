/*
  ==============================================================================

    OrganicPopupComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "OrganicPopupComponent.h"

/**
* OrganicPopupComponent
* Constructor for OrganicPopupComponent. Initializes the UI components and their properties.
*/

OrganicPopupComponent::OrganicPopupComponent()
{
    // Initialize the TooltipWindow
    addAndMakeVisible(tooltipWindow);

    // Algorithm type combo box
    algorithmLabel.setText("Algorithm Type:", juce::dontSendNotification);
    addAndMakeVisible(algorithmLabel);

    comboBox.addItem("None", 1);
    comboBox.addItem("Our Algorithm", 2);
    comboBox.addItem("Logarithm", 3);
    comboBox.setSelectedId(1); // Default to "None"
    addAndMakeVisible(comboBox);

    algorithmHelpButton.setButtonText("?");
    algorithmHelpButton.setTooltip("Algorithm Type:\n- None: No algorithm applied\n- Our Algorithm: Custom algorithm\n- Logarithm: Logarithmic changes");
    addAndMakeVisible(algorithmHelpButton);

    // Influence sounds text editor
    influenceLabel.setText("Influence Sounds:", juce::dontSendNotification);
    addAndMakeVisible(influenceLabel);

    textEditor.setInputFilter(new juce::TextEditor::LengthAndCharacterRestriction(15, "0123456789,all"), true);
    addAndMakeVisible(textEditor);

    influenceHelpButton.setButtonText("?");
    influenceHelpButton.setTooltip("Specify the sound IDs (e.g., 1,2,3) or type 'all' to influence all sounds.");
    addAndMakeVisible(influenceHelpButton);

    // Random change steps checkbox
    randomChangeLabel.setText("Random Change on Steps:", juce::dontSendNotification);
    addAndMakeVisible(randomChangeLabel);

    randomChangeCheckbox.setButtonText("Enable");
    addAndMakeVisible(randomChangeCheckbox);

    randomChangeHelpButton.setButtonText("?");
    randomChangeHelpButton.setTooltip("Enable this to allow random changes in steps, which may result in no changes.");
    addAndMakeVisible(randomChangeHelpButton);

    // Organic slider
    organicSliderLabel.setText("Adjust Strength of Changes:", juce::dontSendNotification);
    addAndMakeVisible(organicSliderLabel);

    organicSlider.setRange(0, 10, 1);
    organicSlider.setValue(0);
    organicSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    organicSlider.setPopupDisplayEnabled(true, true, this);
    organicSlider.setTextValueSuffix("");
    addAndMakeVisible(organicSlider);

    organicSliderHelpButton.setButtonText("?");
    organicSliderHelpButton.setTooltip("Use this slider to adjust \nhow strong the organic changes \nwill be.");
    addAndMakeVisible(organicSliderHelpButton);

    // Save changes checkbox
    saveChangesCheckbox.setButtonText("Save Changes");
    addAndMakeVisible(saveChangesCheckbox);

    // Apply button
    organicApplyButton.setButtonText("Apply");
    organicApplyButton.onClick = [this] { if (onApply) onApply(); };
    addAndMakeVisible(organicApplyButton);

    setSize(350, 340);

    // Apply color scheme
    applyColorScheme();
}

/**
* paint
* Draws the background of the component.
*
* @param g Graphics context used for drawing.
* @pre None
* @post The background of the component is painted.
*/

void OrganicPopupComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff4b7299)); // Background color similar to the app
}

/**
* resized
* Lays out the positions and sizes of the child components.
*
* @pre None
* @post The child components are resized and positioned.
*/

void OrganicPopupComponent::resized()
{
    auto area = getLocalBounds().reduced(10);
    int componentHeight = 30;

    auto algorithmArea = area.removeFromTop(componentHeight);
    algorithmLabel.setBounds(algorithmArea.removeFromLeft(150));
    comboBox.setBounds(algorithmArea.removeFromLeft(150).reduced(5));
    algorithmHelpButton.setBounds(algorithmArea.reduced(5));

    auto influenceArea = area.removeFromTop(componentHeight);
    influenceLabel.setBounds(influenceArea.removeFromLeft(150));
    textEditor.setBounds(influenceArea.removeFromLeft(150).reduced(5));
    influenceHelpButton.setBounds(influenceArea.reduced(5));

    auto randomChangeArea = area.removeFromTop(componentHeight);
    randomChangeLabel.setBounds(randomChangeArea.removeFromLeft(150));
    randomChangeCheckbox.setBounds(randomChangeArea.removeFromLeft(150).reduced(5));
    randomChangeHelpButton.setBounds(randomChangeArea.reduced(5));

    auto organicSliderArea = area.removeFromTop(componentHeight);
    organicSliderLabel.setBounds(organicSliderArea.removeFromLeft(150));
    organicSlider.setBounds(organicSliderArea.removeFromLeft(150).reduced(5));
    organicSliderHelpButton.setBounds(organicSliderArea.reduced(5));

    saveChangesCheckbox.setBounds(area.removeFromTop(componentHeight).reduced(5));
    organicApplyButton.setBounds(area.removeFromTop(componentHeight).reduced(5));
}

/**
* getOrganicSliderValue
* Gets the current value of the organic slider.
*
* @return The current value of the organic slider.
* @pre None
* @post The current value of the organic slider is returned.
*/

double OrganicPopupComponent::getOrganicSliderValue() const
{
    return organicSlider.getValue();
}

/**
* getSelectedAlgorithm
* Gets the selected algorithm from the combo box.
*
* @return The selected algorithm ID.
* @pre None
* @post The selected algorithm ID is returned.
*/

int OrganicPopupComponent::getSelectedAlgorithm() const
{
    return comboBox.getSelectedId();
}

/**
* getInfluenceSounds
* Gets the influence sounds input from the text editor.
*
* @return A string containing the influence sounds.
* @pre None
* @post The influence sounds input is returned.
*/

juce::String OrganicPopupComponent::getInfluenceSounds() const
{
    return textEditor.getText();
}

/**
* isRandomChangeEnabled
* Checks if the random change checkbox is enabled.
*
* @return True if the random change checkbox is enabled, false otherwise.
* @pre None
* @post The state of the random change checkbox is returned.
*/

bool OrganicPopupComponent::isRandomChangeEnabled() const
{
    return randomChangeCheckbox.getToggleState();
}

/**
* shouldSaveChanges
* Checks if the save changes checkbox is enabled.
*
* @return True if the save changes checkbox is enabled, false otherwise.
* @pre None
* @post The state of the save changes checkbox is returned.
*/

bool OrganicPopupComponent::shouldSaveChanges() const
{
    return saveChangesCheckbox.getToggleState();
}

/**
* applyColorScheme
* Applies the color scheme to the UI components.
*
* @pre None
* @post The color scheme is applied to the UI components.
*/

void OrganicPopupComponent::applyColorScheme()
{
    // Label colors
    algorithmLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    influenceLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    randomChangeLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    organicSliderLabel.setColour(juce::Label::textColourId, juce::Colours::white);

    // ComboBox color
    comboBox.setColour(juce::ComboBox::backgroundColourId, juce::Colour(0xff2e4a62));
    comboBox.setColour(juce::ComboBox::textColourId, juce::Colours::white);

    // TextEditor color
    textEditor.setColour(juce::TextEditor::backgroundColourId, juce::Colour(0xff2e4a62));
    textEditor.setColour(juce::TextEditor::textColourId, juce::Colours::white);

    // Buttons color
    algorithmHelpButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2e4a62));
    algorithmHelpButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    influenceHelpButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2e4a62));
    influenceHelpButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    randomChangeHelpButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2e4a62));
    randomChangeHelpButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    organicSliderHelpButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2e4a62));
    organicSliderHelpButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);

    organicApplyButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2e4a62));
    organicApplyButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
}
