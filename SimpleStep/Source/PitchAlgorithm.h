/*
  ==============================================================================

    PitchAlgorithm.h

    The algorithm calculates new values for pitch.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include "Algorithm.h"

class PitchAlgorithm : public Algorithm {
public:
    PitchAlgorithm() {};
    ~PitchAlgorithm() {};
    float calculateNewValue(float currentValue, int organicValue) override;
    float calculateNewLogValue(float currentValue, int organicValue) override;

private:
    float roundable(float param) override;
    int makeChoice() override;
};