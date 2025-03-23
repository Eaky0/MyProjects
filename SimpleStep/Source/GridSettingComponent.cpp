/*
  ==============================================================================

    GridSettingComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GridSettingComponent.h"

//==============================================================================
/**
* Constructor for GridSettingComponent.
*
* Initializes the component with step amount, page amount, and row amount components.
*
* @return None.
* @pre None.
* @post Component is initialized with child components added and visible.
* @author Atakan Kumas
*/
GridSettingComponent::GridSettingComponent()
{
    // Add and make visible child components
    addAndMakeVisible(StepAmount);
    addAndMakeVisible(PageAmount);
    addAndMakeVisible(RowAmount);
}

/**
* Destructor for GridSettingComponent.
*
* Cleans up any resources associated with the component.
*
* @return None.
* @pre None.
* @post Component is destructed, releasing associated resources.
* @author Atakan Kumas
*/
GridSettingComponent::~GridSettingComponent()
{
    // No special cleanup required in the destructor
}

/**
* getStepsPanel
* Retrieves a pointer to the StepsPanel.
*
* @param None.
* @pre None.
* @post None.
* @return A pointer to the StepsPanel.
*/
StepsPanel* GridSettingComponent::getStepsPanel()
{
    return &StepAmount;
}

/**
* getPagesPanel
* Retrieves a pointer to the PagesPanel.
*
* @param None.
* @pre None.
* @post None.
* @return A pointer to the PagesPanel.
*/
PagesPanel* GridSettingComponent::getPagesPanel()
{
    return &PageAmount;
}

/**
* getRowsPanel
* Retrieves a pointer to the RowsPanel.
*
* @param None.
* @pre None.
* @post None.
* @return A pointer to the RowsPanel.
*/
RowsPanel* GridSettingComponent::getRowsPanel()
{
    return &RowAmount;
}

/**
* setModels
* Sets the models for the StepsPanel, PagesPanel, and RowsPanel.
*
* @param sound A pointer to the SoundManager object.
* @pre None.
* @post Models are set for the StepsPanel, PagesPanel, and RowsPanel.
* @return None.
*/
void GridSettingComponent::setModels(SoundManager* sound)
{
    StepAmount.setModels(sound);
    PageAmount.setModels(sound);
    RowAmount.setModels(sound);
}


/**
* Paint function of GridSettingComponent.
*
* Paints this component.
*
* @param g The Graphics context that must be used to do the drawing operations.
* @return None.
* @pre None.
* @post Component has been painted accordingly.
* @author Atakan Kumas
*/
void GridSettingComponent::paint(juce::Graphics& g)
{

    
    g.setColour(juce::Colour(219, 228, 238));
    g.drawRect(getLocalBounds(), 1.0f);
}

/**
* Resized function of GridSettingComponent.
*
* Sets the bounds of child components using a grid layout.
*
* @return None.
* @pre Window needs to be resized.
* @post Child components have been resized and laid out accordingly using a grid layout.
* @author Atakan Kumas
*/
void GridSettingComponent::resized()
{
    // Set bounds for RowAmount
    auto area = getLocalBounds();
    RowAmount.setBounds(area.removeFromBottom(getHeight() / 3));

    // Create a grid layout
    juce::Grid grid;

    using Track = juce::Grid::TrackInfo;
    using Fr = juce::Grid::Fr;

    // Set up the grid layout with two columns
    grid.templateRows = { Track(Fr(1)) };
    grid.templateColumns = { Track(Fr(1)), Track(Fr(1)) };

    // Specify the items in the grid layout
    grid.items = { juce::GridItem(StepAmount), juce::GridItem(PageAmount) };

    // Perform layout using the grid layout
    grid.performLayout(area);
}
