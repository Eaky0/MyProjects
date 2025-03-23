/*
  ==============================================================================

    ReverbManager.h

    This is the class that manages the data streams for the reverb.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/
#pragma once

#include "Parameters.h"
#include <JuceHeader.h>


class ReverbManager {
public:
    ReverbManager();
    ~ReverbManager();
    void resetParam();
    juce::ValueTree* GetParams();
    void setRParam(RParam r, float newValue);
    float getRParam(RParam r);

private:
    juce::ValueTree * ReverbParameters;
};