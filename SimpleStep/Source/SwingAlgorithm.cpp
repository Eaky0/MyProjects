/*
  ==============================================================================

    SwingAlgorithm.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "SwingAlgorithm.h"

/*
    Calculates a new value for the swing based on the current value and organic value.

    @param currentValue The current value.
    @param organicValue The organic value selected by the user.
    @pre None.
    @post None.
    @return The calculated new value.
*/
float SwingAlgorithm::calculateNewValue(float currentValue, int organicValue)
{
    float v1 = (currentValue + organicValue) / 10;
    float v2 = (currentValue - organicValue) / 10;

    int choice = makeChoice();
    if (choice > 0) {
        return roundable(v2);
    }
    else {
        return roundable(v1);
    }
}

float SwingAlgorithm::calculateNewLogValue(float currentValue, int organicValue)
{
    float logValue = log1p(organicValue);
    float v1 = (currentValue + logValue) / 10;
    float v2 = (currentValue - logValue) / 10;
    int choice = makeChoice();
    if (choice > 0) {
        return roundable(v2);
    }
    else {
        return roundable(v1);
    }
}

/*
    Rounds the parameter to be within the range [1, 10].

    @param param The parameter to be rounded.
    @pre None.
    @post None.
    @return The rounded value within the range [1, 10].
*/
float SwingAlgorithm::roundable(float param)
{
    if (param <= 0) {
        return 1;
    }
    else if (param >= 10) {
        return 10;
    }
    return param;
}

/*
    Generates a random choice between 0 and 1.

    @pre None.
    @post None.
    @return A random choice between 0 and 1.
*/
int SwingAlgorithm::makeChoice()
{
    // Seed the random number generator with the current time
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Make a choice between 0 or 1
    return std::rand() % 2;
}
