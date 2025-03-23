/*
  ==============================================================================

    PagesComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PagesComponent.h"

//==============================================================================

/**
* Constructor for PagesComponent.
*
* Initializes the component with previous and next page buttons.
* Sets the initial current page and total page amount.
*
* @return None.
* @pre None.
* @post Component is initialized with buttons and page information set.
* @author Atakan Kumas
*/
PagesComponent::PagesComponent()
    : ToPreviousPage{ "", 0.5f, juce::Colour(62, 124, 177) },
    ToNextPage{ "", 0.0f, juce::Colour(62, 124, 177)}
{

    PageAmount.setFont(14.0f);
    PageAmount.setText("1", juce::dontSendNotification);
    PageAmount.setColour(juce::Label::textColourId, juce::Colours::white);
    PageAmount.setJustificationType(juce::Justification::centred);

    slash.setFont(14.0f);
    slash.setText("/", juce::dontSendNotification);
    slash.setColour(juce::Label::textColourId, juce::Colours::white);
    slash.setJustificationType(juce::Justification::centred);


    CurrentPage.setFont(14.0f);
    CurrentPage.setText("1", juce::dontSendNotification);
    CurrentPage.setColour(juce::Label::textColourId, juce::Colours::white);
    CurrentPage.setJustificationType(juce::Justification::centred);
    
    addAndMakeVisible(PageAmount);
    addAndMakeVisible(slash);
    addAndMakeVisible(CurrentPage);
    addAndMakeVisible(ToNextPage);
    addAndMakeVisible(ToPreviousPage);

    ToNextPage.addListener(this);
    ToPreviousPage.addListener(this);
}





/**
* Destructor for PagesComponent.
*
* Cleans up any resources associated with the component.
*
* @return None.
* @pre None.
* @post Component is destructed, releasing associated resources.
* @author Atakan Kumas
*/
PagesComponent::~PagesComponent()
{
    // No special cleanup required in the destructor
}

/**
* buttonClicked
* Handles button click events for navigation between pages in the SoundManager.
*
* @param button The button that was clicked.
*
* @pre SoundM must be initialized and contain valid Sound objects.
* @post Current page in SoundM may be incremented or decremented based on the button clicked.
*
*/
void PagesComponent::buttonClicked(juce::Button* button)
{
    if (button == &ToNextPage) {
        SoundM->incrementCurrentPage();
    }
    if (button == &ToPreviousPage) {
        SoundM->decrementCurrentPage();
    }
}

/**
* setModels
* Sets the SoundManager model for the PagesComponent.
*
* @param step Pointer to the SoundManager object.
*
* @pre None.
* @post SoundM is set to the provided SoundManager object and the PagesComponent is added as an observer.
*
*/
void PagesComponent::setModels(SoundManager* step)
{
    SoundM.reset(step);
    SoundM->addObserver(this);
}

/**
* Paint function of Pagecomponent
*
* Paints this component
*
* @return None.
* @pre None.
* @post Component has been accordingly
* @author Atakan Kumas
*/
void PagesComponent::paint(juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.fillAll(juce::Colour(129, 164, 205));
    g.setColour(juce::Colour(219, 228, 238));
    g.drawRect(getLocalBounds(), 1.0f);

    
}



/**
* Resized function of Pagecomponent
*
* Resizes child components of this component
*
* @return None.
* @pre Window needs to be resized
* @post Child components have been resized accordingly
* @author Atakan Kumas
*/
void PagesComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

    juce::FlexBox fb;
    fb.flexWrap = juce::FlexBox::Wrap::wrap;
    fb.justifyContent = juce::FlexBox::JustifyContent::center;
    fb.alignItems = juce::FlexBox::AlignItems::center;
    fb.flexDirection = juce::FlexBox::Direction::row;


    fb.items.add(juce::FlexItem(ToPreviousPage).withMinWidth(20.0f).withMinHeight(20.0f));
    fb.items.add(juce::FlexItem(CurrentPage).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(slash).withMinWidth(20.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(PageAmount).withMinWidth(50.0f).withMinHeight(50.0f));
    fb.items.add(juce::FlexItem(ToNextPage).withMinWidth(20.0f).withMinHeight(20.0f));
    fb.performLayout(getLocalBounds());

}



/**
* update
* Updates the GUI components based on the given ID.
* This function is called when changes occur in the SoundManager.
*
* @param id The ID indicating the type of update.
* @pre None.
* @post GUI components are updated accordingly.
* @return None.
*
*/
void PagesComponent::update(int id)
{
    switch (id) {
        // Update the number of pages
    case 10:
        PageAmount.setText(juce::String(SoundM->getPages()), juce::dontSendNotification);
        break;
        // Update the current page number
    case 14:
    case 13:
        CurrentPage.setText(juce::String(SoundM->getCurrentPage()), juce::dontSendNotification);
    default:
        break;
    }
    resized();
}
