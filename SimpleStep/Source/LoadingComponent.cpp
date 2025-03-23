/*
  ==============================================================================

    LoadingComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "LoadingComponent.h"

/**
* LoadingComponent
* Constructor that initializes the progress bar, status label, and logo image, and starts the initialization thread.
*
* @pre
* @post The progress bar and status label are initialized and made visible, and the initialization thread is started.
*/
LoadingComponent::LoadingComponent()
    : Thread("Initialization Thread"), progress(0.0), progressBar(progress)
{
    // Initialize the progress bar
    progressBar.setPercentageDisplay(true);
    progressBar.setColour(juce::ProgressBar::foregroundColourId, juce::Colour(0xFF3C79B5)); // Set progress bar color
    addAndMakeVisible(progressBar);

    // Initialize the status label
    statusLabel.setText("The program will start up soon...", juce::dontSendNotification);
    statusLabel.setJustificationType(juce::Justification::centred);
    statusLabel.setColour(juce::Label::textColourId, juce::Colours::white); // Set status text color
    addAndMakeVisible(statusLabel);

    // Load the logo image
    juce::File resourceDir;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    resourceDir = currentDir.getChildFile("resource");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    resourceDir = grandParentDir.getChildFile("resource");

#endif

    juce::File logoFile(resourceDir.getChildFile("logo.png").getFullPathName());
    logoImage = juce::ImageFileFormat::loadFrom(logoFile);

    // Start the initialization thread
    startThread();
}

/**
* ~LoadingComponent
* Destructor that stops the initialization thread.
*
* @pre
* @post The initialization thread is stopped.
*/
inline LoadingComponent::~LoadingComponent()
{
    stopThread(1000);
}

/**
* paint
* Paints the component, setting the background color and drawing the logo image.
*
* @param g The graphics context used for drawing.
* @pre
* @post The component's background is filled, and the logo image is drawn.
*/
inline void LoadingComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xFFA5C5E5)); // Set background color

    // Draw the logo image centered at the top with reduced size
    if (logoImage.isValid())
    {
        auto logoHeight = getHeight() / 1.1; // Reduce the logo height
        auto logoWidth = static_cast<int>(logoHeight * (static_cast<float>(logoImage.getWidth()) / logoImage.getHeight()));
        auto logoX = (getWidth() - logoWidth) / 2;
        auto logoY = 20; // Add some padding from the top
        g.drawImage(logoImage, logoX, logoY, logoWidth, logoHeight, 0, 0, logoImage.getWidth(), logoImage.getHeight());
    }
}

/**
* resized
* Resizes and positions the child components (progress bar and status label).
*
* @pre
* @post The progress bar and status label are resized and repositioned.
*/
inline void LoadingComponent::resized()
{
    auto area = getLocalBounds().reduced(20); // Reduce the area to make it smaller
    auto logoHeight = getHeight() / 4 + 40; // Adjust height to accommodate logo and padding
    area.removeFromTop(logoHeight); // Remove the logo area from the bounds
    statusLabel.setBounds(area.removeFromBottom(30)); // Position status label above the progress bar
    progressBar.setBounds(area.removeFromBottom(30)); // Position progress bar at the bottom
}

/**
* run
* Executes the initialization tasks in a separate thread, updating the progress bar and status label accordingly.
*
* @pre
* @post The progress bar and status label are updated as each initialization step is completed.
*/
inline void LoadingComponent::run()
{
    const int steps = 5;
    for (int i = 0; i < steps; ++i)
    {
        if (threadShouldExit())
            return;

        // Simulate work
        juce::Thread::sleep(500);

        // Update progress
        progress = (i + 1) / static_cast<double>(steps);

        // Update status text
        juce::String statusText;
        switch (i)
        {
        case 0: statusText = "Initializing Sound Manager..."; break;
        case 1: statusText = "Setting up IO Manager..."; break;
        case 2: statusText = "Loading Sound Library..."; break;
        case 3: statusText = "Configuring Player..."; break;
        case 4: statusText = "Finalizing Setup..."; break;
        }

        // Update progress bar and status label
        juce::MessageManager::callAsync([this, statusText]() {
            progressBar.repaint();
            statusLabel.setText(statusText, juce::dontSendNotification);
            });
    }

    // Notify main component that initialization is complete
    juce::MessageManager::callAsync([this]() {
        if (onInitializationComplete)
            onInitializationComplete();
        });
}
