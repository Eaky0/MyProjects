/*
  ==============================================================================

    StepRow.h

    This class represents one row of a sequence and is responsible for it's logic.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include "Parameters.h"
#include <JuceHeader.h>
#include "Step.h"


class StepRow
{
public:
	StepRow();
    StepRow(int Steps);
    ~StepRow();


    void setParamValue(int Step, float NewValue, Sparam Parameter);
    float getParamValue(int Step, Sparam P);
    int getStepAmount();

    void resetAllSteps();
    void initNewStep();
    void deleteStep();
    Step * getStepAt(int index);
    void setSoundParam(float NewValue, Sparam P);

    void setLock(Gparam filter, bool lock);


private:
    int index = 16;
    //int activSteps = 0;
    std::vector<std::shared_ptr<Step>> Steps;
};

