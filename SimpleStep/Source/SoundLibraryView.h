/*
  ==============================================================================

    SoundLibraryView.h

    This class is responsible for displaying all the instruments.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once


#include <JuceHeader.h>
#include "SoundLibrary.h"
#include "Sound.h"
#include "PlayClass.h"
#include "Utilities.h"

class SoundLibraryView : juce::PopupMenu, juce::Button::Listener, public AbstractObserver
{
public:
    SoundLibraryView();

    void MakeVisible();
    void buttonClicked(juce::Button* button) override;

    void paint(juce::Graphics& g);

    ~SoundLibraryView();
    void setSelected(Sound* s);
    void setModels(Player * play, SoundLibrary * library);

    void update(juce::File file) override;
    void update(int id) override {};
    void update(std::vector<float> data) override {};

private:
    std::unique_ptr<Sound> SelectedSound;
    //std::shared_ptr<Player> PlayerModel;
    SoundLibrary * SoundLibraryModel;
    juce::StringArray Items;
    PopUpMenuLookAndFeel PopupMenuDesign;
};


