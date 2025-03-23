/*
  ==============================================================================

    PitchAlgorithm.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "PitchAlgorithm.h"

/*
    Calculates a new value for the Pitch based on the current value and organic value.

    @param currentValue The current value.
    @param organicValue The organic value selected by the user.
    @pre None.
    @post None.
    @return The calculated new value.
*/
float PitchAlgorithm::calculateNewValue(float currentValue, int organicValue)
{
    float v1 = (currentValue + organicValue) / 10;
    float v2 = (currentValue - organicValue) / 10;

    int choice = makeChoice();
    if (choice > 0.5) {
        return roundable(v2);
    }
    else {
        return roundable(v1);
    }
}

/**
* calculateNewLogValue
* Calculates a new pitch value based on a logarithmic algorithm.
*
* @param currentValue The current pitch value.
* @param organicValue The strength of organic changes applied.
*
* @pre None.
* @post A new pitch value is calculated using a logarithmic algorithm.
* @return The new pitch value.
*
*/
float PitchAlgorithm::calculateNewLogValue(float currentValue, int organicValue)
{
    // Calculate the logarithm of (1 + organicValue)
    float logValue = log1p(organicValue);

    // Calculate two possible new pitch values based on the logarithm
    float v1 = (currentValue + logValue) / 10;
    float v2 = (currentValue - logValue) / 10;

    // Determine which value to return based on a choice
    int choice = makeChoice();
    if (choice > 0.5) {
        return roundable(v2);
    }
    else {
        return roundable(v1);
    }
}


/*
    Rounds the parameter to be within the range [-6, 6].

    @param param The parameter to be rounded.
    @pre None.
    @post None.
    @return The rounded value within the range [-6, 6].
*/
float PitchAlgorithm::roundable(float param)
{
    if (param <= -6) {
        return -6;
    }
    else if (param >= 6) {
        return 6;
    }
    return param;
}

/*
    Generates a random choice between 0 and 1.

    @pre None.
    @post None.
    @return A random choice between 0 and 1.
*/
int PitchAlgorithm::makeChoice()
{
    // Seed the random number generator with the current time
    int random = getRandomNumber(0, 100);

    // Make a choice between 0 or 1
    return random % 2;
}
