/*
  ==============================================================================

    SoundView.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "SoundView.h"

//==============================================================================

/**
* Constructor for SoundView.
*
* Initializes the component with a text button displaying the given SoundName.
* Sets button color and size.
*
* @param SoundName The name of the sound.
* @return None.
* @pre None.
* @post Component is initialized with a text button and color set, displaying the SoundName.
* @author Atakan Kumas
*/
SoundView::SoundView(juce::String SoundName)
{
    
    SoundButton = std::make_unique<juce::TextButton>();
    SoundButton->setButtonText(SoundName);
    SoundButton->setColour(juce::TextButton::buttonColourId, juce::Colour(3, 4, 94));
    SoundButton->addMouseListener(this, true);
    SoundButton->addListener(this);


    auto buttonStyle = [](juce::Button* button) {
        button->setColour(juce::TextButton::buttonColourId, juce::Colours::white); // Set button color
        button->setColour(juce::TextButton::textColourOffId, juce::Colours::black); // Set text color
    };


    SoundSettings = std::make_unique<juce::AlertWindow>("Sound settings",
        "Settings for Sound: Unknown", juce::MessageBoxIconType::NoIcon);

    SoundSettings->addButton("Cancel", 0);
    SoundSettings->getButton("Cancel")->addListener(this);
    buttonStyle(SoundSettings->getButton("Cancel"));

    SoundSettings->addButton("Reset", 1);
    SoundSettings->getButton("Reset")->addListener(this);
    buttonStyle(SoundSettings->getButton("Reset"));

    SoundSettings->addButton("Save", 2);
    SoundSettings->getButton("Save")->addListener(this);
    buttonStyle(SoundSettings->getButton("Save"));


    SoundSettings->setColour(juce::AlertWindow::backgroundColourId, juce::Colour(129, 164, 205));
    SoundSettings->setColour(juce::AlertWindow::outlineColourId, juce::Colour(219, 228, 238));

    CreateSettingComponents();
    
    addAndMakeVisible(*SoundButton);


    setSize(100, 25);
}

/**
* Sets the text of the button.
*
* @param Text The text to set.
* @return None.
* @pre None.
* @post Button text is updated to the provided Text.
* @author Atakan Kumas
*/
void SoundView::setSoundName() {
    juce::String Text = SoundModel.get()->getSoundName();

    if (Text == "Empty") {
        SoundButton.get()->setButtonText("+");
        SoundSettings->setMessage("Settings for Sound: Unknown");
    }
    else {
        SoundButton.get()->setButtonText(Text);
        SoundSettings->setMessage("Settings for Sound: " + Text);
    }
    
    
}

/**
 * CreateSettingComponents
 *
 * Creates and initializes setting components for volume, volume multiplier, pitch, delay, and lock buttons.
 *
 * @pre None
 * @post Setting components are created and initialized.
 * @return void
 *
 */
