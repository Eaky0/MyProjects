/*
  ==============================================================================

    SoundLibrary.h

    This class holds the file paths of every instrument.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AbstractObservable.h"

class SoundLibrary : public AbstractObservable
{
public:
    SoundLibrary();
    void updateYourLib(juce::File file);
    void addSoundToList(juce::File file);
    std::vector<juce::File> getSoundList();
    ~SoundLibrary();

private:
    juce::File LibDirectory;
    std::vector<juce::File> Sounds;

};