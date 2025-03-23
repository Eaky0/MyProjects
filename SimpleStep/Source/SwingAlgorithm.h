/*
  ==============================================================================

    SwingAlgorithm.h

    This class is responsible for the calculation of the new swing algorithm. 

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include "Algorithm.h"

class SwingAlgorithm : public Algorithm {
public:
    float calculateNewValue(float currentValue, int organicValue) override;
    float calculateNewLogValue(float currentValue, int organicValue) override;

private:
    float roundable(float param) override;
    int makeChoice() override;
};
