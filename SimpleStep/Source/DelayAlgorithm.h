/*
  ==============================================================================

    DelayAlgorithm.h

    Algorithm to calculate values for delay.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include "Algorithm.h"

class DelayAlgorithm : public Algorithm {
public:
    DelayAlgorithm();
    ~DelayAlgorithm() override;
    float calculateDelay(int bpm, int Value, int stepResolution);
    float calculateLogDelay(int bpm, int organicValue, int stepResolution);



    float makeDelayChoice();
    float calculateNewValue(float currentValue, int organicValue) override { return 0; };
    float calculateNewLogValue(float currentValue, int organicValue) override { return 0; };

private:
    float roundable(float param) override { return 0; };
    int makeChoice() override { return 0; };
};