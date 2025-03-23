/*
  ==============================================================================

    SavedDataPopupComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "SavedDataPopupComponent.h"

/**
* SavedDataPopupComponent constructor
* Initializes the SavedDataPopupComponent with data loaded from a file and sets up the table for display.
*
* @param filePath The file path from which data is loaded
* @pre The file at the given filePath must exist and contain valid data
* @post The SavedDataPopupComponent is initialized with the data loaded from the file
*/

SavedDataPopupComponent::SavedDataPopupComponent(const juce::String& filePath)
{
    // Initialize the TooltipWindow
    addAndMakeVisible(tooltipWindow);

    // Load JSON data from the file
    loadDataFromFile(filePath);

    // Table configuration
    addAndMakeVisible(table);
    table.setModel(this);
    table.getHeader().addColumn("Manipulated", 1, 90);
    table.getHeader().addColumn("Sound", 2, 150);
    table.getHeader().addColumn("Page", 3, 50);
    table.getHeader().addColumn("Step", 4, 50);  // New Step column
    table.getHeader().addColumn("Status", 5, 70);
    table.getHeader().addColumn("Volume", 6, 70);
    table.getHeader().addColumn("Delay", 7, 70);
    table.getHeader().addColumn("Pitch", 8, 70);

    setSize(900, 400);  // Increased width to accommodate the graph

    // Apply color scheme
    applyColorScheme();
}

/**
* Paint function
* Paints the component and draws the graph.
*
* @param g The graphics context
* @pre None
* @post The component is painted and the graph is drawn
*/

void SavedDataPopupComponent::paint(juce::Graphics& g)
{
    // Fill background color
    g.fillAll(juce::Colour(0xff4b7299)); // Background color similar to the app

    // Draw the graph
    drawGraph(g);
}

/**
* Resized function
* Adjusts the size and position of child components when the component is resized.
*
* @pre None
* @post The child components are resized and repositioned
*/

void SavedDataPopupComponent::resized()
{
    auto bounds = getLocalBounds().reduced(10);

    // Divide the available width into table and graph sections
    auto tableBounds = bounds.removeFromLeft(600);  // Table on the left side
    auto graphBounds = bounds;  // Remaining area for the graph

    table.setBounds(tableBounds);

    // Leave some space between table and graph
    graphBounds.reduce(20, 20);  // Adjust the space as needed

    this->graphBounds = graphBounds;
}

/**
* GetNumRows function
* Returns the number of rows in the table model.
*
* @pre None
* @post None
* @return The number of rows in the table
*/

int SavedDataPopupComponent::getNumRows()
{
    // Get the number of rows in the table
    return static_cast<int>(tableData.size());
}

/**
* PaintRowBackground function
* Paints the background for each row in the table.
*
* @param g The graphics context
* @param rowNumber The index of the row to paint
* @param width The width of the row
* @param height The height of the row
* @param rowIsSelected Indicates if the row is selected
* @pre None
* @post The background for the row is painted
*/

void SavedDataPopupComponent::paintRowBackground(juce::Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    // Paint the background for each row
    auto alternateColour = getLookAndFeel().findColour(juce::ListBox::backgroundColourId)
        .interpolatedWith(getLookAndFeel().findColour(juce::ListBox::textColourId), 0.03f);
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);
    else if (rowNumber % 2)
        g.fillAll(alternateColour);
}

/**
* PaintCell function
* Paints the contents of each cell in the table.
*
* @param g The graphics context
* @param rowNumber The index of the row
* @param columnId The index of the column
* @param width The width of the cell
* @param height The height of the cell
* @param rowIsSelected Indicates if the row is selected
* @pre None
* @post The contents of the cell are painted
*/

void SavedDataPopupComponent::paintCell(juce::Graphics& g, int rowNumber, int columnId, int width, int height, bool)
{
    g.setColour(getLookAndFeel().findColour(juce::ListBox::textColourId));
    g.setFont(juce::Font(height * 0.7f));

    if (rowNumber < tableData.size())
    {
        const auto& rowData = tableData[rowNumber];
        juce::String text;

        switch (columnId)
        {
        case 1: text = rowData.manipulated; break;  // Handle new Manipulated column
        case 2: text = rowData.sound; break;
        case 3: text = rowData.page; break;
        case 4: text = rowData.step; break;  // Handle new Step column
        case 5: text = rowData.status; break;
        case 6: text = rowData.volume; break;
        case 7: text = rowData.delay; break;
        case 8: text = rowData.pitch; break;
        default: break;
        }

        g.drawText(text, 2, 0, width - 4, height, juce::Justification::centredLeft, true);
    }

    g.setColour(getLookAndFeel().findColour(juce::ListBox::backgroundColourId));
    g.fillRect(width - 1, 0, 1, height);
}

/**
* LoadDataFromFile function
* Loads JSON data from a file and populates the tableData vector.
*
* @param filePath The file path from which data is loaded
* @pre The file at the given filePath must exist and contain valid JSON data
* @post The tableData vector is populated with data loaded from the file
*/

