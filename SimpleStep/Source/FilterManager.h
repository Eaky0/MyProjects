/*
  ==============================================================================

    FilterManager.h

    Is responsible for handling filter changes such as high and low pass.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include "Parameters.h"
#include "JuceHeader.h"

class FilterManager {
public:
    FilterManager();
    ~FilterManager() = default;

    void resetParam();
    juce::ValueTree& getParams();
    void setFParam(FParam filterParam, float newValue);
    float getFParam(FParam filterParam) const;
    void setFilterStatus(Gparam filter, bool status);
    bool getLowPassStatus() const;
    bool getHighPassStatus() const;

private:
    juce::ValueTree filterParameters;
    bool lowPassActive = false;
    bool highPassActive = false;
};