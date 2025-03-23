/*
  ==============================================================================

    Step.h

    A class that represents a step and contains the necessary information for a step.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AbstractObservable.h"
#include "Parameters.h"

class Step : public AbstractObservable
{
public:
    Step();
    ~Step();

    // Setters for properties
    void setVolume(float volume);
    void setDelay(float Predelay);
    void setPitch(float Pitch);

    // Getters for properties
    float getVolume() const;
    float getDelay() const;
    float getPitch() const;

    void changeStepStatus();
    void resetStatus();
    void setStatus(bool status);
    bool getStatus();
    bool getManipulated() { return Manipulated; };
    void setManipulationstat(bool stat) { Manipulated = stat; };

    void setLock(Gparam filter, bool lock);
    bool getLockState(Gparam filter);
private:
    bool isActive = false;
    bool ReverbLocked = false;
    bool OrganicLocked = false;
    bool Manipulated = false; 

    juce::ValueTree properties;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Step)
};