/*
  ==============================================================================

    RowsPanel.h

    This is the visual view of the row buttons. These row buttons ensure that when pressed, they change the number of rows.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundManager.h"

//==============================================================================
/*
*/
class RowsPanel : public juce::Component, public juce::Button::Listener, public AbstractObserver {
public:
    RowsPanel();
    ~RowsPanel();

    void buttonClicked(juce::Button* button) override;
    void setModels(SoundManager* sound);

    void update(int id) override;
    void update(juce::File file) override {};
    void update(std::vector<float> data) override {};
    void changeRowAmountPanel();


    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    juce::ArrowButton Plus;
    juce::ArrowButton Minus;
    juce::Label Amount;
    juce::Label RowInfoText;
    std::shared_ptr<SoundManager> SoundM;
};
