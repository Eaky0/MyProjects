#include "MainComponent.h"

//==============================================================================
/**
* MainComponent
* The main component of the application, responsible for displaying the loading screen initially and then switching to the main UI.
*
* @pre
* @post The loading component is shown initially, and the main UI is displayed after initialization.
*/
MainComponent::MainComponent()
{
    loadingComponent = std::make_unique<LoadingComponent>();
    addAndMakeVisible(*loadingComponent);

    loadingComponent->onInitializationComplete = [this]() {
        juce::MessageManager::callAsync([this]() { showMainUI(); });
        };

    setSize(700, 600);
}

/**
* ~MainComponent
* Destructor for MainComponent.
*
* @pre
* @post No special cleanup is required.
*/
MainComponent::~MainComponent()
{
    // No special cleanup required in the destructor
}

/**
* paint
* Paints the main component, filling the background with a dark grey color.
*
* @param g The graphics context used for drawing.
* @pre
* @post The component's background is filled with dark grey color.
*/
void MainComponent::paint(juce::Graphics& g)
{
    // Fill the background with dark grey color
    g.fillAll(juce::Colours::darkgrey);
}

/**
* resized
* Resizes and positions the child components.
*
* @pre
* @post The child components are resized and repositioned based on the current layout.
*/
void MainComponent::resized()
{
    auto area = getLocalBounds();

    if (loadingComponent)
    {
        loadingComponent->setBounds(area);
    }
    else
    {
        // Set bounds for Toolbar
        auto ToolbarHeight = 35;
        Toolbar.setBounds(area.removeFromTop(ToolbarHeight));

        // Set bounds for GlobalSettings
        auto GlobalSettingsHeight = 70;
        GlobalSettings.setBounds(area.removeFromTop(GlobalSettingsHeight));

        // Set bounds for PageLayout
        auto PageLayoutHeight = 50;
        PageLayout.setBounds(area.removeFromTop(PageLayoutHeight));

        // Set bounds for GraphView
        auto GraphViewHeight = 200;
        GraphView.setBounds(area.removeFromBottom(GraphViewHeight));

        // Set bounds for Settings
        auto SettingsWidth = getWidth() / 6;
        Settings.setBounds(area.removeFromLeft(SettingsWidth));

        // Set bounds for StepPattern
        auto StepPatternWidth = getWidth() - SettingsWidth;
        StepPattern.setBounds(area.removeFromRight(StepPatternWidth));
    }
}

/**
* keyPressed
* Handles key press events.
*
* @param key The key press event.
* @pre
* @post If the space key is pressed, the Toolbar's SpacebarPressed method is called.
* @return true if the space key is pressed, otherwise false.
*/
bool MainComponent::keyPressed(const juce::KeyPress& key)
{
    if (key == juce::KeyPress::spaceKey)
    {
        Toolbar.SpacebarPressed(key);
        return true;
    }
    return false;
}

/**
* showMainUI
* Displays the main user interface by removing the loading component and adding the main UI components.
*
* @pre The loading component should be displayed initially.
* @post The main UI components are made visible, and the layout is adjusted.
*/
void MainComponent::showMainUI()
{
    loadingComponent.reset(); // Remove the loading component

    // Add and make visible child components
    addAndMakeVisible(GlobalSettings);
    addAndMakeVisible(Settings);
    addAndMakeVisible(PageLayout);
    addAndMakeVisible(StepPattern);
    addAndMakeVisible(GraphView);
    addAndMakeVisible(Toolbar);

    Proj = std::make_unique<Project>();

    // Global parameters (i.e. Swing, reverb, ...)
    GlobalSettings.setModels(Proj.get()->getSoundManager(), Proj.get()->getIOmanager(), Proj.get()->getOrganicManager(), Proj->getReverbManager(), Proj.get()->getFilterManager());

    // Step Grid Settings (i.e. Pages, Steps, Rows)
    Settings.setModels(Proj->getSoundManager());

    // Managing of pages (i.e. < 2/3 >)
    PageLayout.setModels(Proj->getSoundManager());

    // The Step grid in all its glory!
    StepPattern.setModels(Proj->getSoundManager(), Proj->getPlayer(), Proj->getSoundLibrary().get());

    // Graphs that visualize audio
    GraphView.setModels(Proj->getPlayer());

    // Toolbar (i.e. File, Settings, Run, ...)
    Toolbar.setModels(Proj->getPlayer(), Proj->getIOmanager(), &GlobalSettings);

    Proj->startinitialise();

    DBG("hello");

    resized(); // Adjust the layout
}