/*
  ==============================================================================

    PagesPanel.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PagesPanel.h"

//==============================================================================

/**
* PagesPanel constructor.
* Initializes the PagesPanel with buttons for adjusting page amount.
*
* @pre None.
* @post The PagesPanel is initialized with buttons and labels.
* @return None.
*
*/
PagesPanel::PagesPanel()
    : Plus{ "", 0.75f, juce::Colour(62, 124, 177) },
    Minus{ "", 0.25f, juce::Colour(62, 124, 177) }
{
    setSize(75, 125);

    Plus.addListener(this);
    Minus.addListener(this);

    PageInfoText.setFont(20.0f);
    PageInfoText.setText("Pages", juce::dontSendNotification);
    PageInfoText.setColour(juce::Label::textColourId, juce::Colours::white);

    Amount.setText("1", juce::dontSendNotification);
    Amount.setColour(juce::Label::textColourId, juce::Colours::white);
    Amount.setJustificationType(juce::Justification::centred);

    addAndMakeVisible(PageInfoText);
    addAndMakeVisible(Plus);
    addAndMakeVisible(Amount);
    addAndMakeVisible(Minus);
}

/**
* PagesPanel destructor.
* Cleans up resources used by the PagesPanel.
*
* @pre None.
* @post Resources used by the PagesPanel are released.
* @return None.
*
*/
PagesPanel::~PagesPanel()
{
}

/**
 * Set the SoundManager model and add this component as an observer.
 *
 * @param step Pointer to the SoundManager instance.
 */
void PagesPanel::setModels(SoundManager* step)
{
    SoundM.reset(step);
    SoundM->addObserver(this);
}

/**
 * Handle button clicks for the Plus and Minus buttons.
 *
 * @param button Pointer to the clicked button.
 */
void PagesPanel::buttonClicked(juce::Button* button)
{
    if (button == &Plus) {
        SoundM->addPage();
    }
    else if (button == &Minus) {
        SoundM->deletePage();
    }

    Amount.setText(juce::String(SoundM->getPages()), juce::dontSendNotification);
}

/**
 * Update the component based on an integer ID.
 *
 * @param id The ID to update based on (not used currently).
 */
void PagesPanel::update(int id)
{
    switch (id) {
    case 33:
        changePageAmountPanel();
        break;
    }

    resized();
}

/**
 * Update the component based on a file.
 *
 * @param file The file to update based on (not used currently).
 */
void PagesPanel::update(juce::File file)
{
    // Implement this if you need to handle file updates
}

/**
* changePageAmountPanel
* Updates the page amount panel with the current number of pages.
*
* @pre The SoundManager instance must be initialized.
* @post The page amount panel is updated with the current number of pages.
* @return None.
*
*/
void PagesPanel::changePageAmountPanel()
{
    Amount.setText(juce::String(SoundM->getPages()), juce::dontSendNotification);
}

/**
 * Paint the background and border of the component.
 *
 * @param g The graphics context to use for painting.
 */
void PagesPanel::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(129, 164, 205)); // Background color
    g.setColour(juce::Colour(219, 228, 238)); // Border color
    g.drawRect(getLocalBounds(), 1.0f); // Draw border
}

/**
 * Lay out the child components using a FlexBox layout.
 */
void PagesPanel::resized()
{
    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexDirection = juce::FlexBox::Direction::column;

    fb.items.add(juce::FlexItem(PageInfoText).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(Plus).withMinWidth(20.0f).withMinHeight(20.0f));
    fb.items.add(juce::FlexItem(Amount).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(Minus).withMinWidth(20.0f).withMinHeight(20.0f));

    fb.performLayout(getLocalBounds());
}
