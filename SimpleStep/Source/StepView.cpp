/*
  ==============================================================================

    StepView.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "StepView.h"

//==============================================================================

/**
* Constructor for StepView.
*
* Initializes the component with a text button representing a step.
* Sets button color and size.
*
* @return None.
* @pre None.
* @post Component is initialized with a text button representing a step and color set.
* @author ataka
*/
StepView::StepView(juce::String id) : StepID{id}
{
    StepButton = std::make_unique <juce::TextButton>();
    StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(219, 228, 238));
    StepButton->addMouseListener(this, true);

    auto buttonStyle = [](juce::Button* button) {
        button->setColour(juce::TextButton::buttonColourId, juce::Colours::white); // Set button color
        button->setColour(juce::TextButton::textColourOffId, juce::Colours::black); // Set text color
    };


    StepSettings = std::make_unique<juce::AlertWindow>("Step settings",
        "Settings for step " + StepID, juce::MessageBoxIconType::NoIcon);
    StepSettings->addButton("Cancel", 0);
    StepSettings->getButton("Cancel")->addListener(this);
    buttonStyle(StepSettings->getButton("Cancel"));

    StepSettings->addButton("Reset", 1);
    StepSettings->getButton("Reset")->addListener(this);
    buttonStyle(StepSettings->getButton("Reset"));

    StepSettings->addButton("Save", 2);
    StepSettings->getButton("Save")->addListener(this);
    buttonStyle(StepSettings->getButton("Save"));

    StepSettings->setColour(juce::AlertWindow::backgroundColourId, juce::Colour(129, 164, 205));
    StepSettings->setColour(juce::AlertWindow::outlineColourId, juce::Colour(219, 228, 238));


    CreateSettingComponents();


    addAndMakeVisible(*StepButton);

    setSize(25, 25);

}

/**
* Destructor for StepView.
*
* Cleans up any resources associated with the component.
*
* @return None.
* @pre None.
* @post Component is destructed, releasing associated resources.
* @author ataka
*/
StepView::~StepView()
{
    // No special cleanup required in the destructor
    step->removeObserver(this);
    step.release();
}


/**
* CreateSettingComponents
* This function initializes and sets up the components for the settings panel, including sliders for volume, pitch, and delay,
* as well as lock buttons for organic and reverb settings.
*
* @param none
* @return void
*
*/
void StepView::CreateSettingComponents()
{
    SettingContainer = std::make_unique<juce::Component>();
    SettingContainer->setBounds(0, 0, 200, 220);

    VolumeLabel.setText("Volume", juce::dontSendNotification);
    VolumeLabel.setBounds(10, 10, 100, 20);
    SettingContainer->addAndMakeVisible(VolumeLabel);

    VolumeSlider.setRange(0, 100, 1);
    VolumeSlider.setValue(50);
    VolumeValue = 50;
    VolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    VolumeSlider.setPopupDisplayEnabled(true, true, StepSettings.get());
    VolumeSlider.setTextValueSuffix("%");
    VolumeSlider.setBounds(10, 40, 180, 20);
    SettingContainer->addAndMakeVisible(VolumeSlider);

    PitchLabel.setText("Pitch", juce::dontSendNotification);
    PitchLabel.setBounds(10, 70, 100, 20);
    SettingContainer->addAndMakeVisible(PitchLabel);

    PitchSlider.setRange(-6, 6, 1);
    PitchSlider.setTextValueSuffix(" 8va");
    PitchSlider.setValue(0);
    PitchValue = 0;
    PitchSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    PitchSlider.setPopupDisplayEnabled(true, true, StepSettings.get());
    PitchSlider.setBounds(10, 100, 180, 20);
    SettingContainer->addAndMakeVisible(PitchSlider);

    DelayLabel.setText("Delay", juce::dontSendNotification);
    DelayLabel.setBounds(10, 130, 100, 20);
    SettingContainer->addAndMakeVisible(DelayLabel);

    DelaySlider.setRange(-0.20, 0.10, 0.01);
    DelaySlider.setTextValueSuffix(" ms");
    DelaySlider.setValue(0);
    DelayValue = 0;
    DelaySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    DelaySlider.setPopupDisplayEnabled(true, true, StepSettings.get());
    DelaySlider.setBounds(10, 160, 180, 20);
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
    OrganicLock = std::make_unique<LockButton>("Organic", LockIcon, UnlockIcon);
    OrganicLock->addListener(this);
    OrganicLock->setBounds(10, 190, 90, 20);
    buttonStyle(*OrganicLock);
    SettingContainer->addAndMakeVisible(OrganicLock.get());

    ReverbLock = std::make_unique<LockButton>("Reverb", LockIcon, UnlockIcon);
    ReverbLock->addListener(this);
    ReverbLock->setBounds(110, 190, 90, 20);
    buttonStyle(*ReverbLock);
    SettingContainer->addAndMakeVisible(ReverbLock.get());

    // Ensure all items in the container are visible
    SettingContainer->setVisible(true);

    StepSettings->addCustomComponent(SettingContainer.get());
}