void SoundView::CreateSettingComponents()
{
    SettingContainer = std::make_unique<juce::Component>();
    SettingContainer->setBounds(0, 0, 220, 300);

    VolumeLabel.setText("Volume", juce::dontSendNotification);
    VolumeLabel.setBounds(10, 10, 100, 20);
    SettingContainer->addAndMakeVisible(VolumeLabel);

    VolumeSlider.setRange(0, 100, 1);
    VolumeSlider.setValue(50);
    VolumeValue = 50;
    VolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    VolumeSlider.setPopupDisplayEnabled(true, true, SoundSettings.get());
    VolumeSlider.setTextValueSuffix("%");
    VolumeSlider.setBounds(10, 40, 180, 20);
    SettingContainer->addAndMakeVisible(VolumeSlider);

    // Volume Multiplier Slider
    VolumeMultiplierLabel.setText("Volume Multiplier", juce::dontSendNotification);
    VolumeMultiplierLabel.setBounds(10, 70, 150, 20);
    SettingContainer->addAndMakeVisible(VolumeMultiplierLabel);

    VolumeMultiplierSlider.setRange(0.5, 2.0, 0.1);
    VolumeMultiplierSlider.setValue(1.0);
    VolumeMultiplierValue = 1.0;
    VolumeMultiplierSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    VolumeMultiplierSlider.setPopupDisplayEnabled(true, true, SoundSettings.get());
    VolumeMultiplierSlider.setTextValueSuffix("x");
    VolumeMultiplierSlider.setBounds(10, 100, 180, 20);
    SettingContainer->addAndMakeVisible(VolumeMultiplierSlider);

    PitchLabel.setText("Pitch", juce::dontSendNotification);
    PitchLabel.setBounds(10, 130, 100, 20);
    SettingContainer->addAndMakeVisible(PitchLabel);

    PitchSlider.setRange(-6, 6, 1);
    PitchSlider.setValue(0);
    PitchValue = 0;
    PitchSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    PitchSlider.setPopupDisplayEnabled(true, true, SoundSettings.get());
    PitchSlider.setTextValueSuffix(" 8va");
    PitchSlider.setBounds(10, 160, 180, 20);
    SettingContainer->addAndMakeVisible(PitchSlider);

    DelayLabel.setText("Delay", juce::dontSendNotification);
    DelayLabel.setBounds(10, 190, 100, 20);
    SettingContainer->addAndMakeVisible(DelayLabel);

    DelaySlider.setRange(-0.20, 0.10, 0.01);
    DelaySlider.setTextValueSuffix(" ms");
    DelaySlider.setValue(0);
    DelayValue = 0;
    DelaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    DelaySlider.setPopupDisplayEnabled(true, true, SoundSettings.get());
    DelaySlider.setBounds(10, 220, 180, 20);
    SettingContainer->addAndMakeVisible(DelaySlider);


    auto buttonStyle = [](juce::TextButton& button) {
        button.setColour(juce::TextButton::buttonColourId, juce::Colours::white); // Set button color
        button.setColour(juce::TextButton::textColourOnId, juce::Colours::black); // Set text color
        button.setColour(juce::TextButton::textColourOffId, juce::Colours::black); // Set text color
    };

    juce::File resourceDir;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    resourceDir = currentDir.getChildFile("resource");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    resourceDir = grandParentDir.getChildFile("resource");

#endif
    
    juce::File LockIconFile(resourceDir.getChildFile("lock_closed.png").getFullPathName());
    juce::File UnlockIconFile(resourceDir.getChildFile("lock_open.png").getFullPathName());

    auto LockIcon = juce::ImageFileFormat::loadFrom(LockIconFile);
    auto UnlockIcon = juce::ImageFileFormat::loadFrom(UnlockIconFile);
    OrganicLock = std::make_unique<LockButton>("Organic",LockIcon, UnlockIcon);
    OrganicLock->addListener(this);
    OrganicLock->setBounds(10, 250, 100, 20);
    buttonStyle(*OrganicLock);
    SettingContainer->addAndMakeVisible(OrganicLock.get());

    ReverbLock = std::make_unique<LockButton>("Reverb", LockIcon, UnlockIcon);
    ReverbLock->addListener(this);
    ReverbLock->setBounds(110, 250, 100, 20);
    buttonStyle(*ReverbLock);
    SettingContainer->addAndMakeVisible(ReverbLock.get());

    // Ensure all items in the container are visible
    SettingContainer->setVisible(true);

    SoundSettings->addCustomComponent(SettingContainer.get());
}


/**
 * buttonClicked
 *
 * Handles button click events.
 *
 * @param button The button that was clicked.
 * @pre None
 * @post Depending on the clicked button, settings are reset, saved, or canceled. Sound library visibility is toggled, and lock states are updated accordingly.
 * @return void
 *
 */
void SoundView::buttonClicked(juce::Button* button)
{
    if (button == SoundSettings->getButton("Cancel"))
    {

        VolumeSlider.setValue(SoundModel->getSoundParam(Sparam::VOLUME));
        VolumeMultiplierSlider.setValue(1);
        PitchSlider.setValue(SoundModel->getSoundParam(Sparam::PITCH));
        DelaySlider.setValue(SoundModel->getSoundParam(Sparam::DELAY));

        SoundSettings->setVisible(false);
        SoundSettings->exitModalState();
    }

    if (button == SoundSettings->getButton("Reset"))
    {
        VolumeSlider.setValue(50);
        VolumeMultiplierSlider.setValue(1);
        PitchSlider.setValue(0);
        DelaySlider.setValue(0);
        VolumeValue = 50;
        VolumeMultiplierValue = 1;
        PitchValue = 0;
        DelayValue = 0;
    }


    if (button == SoundSettings->getButton("Save"))
    {
        VolumeSlider.setValue(VolumeSlider.getValue());
        oldVolumeValue = VolumeValue;
        VolumeValue = VolumeSlider.getValue();
        VolumeMultiplierSlider.setValue(VolumeMultiplierSlider.getValue());
        VolumeMultiplierValue = VolumeMultiplierSlider.getValue();
        PitchSlider.setValue(PitchSlider.getValue());
        PitchValue = PitchSlider.getValue();
        DelaySlider.setValue(DelaySlider.getValue());
        DelayValue = DelaySlider.getValue();


        int numPages = SoundModel->getPageAmount();

        if (oldVolumeValue != VolumeValue) {


            for (int page = 0; page < numPages; ++page) {
                SoundModel.get()->setSoundParam(page, VolumeValue, Sparam::VOLUME);
            }

        }


        for (int page = 0; page < numPages; ++page) {
            SoundModel.get()->setSoundParam(page,PitchValue, Sparam::PITCH);
            SoundModel.get()->setSoundParam(page,DelayValue, Sparam::DELAY);
        }

        //if the multiplier value has been changed we will aplly it
        if (VolumeMultiplierValue != (double)1) {
            SoundModel->applyVolumeMultiplier(VolumeMultiplierValue);
            VolumeMultiplierSlider.setValue(1);
        }

        SoundSettings->setVisible(false);
        SoundSettings->exitModalState();
    }


    if (button == SoundButton.get())
    {
        // Ensure all components are visible
        SoundLib_Ptr->MakeVisible();
        SoundLib_Ptr->setSelected(SoundModel.get());
    }

    if (button == OrganicLock.get()) {

        if (OrganicLock->getState()) {
            OrganicLock->setState(false);
            SoundModel->setLock(Gparam::ORGANIC, false);

        }
        else {
            OrganicLock->setState(true);
            SoundModel->setLock(Gparam::ORGANIC, true);
        }



    }

    if (button == ReverbLock.get()) {
        if (ReverbLock->getState()) {
            ReverbLock->setState(false);
            SoundModel->setLock(Gparam::REVERB, false);
        }
        else {
            ReverbLock->setState(true);
            SoundModel->setLock(Gparam::REVERB, true);
        }
    }


}


