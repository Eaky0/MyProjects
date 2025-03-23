/*
  ==============================================================================

    VolumeAlgorithm.h
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "VolumeAlgorithm.h"

/*
    Calculates a new value for the Volume based on the current value and organic value.

    @param currentValue The current value.
    @param organicValue The organic value selected by the user.
    @pre None.
    @post None.
    @return The calculated new value.
*/
float VolumeAlgorithm::calculateNewValue(float currentValue, int organicValue)
{
    float v1 = currentValue + organicValue;
    float v2 = currentValue - organicValue;

    int choice = makeChoice();
    if (choice == 0) {
        return roundable(v2);
    }
    else {
        return roundable(v1);
    }
}



/**
* calculateNewLogValue
* Calculates a new logarithmic value based on the current value and organic value.
* This function is used in a SwingAlgorithm to modify the timing of steps.
*
* @param currentValue The current value to be modified.
* @param organicValue The organic value used in the calculation.
* @pre None.
* @post None.
* @return The new calculated value.
*
*/
float VolumeAlgorithm::calculateNewLogValue(float currentValue, int organicValue)
{
    float logValue = log1p(organicValue);
    float v1 = currentValue + logValue;
    float v2 = currentValue - logValue;
    int choice = makeChoice();
    if (choice == 0) {
        return roundable(v2);
    }
    else {
        return roundable(v1);
    }
}

/**
* calculateGain
* Calculates the gain value based on the swing value and strength of the beat.
* This function is used in a VolumeAlgorithm to adjust volume levels.
*
* @param SwingValue The swing value to be applied.
* @param strength The strength of the beat (1 for strong, 0 for weak).
* @pre None.
* @post None.
* @return The calculated gain value.
*
*/
float VolumeAlgorithm::calculateGain(int SwingValue, int strength)
{
    // Strong beat
    if (strength == 1) {
        return (float)getRandomNumber(75 + SwingValue, 100);
    }
    // Weak beat
    else {
        return (float)getRandomNumber(20, 40 - SwingValue);
    }
}



/*
    Rounds the parameter to be within the range [1, 100].

    @param param The parameter to be rounded.
    @pre None.
    @post None.
    @return The rounded value within the range [1, 100].
*/
float VolumeAlgorithm::roundable(float param)
{
    if (param <= 0) {
        return 1;
    }
    else if (param >= 100) {
        return 100;
    }
    return param;
}

/*
    Generates a random choice between 0 and 1.

    @pre None.
    @post None.
    @return A random choice between 0 and 1.
*/
int VolumeAlgorithm::makeChoice()
{
    // Seed the random number generator with the current time
    int random = getRandomNumber(0, 100);

    // Make a choice between 0 or 1
    return random % 2;
}