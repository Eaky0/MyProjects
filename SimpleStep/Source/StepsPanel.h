/*
  ==============================================================================

    StepsPanel.h

    This is the StepPanel class that shows a panel when a step is clicked and gives 
    the user the option to change values of that step.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundManager.h"

//==============================================================================
/*
*/
class StepsPanel : public juce::Component, public juce::Button::Listener, public AbstractObserver {
public:
    StepsPanel();
    ~StepsPanel();
    void paint(juce::Graphics& g) override;
    void resized() override;
    void setModels(SoundManager* step);
    void buttonClicked(juce::Button* button) override;
    void update(int id) override;
    void update(juce::File file) override {};
    void update(std::vector<float> data) override {};
    void changeStepAmountPanel();

private:
    std::shared_ptr<SoundManager> SoundM;
    juce::ArrowButton Plus;
    juce::ArrowButton Minus;
    juce::Label Amount;
    juce::Label StepInfoText;

};


