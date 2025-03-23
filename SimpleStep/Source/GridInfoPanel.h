/*
  ==============================================================================

    GridInfoPanel.h

    Display the step values on the sequencer.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundManager.h"
#include "AbstractObserver.h"

//==============================================================================

class GridInfoPanel : public juce::Component, public AbstractObserver
{
public:
    GridInfoPanel();
    ~GridInfoPanel();

    void ColourizeCurrentStep();

    void UnColourizeCurrentStep();

    void ReorganizeStepNumbers();

    void setModels(SoundManager* sound);

    void paint(juce::Graphics& g) override;
    void resized() override;

    void update(int id) override;
    void update(juce::File file) override {};
    void update(std::vector<float> data) override {};
    void nextPage();
    void prevPage();

private:
    std::shared_ptr<SoundManager> SoundM;
    juce::Label SoundText;
    juce::Array<juce::Array<std::shared_ptr<juce::Label>>> StepNumbers;



};
