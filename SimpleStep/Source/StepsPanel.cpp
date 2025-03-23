/*
  ==============================================================================

    StepsPanel.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "StepsPanel.h"

//==============================================================================

/**
 * Constructor for the StepsPanel class.
 * Initializes the panel with default values and sets up the UI components.
 */
StepsPanel::StepsPanel() : Plus{ "", 0.75f, juce::Colour(62, 124, 177) }, Minus{ "", 0.25f, juce::Colour(62, 124, 177) }
{
    setSize(75, 125);
    StepInfoText.setFont(20.0f);
    StepInfoText.setText("Steps", juce::dontSendNotification);
    StepInfoText.setColour(juce::Label::textColourId, juce::Colours::white);

    Amount.setText("16", juce::dontSendNotification);
    Amount.setColour(juce::Label::textColourId, juce::Colours::white);
    Amount.setJustificationType(juce::Justification::centred);

    Plus.addListener(this);
    Minus.addListener(this);


    addAndMakeVisible(StepInfoText);
    addAndMakeVisible(Plus);
    addAndMakeVisible(Amount);
    addAndMakeVisible(Minus);

  
}

/**
 * Destructor for the StepsPanel class.
 * Cleans up resources used by the panel.
 */
StepsPanel::~StepsPanel()
{
}

/**
 * Paints the StepsPanel component.
 *
 * @param g The Graphics object used for drawing.
 * @pre The graphics context is ready for drawing.
 * @post The StepsPanel component is painted.
 */
void StepsPanel::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(129, 164, 205));
    g.setColour(juce::Colour(219, 228, 238));
    g.drawRect(getLocalBounds(), 1.0f);
}

/**
 * Resizes and arranges the components within the StepsPanel.
 *
 * @pre The component is resized.
 * @post The child components are laid out according to the new size.
 */
void StepsPanel::resized()
{
    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexDirection = juce::FlexBox::Direction::column;

    fb.items.add(juce::FlexItem(StepInfoText).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(Plus).withMinWidth(20.0f).withMinHeight(20.0f));
    fb.items.add(juce::FlexItem(Amount).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(Minus).withMinWidth(20.0f).withMinHeight(20.0f));

    fb.performLayout(getLocalBounds());
}


/**
 * Sets the SoundManager model for the StepsPanel.
 *
 * @param step A pointer to the SoundManager object.
 * @pre The SoundManager object is created.
 * @post The StepsPanel observes the SoundManager for changes.
 */
void StepsPanel::setModels(SoundManager* step)
{
    SoundM.reset(step);
    SoundM->addObserver(this);
}

/**
 * Handles button click events for the StepsPanel.
 *
 * @param button A pointer to the clicked button.
 * @pre A button is clicked.
 * @post The step amount is incremented or decremented, and the display is updated.
 */
void StepsPanel::buttonClicked(juce::Button* button)
{

    if (button == &Plus) {
        
        SoundM->incrementSteps();

        Amount.setText(juce::String(SoundM->getSteps()), juce::dontSendNotification);
        if (Amount.getText() == "16") {
            Plus.setAccessible(false);
        }
        else {
            Plus.setAccessible(true);
        }
    }

    if (button == &Minus) {
        SoundM->decrementSteps();
        Amount.setText(juce::String(SoundM->getSteps()), juce::dontSendNotification);
        if (Amount.getText() == "4") {
            Minus.setAccessible(false);
        }
        else {
            Minus.setAccessible(true);
        }

    }


}

/**
* Updates the StepsPanel based on the notification ID.
* If the notification ID is 32, it calls the function to change the step amount panel.
* After updating, it resizes the panel.
*
* @param id The ID of the notification.
* @pre The StepsPanel instance must be properly initialized.
* @post The StepsPanel is updated according to the notification ID.
* @return None.
*
*/
void StepsPanel::update(int id)
{
    switch (id) {
    case 32:
        changeStepAmountPanel();
        break;
    }

    resized();
}

/**
* Changes the displayed step amount on the panel.
* Retrieves the current step amount from the SoundManager and updates the displayed text.
*
* @pre The StepsPanel instance must be properly initialized, and SoundManager must be set.
* @post The displayed step amount on the panel is updated.
* @return None.
*
*/
void StepsPanel::changeStepAmountPanel()
{
    Amount.setText(juce::String(SoundM->getSteps()), juce::dontSendNotification);
}


