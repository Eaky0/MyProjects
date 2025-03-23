/*
  ==============================================================================

    StepRow.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "StepRow.h"

/**
 * StepRow
 *
 * Default constructor for StepRow. Initializes a StepRow with 16 steps.
 *
 * @pre None
 * @post A StepRow with 16 steps is created.
 */
StepRow::StepRow()
{
    for (int i = 0; i < 16; i++) {
        std::shared_ptr<Step> s = std::make_shared<Step>();
        Steps.push_back(s);
    }
}

/**
 * StepRow
 *
 * Constructor for StepRow. Initializes a StepRow with the specified number of steps.
 *
 * @param StepAmount The number of steps to initialize.
 * @pre None
 * @post A StepRow with the specified number of steps is created.
 */
StepRow::StepRow(int StepAmount)
{
    for (int i = 0; i < StepAmount; i++) {
        std::shared_ptr<Step> s = std::make_shared<Step>();
        Steps.push_back(s);
    }
}

/**
 * ~StepRow
 *
 * Destructor for StepRow. Cleans up resources by resetting the shared pointers for each step.
 *
 * @pre None
 * @post The resources used by StepRow are cleaned up.
 */
StepRow::~StepRow()
{
    for (int i = 0; i < Steps.size(); i++) {
        Steps[i].reset();
    }
}

/**
 * setParamValue
 *
 * Sets the value of the specified parameter for a given step.
 *
 * @param Step The index of the step.
 * @param NewValue The new value for the parameter.
 * @param Parameter The parameter to be set (VOLUME, PITCH, DELAY).
 * @pre Step index must be valid.
 * @post The specified parameter value for the given step is updated.
 */
void StepRow::setParamValue(int Step, float NewValue, Sparam Parameter)
{
    switch (Parameter) {
    case Sparam::VOLUME:
        return Steps[Step]->setVolume(NewValue);
    case Sparam::PITCH:
        return Steps[Step]->setPitch(NewValue);
    case Sparam::DELAY:
        return Steps[Step]->setDelay(NewValue);
    default:
        break;
    }
}

/**
 * getParamValue
 *
 * Gets the value of the specified parameter for a given step.
 *
 * @param Step The index of the step.
 * @param P The parameter to retrieve (VOLUME, PITCH, DELAY).
 * @return The value of the specified parameter for the given step.
 * @pre Step index must be valid.
 * @post None
 */
float StepRow::getParamValue(int Step, Sparam P)
{
    switch (P) {
    case Sparam::VOLUME:
        return Steps[Step]->getVolume();
    case Sparam::PITCH:
        return Steps[Step]->getPitch();
    case Sparam::DELAY:
        return Steps[Step]->getDelay();
    default:
        break;
    }
    return 0.0f; // Default return value in case of invalid parameter
}

/**
 * getStepAmount
 *
 * Gets the number of steps in the StepRow.
 *
 * @return The number of steps.
 * @pre None
 * @post None
 */
int StepRow::getStepAmount()
{
    return Steps.size();
}

/**
 * resetAllSteps
 *
 * Resets the status of all steps in the StepRow.
 *
 * @pre None
 * @post The status of all steps is reset.
 */
void StepRow::resetAllSteps()
{
    for (std::shared_ptr<Step> s : Steps) {
        s->resetStatus();
    }
}

/**
 * initNewStep
 *
 * Initializes a new step and increments the step index.
 *
 * @pre None
 * @post The step index is incremented.
 */
void StepRow::initNewStep()
{
    index++;
    DBG(index);
}

/**
 * deleteStep
 *
 * Deletes a step and decrements the step index.
 *
 * @pre None
 * @post The step index is decremented.
 */
void StepRow::deleteStep()
{
    index--;
    DBG(index);
}

/**
 * getStepAt
 *
 * Gets the step at the specified index.
 *
 * @param index The index of the step.
 * @return Pointer to the Step object.
 * @pre Index must be valid.
 * @post None
 */
Step* StepRow::getStepAt(int index)
{
    return Steps[index].get();
}

/**
 * setSoundParam
 *
 * Sets the specified sound parameter for all steps in the StepRow.
 *
 * @param NewValue The new value for the parameter.
 * @param P The parameter to be set (VOLUME, PITCH, DELAY).
 * @pre None
 * @post The specified parameter value for all steps is updated.
 */
void StepRow::setSoundParam(float NewValue, Sparam P)
{
    for (int index = 0; index < Steps.size(); index++) {
        setParamValue(index, NewValue, P);
    }
}

/**
 * setLock
 *
 * Sets the lock state for the specified filter for all steps in the StepRow.
 *
 * @param filter The filter to lock/unlock (ORGANIC, REVERB).
 * @param lock The lock state (true to lock, false to unlock).
 * @pre None
 * @post The lock state for the specified filter for all steps is updated.
 */
void StepRow::setLock(Gparam filter, bool lock)
{
    for (std::shared_ptr<Step> s : Steps) {
        s->setLock(filter, lock);
    }
}
