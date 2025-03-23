/*
  ==============================================================================

    FilterManager.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "FilterManager.h"

/**
 * Constructs a new FilterManager object.
 *
 * Initializes the FilterManager object by resetting its parameters.
 *
 * @pre None.
 * @post FilterManager object is constructed with reset parameters.
 * @param None.
 * @return None.
 */
FilterManager::FilterManager() : filterParameters("FilterParameters")
{
    resetParam();
}

/**
 * Resets the parameters of the filter manager.
 *
 * Sets the default values for low-pass and high-pass filter parameters.
 *
 * @pre None.
 * @post Filter parameters are reset to default values.
 * @param None.
 * @return None.
 */
void FilterManager::resetParam()
{
    float lowFrequency = 2000.0f;
    float highFrequency = 2000.0f;
    float lowQ = 0.707f;
    float highQ = 0.707f;

    filterParameters.setProperty("LowFrequency", lowFrequency, nullptr);
    filterParameters.setProperty("HighFrequency", highFrequency, nullptr);
    filterParameters.setProperty("LowQ", lowQ, nullptr);
    filterParameters.setProperty("HighQ", highQ, nullptr);
}

/**
 * Retrieves the parameters of the filter manager.
 *
 * Returns a reference to the ValueTree object containing the filter parameters.
 *
 * @pre None.
 * @post Filter parameters are accessed.
 * @param None.
 * @return Reference to the ValueTree object containing the filter parameters.
 */
juce::ValueTree& FilterManager::getParams()
{
    return filterParameters;
}

/**
 * Sets a specific filter parameter to a new value.
 *
 * Modifies the value of a specified filter parameter in the filter parameters ValueTree.
 *
 * @pre None.
 * @post The specified filter parameter is updated with the new value.
 * @param filterParam The filter parameter to be modified.
 * @param newValue The new value to set for the filter parameter.
 * @return None.
 */
void FilterManager::setFParam(FParam filterParam, float newValue)
{
    switch (filterParam)
    {
    case FParam::LOWFREQUENCY:
        filterParameters.setProperty("LowFrequency", newValue, nullptr);
        break;
    case FParam::HIGHFREQUENCY:
        filterParameters.setProperty("HighFrequency", newValue, nullptr);
        break;
    case FParam::LOWQ:
        filterParameters.setProperty("LowQ", newValue, nullptr);
        break;
    case FParam::HIGHQ:
        filterParameters.setProperty("HighQ", newValue, nullptr);
        break;
    default:
        jassertfalse; //assertion error that will help with debugging
        break;
    }
}

/**
 * Retrieves the value of a specific filter parameter.
 *
 * Returns the value of the specified filter parameter from the filter parameters ValueTree.
 *
 * @pre None.
 * @post The value of the specified filter parameter is retrieved.
 * @param filterParam The filter parameter whose value is to be retrieved.
 * @return The value of the specified filter parameter.
 */
float FilterManager::getFParam(FParam filterParam) const
{
    switch (filterParam)
    {
    case FParam::LOWFREQUENCY:
        return filterParameters.getProperty("LowFrequency");
    case FParam::HIGHFREQUENCY:
        return filterParameters.getProperty("HighFrequency");
    case FParam::LOWQ:
        return filterParameters.getProperty("LowQ");
    case FParam::HIGHQ:
        return filterParameters.getProperty("HighQ");
    default:
        jassertfalse; //assertion error that will help with debugging
        return 0.0f;
    }
}

/**
 * Sets the status of a specific filter.
 *
 * Modifies the status of a specified filter (e.g., low-pass or high-pass).
 *
 * @pre None.
 * @post The status of the specified filter is updated.
 * @param filter The filter for which the status is to be modified.
 * @param status The new status to set for the filter.
 * @return None.
 */
void FilterManager::setFilterStatus(Gparam filter, bool status)
{
    switch (filter) {
    case Gparam::LOWPASS:
        lowPassActive = status;
        break;
    case Gparam::HIGHPASS:
        highPassActive = status;
        break;
    default:
        jassertfalse; //assertion error that will help with debugging
    }
}

/**
 * Retrieves the status of the low-pass filter.
 *
 * Returns the status of the low-pass filter.
 *
 * @pre None.
 * @post The status of the low-pass filter is retrieved.
 * @param None.
 * @return True if the low-pass filter is active, false otherwise.
 */
bool FilterManager::getLowPassStatus() const
{
    if (lowPassActive) {
        return true;
    }
    else {
        return false;
    }
}

/**
 * Retrieves the status of the high-pass filter.
 *
 * Returns the status of the high-pass filter.
 *
 * @pre None.
 * @post The status of the high-pass filter is retrieved.
 * @param None.
 * @return True if the high-pass filter is active, false otherwise.
 */
bool FilterManager::getHighPassStatus() const
{
    if (highPassActive) {
        return true;
    }
    else {
        return false;
    }
}
