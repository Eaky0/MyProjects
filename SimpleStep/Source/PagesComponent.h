/*
  ==============================================================================

    PagesComponent.h

    Component to show the current page

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundManager.h"

//==============================================================================
/*
*/
class PagesComponent  : public juce::Component, juce::Button::Listener, public AbstractObserver
{
public:
    PagesComponent();
    ~PagesComponent() override;

    void buttonClicked(juce::Button* button) override;

    void setModels(SoundManager* step);
    void update(int id) override;
    void update(juce::File file) override {};
    void update(std::vector<float> data) override {};

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    std::shared_ptr<SoundManager> SoundM;
    juce::Label PageAmount;
    juce::Label slash;
    juce::Label CurrentPage;
    juce::ArrowButton ToPreviousPage;
    juce::ArrowButton ToNextPage;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PagesComponent)
};
