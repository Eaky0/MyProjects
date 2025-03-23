/*
  ==============================================================================

    StepGridComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "StepGridComponent.h"

//==============================================================================

/**
* Constructor for StepGridComponent.
*
* Initializes the component with grid information and adds sound views and step views.
*
* @return None.
* @pre None.
* @post Component is initialized with grid information, sound views, and step views added.
* @author Atakan Kumas
*/
StepGridComponent::StepGridComponent()
{    
    setScrollBarsShown(true, false, true, true);

    addAndMakeVisible(GridInfo);
    addAndMakeVisible(contentComponent);
    setSize(450, 250);

    setViewedComponent(&contentComponent, false);
}

/**
* Destructor for StepGridComponent.
*
* Cleans up any resources associated with the component.
*
* @return None.
* @pre None.
* @post Component is destructed, releasing associated resources.
* @author Atakan Kumas
*/
StepGridComponent::~StepGridComponent()
{
    // No special cleanup required in the destructor
}

/**
* Paint function of StepGridComponent.
*
* Paints this component.
*
* @param g The Graphics context that must be used to do the drawing operations.
* @return None.
* @pre None.
* @post Component has been painted accordingly.
* @author Atakan Kumas
*/
void StepGridComponent::paint(juce::Graphics& g)
{
    // Fill the background with dark grey color and draw a rectangle around the component

    g.fillAll(juce::Colour(129, 164, 205));
    g.setColour(juce::Colour(219, 228, 238));
    g.drawRect(getLocalBounds(), 1.0f);
}

/**
* Resized function of StepGridComponent.
*
* Resizes child components of this component and performs layout for sound views and step views.
*
* @return None.
* @pre Window needs to be resized.
* @post Child components have been resized and layout has been performed accordingly.
* @author Atakan Kumas
*/
void StepGridComponent::resized()
{
    if (SoundM != nullptr) {
        int contentHeight = 25 + SoundM->getRows() * 50;

        GridInfo.setBounds(getLocalBounds().removeFromTop(25));

        contentComponent.setBounds(0, 25, getWidth(), contentHeight);

        juce::Rectangle<int> gridRect = contentComponent.getBounds().withTrimmedTop(25);

    
        for (int i = 0; i < SoundM->getRows(); i++) {
            StepGrid[i]->setBounds(gridRect.removeFromTop(50));
        }


    }



}


/**
 * setModels
 *
 * Sets the models for the StepGridComponent, initializing the necessary components and patterns.
 *
 * @param sound Pointer to the SoundManager instance.
 * @param play Pointer to the Player instance.
 * @param lib Pointer to the SoundLibrary instance.
 * @pre None
 * @post The StepGridComponent is initialized with the provided models, and all patterns are set and made visible or hidden as needed.
 * @return void
 */
void StepGridComponent::setModels(SoundManager* sound, Player * play, SoundLibrary * lib)
{
    GridInfo.setModels(sound);
    SoundLib.setModels(play, lib);

    SoundM.reset(sound);
    SoundM->addObserver(this);

    
    for (int i = 0; i < 20; i++) {
        StepPatternPanel* Pattern = new StepPatternPanel(sound->getSoundAt(i)->getSoundName(), i, &SoundLib);
        StepGrid.add(Pattern);

        if (i < 10) {
            contentComponent.addAndMakeVisible(Pattern);
        }
        else {
            contentComponent.addChildComponent(Pattern);
        }
    }

    for (int i = 0; i < 20; i++) {
        StepGrid[i]->setModels(sound);
    }

    RefreshPatterns();


}

/**
 * update
 *
 * Updates the StepGridComponent based on the provided observer ID.
 *
 * @param id The ID of the observer event.
 * @pre None
 * @post The StepGridComponent is refreshed and resized if the ID corresponds to an event requiring such actions.
 * @return void
 */
void StepGridComponent::update(int id)
{
    switch (id) {
    case 7:
    case 8:
        RefreshPatterns();
        resized();
        break;
    default:
        break;
    }
}


/**
 * RefreshPatterns
 *
 * Refreshes the visibility of the patterns in the StepGrid based on the number of rows in the SoundManager.
 *
 * @pre None
 * @post The visibility of patterns in the StepGrid is updated to match the number of rows in the SoundManager.
 * @return void
 */
void StepGridComponent::RefreshPatterns()
{
    for (int i = 0; i < StepGrid.size(); i++) {
        if (i < SoundM->getRows()) {
            StepGrid[i] -> setVisible(true);
        }
        else {
            StepGrid[i]->setVisible(false);
        }
    }
}



