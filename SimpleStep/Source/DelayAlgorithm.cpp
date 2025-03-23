/*
  ==============================================================================

    DelayAlgorithm.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "DelayAlgorithm.h"

DelayAlgorithm::DelayAlgorithm()
{
}

DelayAlgorithm::~DelayAlgorithm()
{
}

/**
* calculateDelay
* Calculates the delay value based on the BPM, organic value, and step resolution.
*
* @param bpm The beats per minute (tempo) of the music.
* @param Value The organic value selected by the user.
* @param stepResolution The resolution of each step in the step sequencer.
* @pre bpm > 0
* @pre Value >= 0
* @pre stepResolution > 0
* @post The delay value is calculated and constrained to a maximum of 0.1.
* @return The calculated delay value.
*/
float DelayAlgorithm::calculateDelay(int bpm, int Value, int stepResolution)
{
    // Calculate the length of a step
    float stepLength = (float)60 / (bpm * stepResolution);
    // Divide the step length into 3 segments
    float segmentLength = stepLength / 3;
    // Calculate the delay using the organic value
    float delay = (segmentLength / 10) * Value;

    float result = delay * makeDelayChoice();

    DBG("Delay Value = " + juce::String(result));

    // Constrain the result to a maximum of 0.1
    if (result > 0.1) {
        result = 0.1;
    }
    return result;
}

/**
* calculateLogDelay
* Calculates the logarithmic delay value based on the BPM, organic value, and step resolution.
*
* @param bpm The beats per minute (tempo) of the music.
* @param organicValue The organic value selected by the user.
* @param stepResolution The resolution of each step in the step sequencer.
* @pre bpm > 0
* @pre organicValue >= 0
* @pre stepResolution > 0
* @post The logarithmic delay value is calculated and constrained to a maximum of 0.1.
* @return The calculated logarithmic delay value.
*/
float DelayAlgorithm::calculateLogDelay(int bpm, int organicValue, int stepResolution)
{
    float stepLength = (float)60 / (bpm * stepResolution);
    float segmentLength = stepLength / 3;
    float delay = (segmentLength / 10) * log1p(organicValue);
    float result = delay * makeDelayChoice();
    DBG("Logarithmic Delay Value = " + juce::String(result));

    // Constrain the result to a maximum of 0.1
    if (result > 0.1) {
        result = 0.1;
    }
    return result;
}

/**
* makeDelayChoice
* Generates a random multiplier for the delay calculation.
*
* @pre None.
* @post Returns a random float between -1 and 1.
* @return A random float multiplier for the delay.
*/
float DelayAlgorithm::makeDelayChoice() {
    // Seed the random number generator with the current time
    float random = (float)getRandomNumber(-100, 100);
    float rand = random / 100;
    DBG("Random val = : " + juce::String(rand));
    return rand;
}
