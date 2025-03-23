/*
  ==============================================================================

    GraphComponent.h

    Shows a graph when the sequence is playing.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PlayClass.h"
#include "AbstractObserver.h"
#include "Utilities.h"

//==============================================================================
/*
*/
class GraphComponent : public juce::Component, public AbstractObserver
{
public:
    GraphComponent();
    ~GraphComponent() override;

    void setModels(Player* audio);
    void update(int id) override {};
    void update(juce::File file) override {};
    void update(std::vector<float> data) override; // New update method

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    std::shared_ptr<Player> AudioManager;

    // ComboBox for selecting the graph type
    juce::ComboBox graphTypeComboBox;

    // Example data for the graphs
    std::vector<float> volumeData;
    std::vector<float> pitchData;

    PopUpMenuLookAndFeel PopUpMenuDesign;
    

    // Function to generate example data
    void generateExampleData();

    // Function to paint the graph
    void paintGraph(juce::Graphics& g);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(GraphComponent)
};