/**
 * mouseDown
 *
 * Handles mouse down events, specifically right-clicks on the SoundButton.
 *
 * @param event The MouseEvent object containing details about the mouse event.
 * @pre None
 * @post If the right mouse button is pressed while the SoundButton is clicked, the SoundSettings component becomes visible and enters a modal state.
 * @return void
 */
void SoundView::mouseDown(const juce::MouseEvent& event)
{
    if (event.mods.isRightButtonDown() && event.originalComponent == SoundButton.get())
    {
        // Ensure all components are visible

        VolumeSlider.setValue(SoundModel->getSoundParam(Sparam::VOLUME));
        PitchSlider.setValue(SoundModel->getSoundParam(Sparam::PITCH));
        DelaySlider.setValue(SoundModel->getSoundParam(Sparam::DELAY));

        SoundSettings->setVisible(true);
        SoundSettings->enterModalState(true);

    }
 
}

juce::String SoundView::getSoundName()
{
    return juce::String();
}

/**
* Destructor for SoundView.
*
* Cleans up any resources associated with the component.
*
* @return None.
* @pre None.
* @post Component is destructed, releasing associated resources.
* @author Atakan Kumas
*/
SoundView::~SoundView()
{
    // No special cleanup required in the destructor
    SoundModel.reset();
}



/**
* SetLibrary
*
* Makes sure that a SoundView object is linked to the library.
*
* @return None.
* @pre None.
* @post This SoundView-object shares the library with other SoundView-objects.
* @author Atakan Kumas
*/
void SoundView::setLibrary(SoundLibraryView *SL)
{
    SoundLib_Ptr = std::make_shared<SoundLibraryView>();
    SoundLib_Ptr.reset(SL);
}




/**
* Paint function of SoundView.
*
* Paints this component.
*
* @param g The Graphics context that must be used to do the drawing operations.
* @return None.
* @pre None.
* @post Component has been painted accordingly.
* @author Atakan Kumas
*/
void SoundView::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(129, 164, 205));
}

/**
* Resized function of SoundView.
*
* Resizes child components of this component.
*
* @return None.
* @pre Window needs to be resized.
* @post Child components have been resized accordingly.
* @author Atakan Kumas
*/
void SoundView::resized()
{
    SoundButton->setBounds(2, 5, getWidth() - 5, getHeight() - 5);
}


/**
 * getSoundPtr
 *
 * Retrieves the pointer to the current SoundModel.
 *
 * @pre None
 * @post None
 * @return A pointer to the SoundModel.
 */
Sound* SoundView::getSoundPtr()
{
    return SoundModel.get();
}

/**
 * setModels
 *
 * Sets the SoundModel to a new Sound object.
 *
 * @param s A pointer to the new Sound object.
 * @pre None
 * @post The SoundModel is updated to point to the new Sound object.
 * @return void
 */
void SoundView::setModels(Sound* s)
{
    SoundModel.reset(s);
}


/**
 * getSoundViewButton
 *
 * Retrieves the pointer to the SoundButton.
 *
 * @pre None
 * @post None
 * @return A pointer to the SoundButton.
 */
juce::TextButton * SoundView::getSoundViewButton()
{
    return SoundButton.get();
}
