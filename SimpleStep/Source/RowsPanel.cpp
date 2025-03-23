/*
  ==============================================================================

    RowsPanel.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RowsPanel.h"

//==============================================================================

/**
* RowsPanel
* Constructor for the RowsPanel class.
* Initializes the UI components and sets their properties.
*
* @pre None.
* @post Initializes the RowsPanel UI components.
*
*/
RowsPanel::RowsPanel() : Plus{ "", 0.0f, juce::Colour(62, 124, 177) }, Minus{ "", 0.5f, juce::Colour(62, 124, 177) }
{
    setSize(150, 75);

    Plus.addListener(this);
    Minus.addListener(this);

    RowInfoText.setFont(20.0f);
    RowInfoText.setText("Rows", juce::dontSendNotification);
    RowInfoText.setColour(juce::Label::textColourId, juce::Colours::white);

    Amount.setText("10", juce::dontSendNotification);
    Amount.setColour(juce::Label::textColourId, juce::Colours::white);
    Amount.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(RowInfoText);
    addAndMakeVisible(Minus);
    addAndMakeVisible(Amount);
    addAndMakeVisible(Plus);
}

/**
* ~RowsPanel
* Destructor for the RowsPanel class.
*
* @pre None.
* @post None.
*
*/
RowsPanel::~RowsPanel()
{
}

/**
* buttonClicked
* Handles button clicks on the RowsPanel.
*
* @param button The button that was clicked.
* @pre None.
* @post Modifies the sound manager based on the button clicked.
*
*/
void RowsPanel::buttonClicked(juce::Button* button)
{
    if (button == &Plus) {
        SoundM->addNewSound();

        Amount.setText(juce::String(SoundM->getRows()), juce::dontSendNotification);
        if (Amount.getText() == "20") {
            Plus.setAccessible(false);
        }
        else {
            Plus.setAccessible(true);
        }
    }

    if (button == &Minus) {
        SoundM->deleteSound();

        Amount.setText(juce::String(SoundM->getRows()), juce::dontSendNotification);
        if (Amount.getText() == "5") {
            Minus.setAccessible(false);
        }
        else {
            Minus.setAccessible(true);
        }
    }
}

/**
* setModels
* Sets the sound manager for the RowsPanel.
*
* @param sound The sound manager to set.
* @pre None.
* @post Sets the sound manager for the RowsPanel.
*
*/
void RowsPanel::setModels(SoundManager* sound)
{
    SoundM.reset(sound);
    SoundM->addObserver(this);
}

/**
* update
* Updates the RowsPanel based on changes.
*
* @param id The ID of the update.
* @pre None.
* @post None.
*
*/
void RowsPanel::update(int id)
{
    switch (id) {
    case 34:
        changeRowAmountPanel();
        break;
    }
}

/**
* Updates the label displaying the number of rows in the panel.
* Retrieves the current number of rows from the associated SoundManager and updates the label accordingly.
*
* @pre The SoundManager instance associated with the panel must be valid.
* @post The label displaying the number of rows is updated.
* @return None.
*
*/
void RowsPanel::changeRowAmountPanel()
{
    Amount.setText(juce::String(SoundM->getRows()), juce::dontSendNotification);
}


/**
* paint
* Renders the RowsPanel component.
*
* @param g The graphics context to render.
* @pre None.
* @post Renders the RowsPanel component.
*
*/
void RowsPanel::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(129, 164, 205));
    g.setColour(juce::Colour(219, 228, 238));
    g.drawRect(getLocalBounds(), 1.0f);
}

/**
* resized
* Called when the RowsPanel is resized.
*
* @pre None.
* @post Adjusts the layout of RowsPanel components.
*
*/
void RowsPanel::resized()
{
    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexDirection = juce::FlexBox::Direction::row;

    fb.items.add(juce::FlexItem(RowInfoText).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(Minus).withMinWidth(20.0f).withMinHeight(20.0f));
    fb.items.add(juce::FlexItem(Amount).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(Plus).withMinWidth(20.0f).withMinHeight(20.0f));

    fb.performLayout(getLocalBounds());
}
