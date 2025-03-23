/*
  ==============================================================================

    SavedDataPopupComponent.h

    A popup that shows the organics in a table with a graph.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
class SavedDataPopupComponent : public juce::Component, public juce::TableListBoxModel
{
public:
    SavedDataPopupComponent::SavedDataPopupComponent(const juce::String& filePath);

    /**
    * SavedDataPopupComponent destructor
    * Default destructor for SavedDataPopupComponent
    */
    SavedDataPopupComponent::~SavedDataPopupComponent() = default;
    void SavedDataPopupComponent::paint(juce::Graphics& g);
    void SavedDataPopupComponent::resized();
    int SavedDataPopupComponent::getNumRows();
    void SavedDataPopupComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected);
    void paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool /*rowIsSelected*/) override;

private:
    struct RowData
    {
        juce::String manipulated;  // New manipulated field
        juce::String sound;
        juce::String page;
        juce::String step;  // New step field
        juce::String status;
        juce::String volume;
        juce::String delay;
        juce::String pitch;
    };
    void loadDataFromFile(const juce::String& filePath);
    void applyColorScheme();
    void drawGraph(juce::Graphics& g);

    std::vector<int> graph;
    juce::TableListBox table;
    std::vector<RowData> tableData;
    juce::TooltipWindow tooltipWindow;
    juce::Rectangle<int> graphBounds; 
    bool graphset = false;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SavedDataPopupComponent)
};
