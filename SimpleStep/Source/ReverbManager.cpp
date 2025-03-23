/*
  ==============================================================================

    ReverbManager.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "ReverbManager.h"

/**
* ReverbManager
* Constructor for the ReverbManager class.
* Initializes the default reverb parameters.
*
* @pre None.
* @post Initializes the ReverbParameters value tree with default parameters.
*
*/
ReverbManager::ReverbManager()
{

    float roomSize = 0.5f;
    float damping = 0.5f;
    float wetLevel = 0.33f;
    float dryLevel = 0.4f;
    float width = 1.0f;


    ReverbParameters = new juce::ValueTree("Reverb Parameters");

    ReverbParameters->setProperty("Roomsize", roomSize, nullptr);
    ReverbParameters->setProperty("Damping", damping, nullptr);
    ReverbParameters->setProperty("Wet", wetLevel, nullptr);
    ReverbParameters->setProperty("Dry", dryLevel, nullptr);
    ReverbParameters->setProperty("Width", width, nullptr);

}

/**
* ~ReverbManager
* Destructor for the ReverbManager class.
* Deallocates memory used by the ReverbParameters value tree.
*
* @pre None.
* @post Deallocates memory used by the ReverbParameters value tree.
*
*/
ReverbManager::~ReverbManager()
{
    delete ReverbParameters;
}


/**
* resetParam
* Resets the reverb parameters to their default values.
*
* @pre None.
* @post Resets the reverb parameters to their default values.
*
*/
void ReverbManager::resetParam() {
    float roomSize = 0.5f;
    float damping = 0.5f;
    float wetLevel = 0.33f;
    float dryLevel = 0.4f;
    float width = 1.0f;

    ReverbParameters->setProperty("Roomsize", roomSize, nullptr);
    ReverbParameters->setProperty("Damping", damping, nullptr);
    ReverbParameters->setProperty("Wet", wetLevel, nullptr);
    ReverbParameters->setProperty("Dry", dryLevel, nullptr);
    ReverbParameters->setProperty("Width", width, nullptr);
}

/**
* GetParams
* Retrieves the value tree containing the reverb parameters.
*
* @pre None.
* @post None.
* @return A pointer to the value tree containing the reverb parameters.
*
*/
juce::ValueTree* ReverbManager::GetParams()
{
    return ReverbParameters;
}

/**
* setRParam
* Sets a specific reverb parameter to the given value.
*
* @param r The reverb parameter to set.
* @param newValue The new value for the reverb parameter.
* @pre None.
* @post Sets the specified reverb parameter to the given value.
*
*/
void ReverbManager::setRParam(RParam r, float newValue)
{
    switch (r)
    {
    case RParam::ROOMSIZE:
        ReverbParameters->setProperty("Roomsize", newValue, nullptr);
        break;
    case RParam::DAMPING:
        ReverbParameters->setProperty("Damping", newValue, nullptr);
        break;
    case RParam::WIDTH:
        ReverbParameters->setProperty("Width", newValue, nullptr);
        break;
    case RParam::DRY:
        ReverbParameters->setProperty("Dry", newValue, nullptr);
        break;
    case RParam::WET:
        ReverbParameters->setProperty("Wet", newValue, nullptr);
        break;
    default:
        break;
    }

}

/**
* getRParam
* Retrieves the value of a specific reverb parameter.
*
* @param r The reverb parameter to retrieve.
* @pre None.
* @post None.
* @return The value of the specified reverb parameter.
*
*/
float ReverbManager::getRParam(RParam r)
{
    switch (r)
    {
    case RParam::ROOMSIZE:
        return ReverbParameters->getProperty("Roomsize");
        break;
    case RParam::DAMPING:
        return ReverbParameters->getProperty("Damping");
        break;
    case RParam::WIDTH:
        return ReverbParameters->getProperty("Width");
        break;
    case RParam::DRY:
        return ReverbParameters->getProperty("Dry");
        break;
    case RParam::WET:
        return ReverbParameters->getProperty("Wet");
        break;
    default:
        break;
    }
}
