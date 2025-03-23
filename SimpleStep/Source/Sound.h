/*
  ==============================================================================

    Sound.h

    This class contains the data of an instrument and can influence other steps using the StepRow.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include "StepRow.h"
#include "VolumeAlgorithm.h"

class Sound : public AbstractObservable
{
public:
    Sound(juce::String name);
    Sound(juce::String name, int PageAmount, int StepAmount);
    ~Sound();
    juce::String getSoundName();
    void setSoundName(juce::String newName);
    Step* getStepAt(int page, int index);
    void initNewStep();
    void deleteStep();

    void addPage();
    //void deletePage();
    int getSize();

    int getPageAmount() { return Patterns.size(); };

    void resetAllSteps();

    float getStepParamValue(int page, int index, Sparam P);
    void setStepParamValue(int page, int index, float newValue, Sparam P);
    void setSoundParam(int page, float NewValue, Sparam P);

    void applyGain(int SwingValue, int Strength);

    void resetAllParams();
    void applyVolumeMultiplier(float multiplier);
    float getSoundParam(Sparam P);

    void setLock(Gparam filter, bool lock);


private:
    bool Chosen = false;
    juce::String SoundName;
    std::vector<StepRow*> Patterns;
    juce::ValueTree SoundParameters;
};