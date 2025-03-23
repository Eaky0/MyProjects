/*
  ==============================================================================

    LoadingComponent.h

    This component displays a loading screen, and once the program is ready, it displays the main program interface.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

/**
* LoadingComponent
* A component that displays a progress bar and status label while performing initialization tasks in a separate thread.
*
* @pre The logo image file should exist at the specified path.
* @post The progress bar and status label are updated during initialization, and a callback is triggered upon completion.
*/
class LoadingComponent : public juce::Component, public juce::Thread
{
public:
    LoadingComponent();
    ~LoadingComponent();
    void paint(juce::Graphics& g) override;
    void resized() override;
    void run() override;
    std::function<void()> onInitializationComplete;
private:
    juce::ProgressBar progressBar;
    juce::Label statusLabel;
    juce::Image logoImage;
    double progress;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoadingComponent)
};