/**
* buttonClicked
* This function handles the actions taken when different buttons in the settings panel are clicked.
*
* @param button The button that was clicked
* @return void
*
*/
void StepView::buttonClicked(juce::Button* button)
{
    if (button == StepSettings->getButton("Cancel"))
    {
        VolumeSlider.setValue(step.get()->getVolume());
        PitchSlider.setValue(step.get()->getPitch());
        DelaySlider.setValue(step.get()->getDelay());

        StepSettings->setVisible(false);
        StepSettings->exitModalState();

        // Change the colour of the step to the previous colour
        if (step->getStatus()) {
            StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(5, 74, 145));
        }
        else {
            StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(219, 228, 238));
        }
    }

    if (button == StepSettings->getButton("Reset"))
    {
        VolumeSlider.setValue(50);
        PitchSlider.setValue(0);
        DelaySlider.setValue(0);
        VolumeValue = 50;
        PitchValue = 0;
        DelayValue = 0;
    }

    if (button == StepSettings->getButton("Save"))
    {
        VolumeSlider.setValue(VolumeSlider.getValue());
        VolumeValue = VolumeSlider.getValue();

        PitchSlider.setValue(PitchSlider.getValue());
        PitchValue = PitchSlider.getValue();

        DelaySlider.setValue(DelaySlider.getValue());
        DelayValue = DelaySlider.getValue();

        step.get()->setVolume(VolumeValue);
        step.get()->setPitch(PitchValue);
        step.get()->setDelay(DelayValue);

        StepSettings->setVisible(false);
        StepSettings->exitModalState();

        // Change the colour of the step to the previous colour
        if (step->getStatus()) {
            StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(5, 74, 145));
        }
        else {
            StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(219, 228, 238));
        }
    }

    if (button == OrganicLock.get()) {
        if (OrganicLock->getState()) {
            OrganicLock->setState(false);
            step->setLock(Gparam::ORGANIC, false);
        }
        else {
            OrganicLock->setState(true);
            step->setLock(Gparam::ORGANIC, true);
        }
    }

    if (button == ReverbLock.get()) {
        if (ReverbLock->getState()) {
            ReverbLock->setState(false);
            step->setLock(Gparam::REVERB, false);
        }
        else {
            ReverbLock->setState(true);
            step->setLock(Gparam::REVERB, true);
        }
    }
}