void SavedDataPopupComponent::loadDataFromFile(const juce::String& filePath)
{
    juce::File inputFile(filePath);
    juce::String jsonString = inputFile.loadFileAsString();
    juce::var jsonData = juce::JSON::parse(jsonString);
    int changedsound = 0;
    int Xsound = 0;

    if (auto* jsonObj = jsonData.getDynamicObject())
    {

        for (auto& soundEntry : jsonObj->getProperties())
        {
            juce::String soundName = soundEntry.name.toString();
            if (auto* soundObj = soundEntry.value.getDynamicObject())
            {
                if (auto* pages = soundObj->getProperty("pages").getArray())
                {
                    for (int pageIndex = 0; pageIndex < pages->size(); ++pageIndex)
                    {
                        juce::String pageName = "Page " + juce::String(pageIndex + 1);
                        if (auto* steps = (*pages)[pageIndex].getDynamicObject()->getProperty(pageName).getArray())
                        {

                            if (!graphset)
                            {
                                graphset = true;
                                graph.resize(steps->size() * pages->size(), 0);
                            }

                            for (int stepIndex = 0; stepIndex < steps->size(); ++stepIndex)
                            {
                                if (auto* stepObj = steps->getReference(stepIndex).getDynamicObject())
                                {
                                    juce::String manipulated = stepObj->getProperty("Manipulated").toString() == "1" ? "manipulated" : "n-manipulated";
                                    juce::String status = stepObj->getProperty("Status").toString() == "1" ? "active step" : "inactive step";

                                    tableData.push_back({
                                        manipulated,
                                        soundName,
                                        pageName,
                                        "Step " + juce::String(stepIndex + 1),  // Set step number
                                        status,
                                        stepObj->getProperty("volume").toString(),
                                        stepObj->getProperty("Delay").toString(),
                                        stepObj->getProperty("pitch").toString()
                                        });
                                    if (stepObj->getProperty("Manipulated").toString() == "1")
                                    {
                                        graph[stepIndex * (pageIndex + 1)]++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            Xsound++;
        }
    }
    graph.push_back(Xsound);
}

/**
* ApplyColorScheme function
* Applies a color scheme to the table and its header.
*
* @pre None
* @post The color scheme is applied to the table and its header
*/

void SavedDataPopupComponent::applyColorScheme()
{
    // Set table background color
    table.setColour(juce::TableListBox::backgroundColourId, juce::Colour(0xff2e4a62));
    table.setColour(juce::TableListBox::textColourId, juce::Colours::white);

    // Set table header colors
    table.getHeader().setColour(juce::TableHeaderComponent::backgroundColourId, juce::Colour(0xff2e4a62));
    table.getHeader().setColour(juce::TableHeaderComponent::textColourId, juce::Colours::white);
    table.getHeader().setColour(juce::TableHeaderComponent::outlineColourId, juce::Colour(0xff2e4a62));
}

/**
* DrawGraph function
* Draws a graph representing the loaded data.
*
* @param g The graphics context
* @pre The graph vector must be populated with data
* @post The graph is drawn on the component
*/

void SavedDataPopupComponent::drawGraph(juce::Graphics& g)
{
    // Ensure there's data to plot
    if (graph.size() < 2) return;

    // Calculate dimensions for the graph
    int graphWidth = graphBounds.getWidth();
    int graphHeight = graphBounds.getHeight();

    // Determine the maximum y-value (last element in graph vector)
    int maxY = *std::max_element(graph.begin(), graph.end());
    int numPoints = graph.size() - 1;  // Number of points excluding maxY

    // Draw the x-axis
    g.setColour(juce::Colours::white);
    g.drawLine(graphBounds.getX(), graphBounds.getBottom(), graphBounds.getRight(), graphBounds.getBottom());

    // Draw the bars
    float barWidth = (float)graphWidth / numPoints;
    for (int i = 0; i < numPoints; ++i)
    {
        int value = graph[i];
        float barHeight = (float)value / maxY * graphHeight;

        // Determine the color based on the value
        juce::Colour barColor = (value == 0) ? juce::Colours::grey.withAlpha(0.5f) : juce::Colour(0xff5ad7a4);

        // Draw the bar
        g.setColour(barColor);
        g.fillRect(graphBounds.getX() + i * barWidth, graphBounds.getBottom() - barHeight, barWidth, barHeight);

        // Draw the text label on each bar
        juce::String labelText = juce::String(value);
        g.setColour(juce::Colours::white);
        g.setFont(juce::Font(12.0f));  // Adjust font size as needed
        g.drawText(labelText, graphBounds.getX() + i * barWidth, graphBounds.getBottom() - barHeight - 20, barWidth, 20, juce::Justification::centred);
    }

    // Draw the y-axis (only positive values)
    g.drawLine(graphBounds.getX(), graphBounds.getBottom(), graphBounds.getX(), graphBounds.getY());

    // Draw the maxY value as text on the left side
    juce::String maxYText = "max changeable sounds: " + juce::String(maxY);
    g.drawText(maxYText, graphBounds.getX() - 90, graphBounds.getY() - graphHeight / 2 - 15, 300, graphHeight, juce::Justification::centred, true);

    // Draw the x-axis label for max step
    juce::String maxStepLabel = "max step: " + juce::String(numPoints);
    g.drawText(maxStepLabel, graphBounds.getX() + graphWidth / 4, graphHeight + 30, 100, 20, juce::Justification::centred, true);

    graphset = false;
}
