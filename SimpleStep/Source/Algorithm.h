/*
  ==============================================================================

    Algorithm.h

    Is an interface for algorithms 

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/


#pragma once

#include <JuceHeader.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <random>

// The abstract class that is our interface for the different algorithms we provide
class Algorithm {
public:
    virtual ~Algorithm() {};

    /**
    * calculateNewValue
    * Calculates a new value based on the current value and an organic value.
    *
    * @param currentValue The current float value.
    * @param organicValue An integer representing the organic value.
    * @pre currentValue is a valid float and organicValue is a valid integer.
    * @post Returns a new float value based on the algorithm's calculation.
    * @return The calculated new float value.
    */
    virtual float calculateNewValue(float currentValue, int organicValue) = 0;

    /**
    * calculateNewLogValue
    * Calculates a new logarithmic value based on the current value and an organic value.
    *
    * @param currentValue The current float value.
    * @param organicValue An integer representing the organic value.
    * @pre currentValue is a valid float and organicValue is a valid integer.
    * @post Returns a new logarithmic float value based on the algorithm's calculation.
    * @return The calculated new logarithmic float value.
    */
    virtual float calculateNewLogValue(float currentValue, int organicValue) = 0;

    int getRandomNumber(int min, int max);

private:
    /**
    * roundable
    * Rounds the given parameter based on the algorithm's specific rounding rules.
    *
    * @param param The float parameter to be rounded.
    * @pre param is a valid float.
    * @post Returns the rounded float value based on the algorithm's rules.
    * @return The rounded float value.
    */
    virtual float roundable(float param) = 0;

    /**
    * makeChoice
    * Makes a choice based on the algorithm's specific decision rules.
    *
    * @pre None.
    * @post Returns an integer representing the choice made by the algorithm.
    * @return The integer representing the choice.
    */
    virtual int makeChoice() = 0;
};