/**
* mouseDown
* This function handles mouse click events on the step button. It updates the status and color of the step button based on
* whether the left or right mouse button was clicked.
*
* @param event The mouse event containing details of the mouse click
* @return void
*
*/
void StepView::mouseDown(const juce::MouseEvent& event)
{
    if (event.mods.isRightButtonDown() && event.originalComponent == StepButton.get())
    {
        // Change the colour of the step to be user friendly
        if (step->getStatus()) {
            StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(0, 180, 216));
        }
        else {
            StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(202, 240, 248));
        }

        // Ensure all components are visible
        VolumeSlider.setValue(step.get()->getVolume());
        PitchSlider.setValue(step.get()->getPitch());
        DelaySlider.setValue(step.get()->getDelay());

        StepSettings->setVisible(true);
        StepSettings->enterModalState(true);
    }

    if (event.mods.isLeftButtonDown() && event.originalComponent == StepButton.get())
    {
        // Change the status of the step
        step.get()->changeStepStatus();
    }
}




/**
* Paint function of StepView.
*
* Paints this component.
*
* @param g The Graphics context that must be used to do the drawing operations.
* @return None.
* @pre None.
* @post Component has been painted accordingly.
* @author ataka
*/
void StepView::paint(juce::Graphics& g)
{
    // Fill the background with dark grey color
    g.fillAll(juce::Colour(129, 164, 205));

}

/**
* Resized function of StepView.
*
* Resizes child components of this component.
*
* @return None.
* @pre Window needs to be resized.
* @post Child components have been resized accordingly.
* @author ataka
*/
void StepView::resized()
{
    // Set bounds for the button, leaving some margin
    StepButton->setBounds(2, 5, getWidth() - 5, getHeight() - 5);
}

/**
* StepView::setModels
* Sets the model for the step view.
*
* @param s Pointer to the Step model.
* @pre None.
* @post Sets the Step model and adds the StepView as an observer.
*/

void StepView::setModels(Step* s)
{
    step.reset(s);
    step->addObserver(this);
}

/**
* StepView::update
* Updates the step view based on the notification received from the Step model.
*
* @param id Identifier of the notification.
* @pre None.
* @post Updates the view based on the notification type.
*/
void StepView::update(int id)
{
    switch (id) {
        case 1:
            resetStep();
            break;
        case 2:
            changeOrganicLockState();
            break;
        case 3:
            changeReverbLockState();
            break;
        case 30:
            changeStepColor();
            break;
        default:
            break;
    }

    resized();

}

/**
* Changes the color of the step button based on its status.
* If the step is active, the button color is set to a specific shade of blue.
* If the step is inactive, the button color is set to a light gray.
*
* @pre The StepView instance must be properly initialized.
* @post The color of the step button is updated based on its status.
* @return None.
*
*/
void StepView::changeStepColor() {
    //change the colour of the step to the previous colour
    if (step->getStatus()) {
        StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(5, 74, 145));
    }
    else {
        StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(219, 228, 238));
    }
}



/**
* StepView::changeOrganicLockState
* Updates the state of the Organic Lock button based on the Step model.
*
* @pre None.
* @post Updates the state of the Organic Lock button.
*/

void StepView::changeOrganicLockState() {
    OrganicLock->setState(step->getLockState(Gparam::ORGANIC));
}

/**
* StepView::changeReverbLockState
* Updates the state of the Reverb Lock button based on the Step model.
*
* @pre None.
* @post Updates the state of the Reverb Lock button.
*/

void StepView::changeReverbLockState() {
    ReverbLock->setState(step->getLockState(Gparam::REVERB));
}

/**
* StepView::resetStep
* Resets the step view to its default state.
*
* @pre None.
* @post Resets the StepButton color and sets the sound name to "Empty".
*/

void StepView::resetStep()
{
    StepButton->setColour(juce::TextButton::buttonColourId, juce::Colour(219, 228, 238));
    setSoundName("Empty");
}

/**
* StepView::setSoundName
* Sets the name of the sound for the step view.
*
* @param name Name of the sound.
* @pre None.
* @post Sets the message for the StepSettings with the sound name.
*/

void StepView::setSoundName(juce::String name)
{
    juce::String desc = StepSettings->getDescription();
    int sep = desc.lastIndexOf(" ");
    juce::String Number = desc.substring(sep + 1, desc.length());
    StepSettings->setMessage("Settings for step " + name + " : " + Number);
}




