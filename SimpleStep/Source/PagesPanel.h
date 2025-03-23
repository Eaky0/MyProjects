/*
  ==============================================================================

    PagesPanel.h

    This is a panel that gives you the option to manipulate the number of pages.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundManager.h"

//==============================================================================
/*
*/
class PagesPanel : public juce::Component, public juce::Button::Listener, public AbstractObserver {
public:
    PagesPanel();
    ~PagesPanel();

    void setModels(SoundManager* step);

    void buttonClicked(juce::Button* button) override;
    
    void update(int id) override;
    void update(juce::File file) override;
    void update(std::vector<float> data) override {};
    void changePageAmountPanel();


    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    std::shared_ptr<SoundManager> SoundM;

    juce::ArrowButton Plus;
    juce::ArrowButton Minus;
    juce::Label Amount;
    juce::Label PageInfoText;
};
