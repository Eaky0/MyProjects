/*
  ==============================================================================

    VolumeAlgorithm.h

    This class implements the volume algorithm that will be used to generate new volume values.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include "Algorithm.h"

class VolumeAlgorithm : public Algorithm {
public:
    float calculateNewValue(float currentValue, int organicValue) override;
    float calculateNewLogValue(float currentValue, int organicValue) override;
    float calculateGain(int SwingValue, int strength);

private:
    float roundable(float param) override;
    int makeChoice() override;
};