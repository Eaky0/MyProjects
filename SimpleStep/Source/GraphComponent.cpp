/*
  ==============================================================================

    GraphComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "GraphComponent.h"

/**
* GraphComponent Constructor
* Initializes the ComboBox for selecting graph types and generates example data.
*
* @param None.
* @pre None.
* @post ComboBox is initialized with default settings and example data is generated.
* @return None.
*/
GraphComponent::GraphComponent()
{
    // Initialize the ComboBox
    graphTypeComboBox.addItem("No Graph", 1);
    graphTypeComboBox.addItem("Volume", 2);
    graphTypeComboBox.addItem("Pitch", 3);
    graphTypeComboBox.setColour(juce::ComboBox::backgroundColourId, juce::Colours::white);
    graphTypeComboBox.setColour(juce::ComboBox::textColourId, juce::Colours::black);
    graphTypeComboBox.setColour(juce::ComboBox::arrowColourId, juce::Colours::black);
    graphTypeComboBox.setLookAndFeel(&PopUpMenuDesign);

    graphTypeComboBox.setSelectedId(1); // Default to "No Graph"
    graphTypeComboBox.onChange = [this] { repaint(); }; // Repaint when the selection changes
    addAndMakeVisible(graphTypeComboBox);

    // Generate example data
    generateExampleData();
}

/**
* GraphComponent Destructor
* Cleans up any resources associated with the GraphComponent.
*
* @param None.
* @pre None.
* @post GraphComponent is destructed, releasing associated resources.
* @return None.
*/
GraphComponent::~GraphComponent()
{
    setLookAndFeel(nullptr);
}

/**
* setModels
* Sets the model for the GraphComponent.
*
* @param audio Pointer to the Player object.
* @pre None.
* @post Model for the GraphComponent is set.
* @return None.
*/
void GraphComponent::setModels(Player* audio)
{
    AudioManager.reset(audio);
    audio->addObserver(this);
}

/**
* update (vector<float> version)
* Updates the GraphComponent with a vector of float data.
*
* @param data Vector containing float data.
* @pre None.
* @post GraphComponent is updated based on the provided float data.
* @return None.
*/
void GraphComponent::update(std::vector<float> data)
{
    DBG("hello");

    // Validate data size and values
    if (data.size() >= 2)
    {
        float volumeValue = (data[0] >= 0 && data[0] <= 100) ? data[0] : 0.0f;
        float pitchValue = (data[1] >= -6 && data[1] <= 6) ? data[1] : 0.0f;

        // Update volume data
        if (volumeData.size() >= 10)
        {
            volumeData.erase(volumeData.begin()); // Remove the oldest value
        }
        volumeData.push_back(volumeValue); // Add the new volume value

        // Update pitch data
        if (pitchData.size() >= 10)
        {
            pitchData.erase(pitchData.begin()); // Remove the oldest value
        }
        pitchData.push_back(pitchValue); // Add the new pitch value

        repaint();
    }
}

/**
* paint
* Paints the GraphComponent.
*
* @param g Reference to the Graphics object for drawing.
* @pre None.
* @post GraphComponent is painted with appropriate graph data.
* @return None.
*/
void GraphComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(129, 164, 205));
    g.setColour(juce::Colour(219, 228, 238));
    g.drawRect(getLocalBounds(), 1.0f);

    paintGraph(g);
}

/**
* resized
* Resizes the GraphComponent.
*
* @param None.
* @pre None.
* @post GraphComponent is resized to fit the available space.
* @return None.
*/
void GraphComponent::resized()
{
    graphTypeComboBox.setBounds(10, 10, getWidth() - 20, 30);
}

/**
* generateExampleData
* Generates example data for the GraphComponent.
*
* @param None.
* @pre None.
* @post Example data for volume and pitch is generated.
* @return None.
*/
void GraphComponent::generateExampleData()
{
    volumeData = { 10.0f, 23.0f, 15.0f, 37.0f, 28.0f }; // Example volume data in the range 0-100
    pitchData = { -1.0f, 2.0f, 0.0f, -3.0f, 1.0f }; // Example pitch data in the range -6 to 6
}

/**
* paintGraph
* Paints the graph based on the selected graph type.
*
* @param g Reference to the Graphics object for drawing.
* @pre None.
* @post Graph is painted with appropriate data based on the selected graph type.
* @return None.
*/
void GraphComponent::paintGraph(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(10, 60); // Adjusted the reduction to add more space

    g.setColour(juce::Colours::white);
    g.drawRect(bounds);

    int selectedGraph = graphTypeComboBox.getSelectedId();
    const std::vector<float>* data = nullptr;
    float yScale = 1.0f;

    switch (selectedGraph)
    {
    case 1:
        // No Graph selected
        return;
    case 2:
        data = &volumeData;
        yScale = 100.0f; // Volume range is 0-100
        break;
    case 3:
        data = &pitchData;
        yScale = 12.0f; // Pitch range is -6 to 6, total range is 12
        break;
    default:
        return;
    }

    if (data != nullptr && !data->empty())
    {
        if (data->size() == 1) {
            g.drawText("Insufficient data", bounds, juce::Justification::centred);
            return;
        }

        float stepX = bounds.getWidth() / static_cast<float>(data->size() - 1);
        float stepY = bounds.getHeight() / yScale;

        juce::Path graphPath;
        float startY = selectedGraph == 3 ? bounds.getBottom() - (data->at(0) + 6.0f) * stepY : bounds.getBottom() - data->at(0) * stepY;
        graphPath.startNewSubPath(bounds.getX(), startY);

        for (size_t i = 1; i < data->size(); ++i)
        {
            float x = bounds.getX() + i * stepX;
            float y = selectedGraph == 3 ? bounds.getBottom() - (data->at(i) + 6.0f) * stepY : bounds.getBottom() - data->at(i) * stepY;
            graphPath.lineTo(x, y);

            // Draw value labels
            g.setColour(juce::Colours::black);
            g.drawText(juce::String(data->at(i), 1), x - 10, y - 20, 40, 20, juce::Justification::centred);
        }

        g.strokePath(graphPath, juce::PathStrokeType(2.0f));
    }
}
