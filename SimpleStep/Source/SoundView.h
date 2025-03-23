/*
  ==============================================================================

    SoundView.h

    A class that is responsible for the appearance of an instrument in the sequence.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SoundLibraryView.h"
#include "Utilities.h"

//==============================================================================
/*
*/



class SoundView  : public juce::Component, juce::Button::Listener
{
public:
    SoundView(juce::String SoundName);
    ~SoundView() override;

    void setLibrary(SoundLibraryView * SL);

    void setSoundName();
    void CreateSettingComponents();
    void buttonClicked(juce::Button* button) override;
    void mouseDown(const juce::MouseEvent& event) override;
    juce::String getSoundName();
    void paint (juce::Graphics&) override;
    void resized() override;
    Sound* getSoundPtr();
    void setModels(Sound * s);
    juce::TextButton * getSoundViewButton();

private:

    std::unique_ptr<juce::TextButton> SoundButton;
    std::unique_ptr<juce::AlertWindow> SoundSettings;
    std::unique_ptr<juce::Component> SettingContainer;
    std::shared_ptr<Sound> SoundModel;
    std::shared_ptr<SoundLibraryView> SoundLib_Ptr;

    // Volume - slider - min:0 - max:100
    juce::Label VolumeLabel;
    juce::Slider VolumeSlider;
    double VolumeValue;
    double oldVolumeValue;

    // Volume Multiplier - slider - min: 0.5 - max: 2.0
    juce::Label VolumeMultiplierLabel;
    juce::Slider VolumeMultiplierSlider;
    double VolumeMultiplierValue;

    std::unique_ptr<LockButton> OrganicLock;
    std::unique_ptr<LockButton> ReverbLock;

    // Pitch - slider - min:-6 - max:6
    juce::Label PitchLabel;
    juce::Slider PitchSlider;
    double PitchValue;

    // Delay - slider - min:pre - max:post
    juce::Label DelayLabel;
    juce::Slider DelaySlider;
    double DelayValue;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SoundView)
};
