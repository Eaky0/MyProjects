/*
  ==============================================================================

    Step.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "Step.h"

/**
    Constructs a Step object.

    @pre None.
    @post A Step object is created.
    @param None.
    @return None.
*/
Step::Step()
{
    // Initialize the ValueTree with the property names and default values
    properties = juce::ValueTree("StepProperties");
    properties.setProperty("Volume", 50, nullptr);
    properties.setProperty("Delay", 0.0f, nullptr);
    properties.setProperty("Pitch", 0.0f, nullptr);

} 

/**
    Destructs a Step object.

    @pre None.
    @post The Step object is destroyed.
    @param None.
    @return None.
*/
Step::~Step()
{

}

/**
    Sets the volume property of the Step.

    @pre volume is a value between 0 and 100.
    @post The volume property of the Step is set to the specified value.
    @param volume The volume value to set.
    @return None.
*/
void Step::setVolume(float volume) {
    properties.setProperty("Volume", volume, nullptr);
}

/**
    Sets the pre-delay property of the Step.

    @pre the delay can be between 0 and half of the step length.
    @post The pre-delay property of the Step is set to the specified value.
    @param preDelay The pre-delay value to set.
    @return None.
*/
void Step::setDelay(float preDelay) {
    properties.setProperty("Delay", preDelay, nullptr);
}

/**
    Sets the pitch property of the Step.

    @pre pitch is a value between -6 and 6.
    @post The pitch property of the Step is set to the specified value.
    @param pitch The pitch value to set.
    @return None.
*/
void Step::setPitch(float pitch) {
    properties.setProperty("Pitch", pitch, nullptr);
}

/**
    Retrieves the volume property of the Step.

    @pre None.
    @post None.
    @param None.
    @return The volume property value of the Step.
*/
float Step::getVolume() const {
    return properties.getProperty("Volume");
}

/**
    Retrieves the pre-delay property of the Step.

    @pre None.
    @post None.
    @param None.
    @return The pre-delay property value of the Step.
*/
float Step::getDelay() const {
    return properties.getProperty("Delay");
}


/**
    Retrieves the pitch property of the Step.

    @pre None.
    @post None.
    @param None.
    @return The pitch property value of the Step.
*/
float Step::getPitch() const {
    return properties.getProperty("Pitch");
}


/**
    Changes the status of the Step (active/inactive).

    @pre None.
    @post The status of the Step is toggled between active and inactive.
    @param None.
    @return None.
*/
void Step::changeStepStatus()
{
    isActive = !isActive;
    notifyObservers(30);
}

/**
 * resetStatus
 *
 * Resets the status of the Step object, deactivating it and unlocking any filters.
 *
 * @pre None
 * @post The Step object is deactivated and all filters are unlocked. Observers are notified of these changes.
 * @return void
 */
void Step::resetStatus(){
    isActive = false;
    notifyObservers(1);
    ReverbLocked = false;
    notifyObservers(2);
    OrganicLocked = false;
    notifyObservers(3);
}

/**
 * Sets the active status of the step.
 *
 * Updates the active status of the step and notifies observers.
 *
 * @param status The new active status for the step (true for active, false for inactive).
 * @pre None.
 * @post The step's active status is updated and observers are notified.
 * @return None.
 */
void Step::setStatus(bool status)
{
    isActive = status;
    notifyObservers(30);
}

/**
    Retrieves the status of the Step.

    @pre None.
    @post None.
    @param None.
    @return Returns true if the Step is active, false otherwise.
*/
bool Step::getStatus()
{
    return isActive;
}

/**
 * setLock
 *
 * Sets the lock state for a specified filter.
 *
 * @param filter The filter for which the lock state is being set.
 * @param lock The lock state to be set (true for locked, false for unlocked).
 * @pre None
 * @post The lock state of the specified filter is updated and observers are notified.
 * @return void
 */
void Step::setLock(Gparam filter, bool lock)
{
    switch (filter) {
        case Gparam::ORGANIC:
            OrganicLocked = lock;
            notifyObservers(2);
            break;
        case Gparam::REVERB:
            ReverbLocked = lock;
            notifyObservers(3);
            break;
    }
}

/**
 * getLockState
 *
 * Retrieves the lock state for a specified filter.
 *
 * @param filter The filter for which the lock state is being retrieved.
 * @pre None
 * @post None
 * @return True if the filter is locked, false otherwise.
 */
bool Step::getLockState(Gparam filter)
{
    switch (filter) {
    case Gparam::ORGANIC:
        return OrganicLocked;
        break;
    case Gparam::REVERB:
        return ReverbLocked;
    }
}

