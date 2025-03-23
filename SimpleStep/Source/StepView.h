/*
  ==============================================================================

    StepView.h

    This class is a view that shows a single step.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "Step.h"
#include "Utilities.h"

//==============================================================================
/*
*/
class StepView  : public juce::Component, public juce::Button::Listener, public AbstractObserver
{
public:
    StepView(juce::String id);
    ~StepView() override;


    void CreateSettingComponents();
    void buttonClicked(juce::Button* button) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void setModels(Step* s);
    void changeStepColor();

    void update(int id) override;
    void update(juce::File file) override {};
    void update(std::vector<float> data) override {};

    void changeOrganicLockState();
    void changeReverbLockState();
    void resetStep();
    
    void setSoundName(juce::String name);


private:
    std::unique_ptr<juce::TextButton> StepButton;
    std::unique_ptr<juce::AlertWindow> StepSettings;
    std::unique_ptr <juce::Component> SettingContainer;


    std::unique_ptr<LockButton> OrganicLock;
    std::unique_ptr<LockButton> ReverbLock;
    
    //pointer pointing to the step
    std::unique_ptr<Step> step;
    
    // Volume - slider - min:0 - max:100
    juce::Label VolumeLabel;
    juce::Slider VolumeSlider;
    double VolumeValue;

    // Pitch - slider - min:-6 - max:6
    juce::Label PitchLabel;
    juce::Slider PitchSlider;
    double PitchValue;

    // Delay - slider - min:pre - max:post
    juce::Label DelayLabel;
    juce::Slider DelaySlider;
    double DelayValue;


    juce::String StepID;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StepView)
};
