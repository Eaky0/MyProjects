/*
  ==============================================================================

    OrganicManager.h

    OrganicManager manages the manipulations when an organic generation is called.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once
#include "Algorithm.h"
#include "DelayAlgorithm.h"
#include "PitchAlgorithm.h"
#include "SwingAlgorithm.h"
#include "VolumeAlgorithm.h"
#include "SoundManager.h"
#include "OrganicPopupComponent.h"
#include <vector>

class OrganicManager {
public:
    OrganicManager();
    ~OrganicManager();
    void setOrganicView(OrganicPopupComponent* popup);
    void setSMPtr(SoundManager* s);
    void setAlgorithms();
    void applyOrganic();
private:
    void OurAlgorithm(std::vector<int> steps);
    void LOGAlgorithm(std::vector<int> steps);
    std::vector<int> getStepsToChange();

    std::vector<int> OrganicManager::calculateAmountActive();
    float calcChancetoChange(int totalSteps, int activeSteps);

    OrganicPopupComponent* popupREF;
    std::unique_ptr<DelayAlgorithm> delayAlg;
    std::unique_ptr<PitchAlgorithm> pitchAlg;
    std::unique_ptr<SwingAlgorithm> swingAlg;
    std::unique_ptr<VolumeAlgorithm> volumeAlg;

    std::shared_ptr<SoundManager> SoundM;
};