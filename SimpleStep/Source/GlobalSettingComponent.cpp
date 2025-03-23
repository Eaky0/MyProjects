/*
  ==============================================================================

    GlobalSettingComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "GlobalSettingComponent.h"

/**
* Constructor for GlobalSettingComponent.
*
* Initializes the editor with the given audio processor.
* Sets the size of the editor.
* Calls functions to create and add various components to the editor.
*
* @param p Reference to the StepSequencerAudioProcessor.
* @return None.
* @pre None.
* @post Editor is initialized with components added.
* @author Faruk Kazankaya
*/
GlobalSettingComponent::GlobalSettingComponent()
{
    createSwingComponents();
    createOrganicComponents();
    createBPMComponents();
    createReverbComponents();
    createRecentDropdownMenu();
    createChangesButton();
    createFilterComponents();
    createMasterVolumeSlider();

    // Set tooltips
    if (showToolTips) {
        bpmButton.setTooltip("Adjust the beats per minute (BPM) of the sequence.");
        swingButton.setTooltip("Adjust the swing of the sequence.");
        reverbButton.setTooltip("Apply reverb to the sound.");
        filtersButton.setTooltip("Apply a low- or high-pass filter with custom variables.");
        organicButton.setTooltip("Toggle organic sound mode. This makes your sequence sound more natural by applying subtle changes to the active steps' settings. Higher values result in more significant changes.");
        changesButton.setTooltip("View the changes made to your sequence by the organic filter.");
        recentDropdownMenu.setTooltip("Select from recently generated organic sequences.");
    }
    auto buttonStyle = [](juce::TextButton& button) {
        button.setColour(juce::TextButton::buttonColourId, juce::Colours::white); // Set button color
        button.setColour(juce::TextButton::textColourOnId, juce::Colours::white); // Set text color
        button.setColour(juce::TextButton::textColourOffId, juce::Colours::black); // Set text color
    };



   
    buttonStyle(reverbButton);
    buttonStyle(bpmButton);
   // buttonStyle(bpmapplyButton);
    buttonStyle(swingButton);
    buttonStyle(swingApplyButton);
    buttonStyle(organicButton);
    buttonStyle(changesButton);
    buttonStyle(filtersButton);


    recentDropdownMenu.setColour(juce::ComboBox::backgroundColourId, juce::Colours::white);
    recentDropdownMenu.setColour(juce::ComboBox::textColourId, juce::Colours::black);
    recentDropdownMenu.setColour(juce::ComboBox::arrowColourId, juce::Colours::black);


}

/**
* Destructor for GlobalSettingComponent.
*
* Cleans up any resources associated with the editor.
*
* @param None.
* @return None.
* @pre None.
* @post Editor is destructed, releasing associated resources.
* @author Faruk Kazankaya
*/
GlobalSettingComponent::~GlobalSettingComponent()
{
}


/**
* Paints the content of the editor.
*
* Fills the background of the editor with a solid color.
*
* @param g Reference to the Graphics context for drawing.
* @return None.
* @pre None.
* @post Editor's background is filled with a solid color.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(129, 164, 205));

    g.setColour(juce::Colour(219, 228, 238));
    g.drawRect(getLocalBounds(), 1.0f);
}

/**
* Handles the resizing of the GlobalSettingComponent.
*
* This function adjusts the layout of components within the GlobalSettingComponent,
* ensuring proper positioning and sizing according to the resized dimensions.
*
* @param None.
* @return None.
* @pre None.
* @post Components are appropriately laid out within the GlobalSettingComponent.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::resized()
{
    juce::Rectangle<int> flexBoxBounds(1, 1, getWidth(), getHeight() - 280);

    juce::FlexBox flexBox;
    flexBox.flexDirection = juce::FlexBox::Direction::row;
    flexBox.flexWrap = juce::FlexBox::Wrap::wrap;

    flexBox.items.add(juce::FlexItem(bpmButton).withMinWidth(85).withMinHeight(30).withMaxHeight(55).withMargin(juce::FlexItem::Margin(3)));
    flexBox.items.add(juce::FlexItem(swingButton).withMinWidth(85).withMinHeight(30).withMaxHeight(55).withMargin(juce::FlexItem::Margin(3)));
    flexBox.items.add(juce::FlexItem(reverbButton).withMinWidth(85).withMinHeight(30).withMaxHeight(55).withMargin(juce::FlexItem::Margin(3)));
    flexBox.items.add(juce::FlexItem(filtersButton).withMinWidth(85).withMinHeight(30).withMaxHeight(55).withMargin(juce::FlexItem::Margin(3)));
    flexBox.items.add(juce::FlexItem(organicButton).withMinWidth(85).withMinHeight(30).withMaxHeight(55).withMargin(juce::FlexItem::Margin(3)));
    flexBox.items.add(juce::FlexItem(changesButton).withMinWidth(85).withMinHeight(30).withMaxHeight(55).withMargin(juce::FlexItem::Margin(3)));
    flexBox.items.add(juce::FlexItem(recentDropdownMenu).withMinWidth(200).withMinHeight(30).withMaxHeight(55).withMargin(juce::FlexItem::Margin(3)));

    flexBox.performLayout(flexBoxBounds.toFloat());

    swingSlider.setBounds(110, 40, 200, 20);
    bpmEditor.setBounds(10, 40, 200, 20);
    swingApplyButton.setBounds(0, 40, 100, 20);
    //bpmapplyButton.setBounds(0, 40, 100, 20);

    //the psoitioning of our master volume slider and label
    int sliderWidth = 200;
    int sliderHeight = 40;
    int labelWidth = 100;
    int labelHeight = 20;
    int margin = 5;

    int sliderX = flexBoxBounds.getRight() - sliderWidth - margin;
    int sliderY = getHeight() - sliderHeight - margin;
    int labelX = sliderX;
    int labelY = sliderY - labelHeight - margin;

    masterVolumeLabel.setBounds(labelX, labelY, labelWidth, labelHeight);
    masterVolumeSlider.setBounds(sliderX, sliderY - 20, sliderWidth, sliderHeight);
}


/**
* Sets various models for managing settings.
*
* @param sound Pointer to SoundManager object.
* @param IO Pointer to IOManager object.
* @param organic Pointer to OrganicManager object.
* @param reverb Pointer to ReverbManager object.
* @param filterM Pointer to FilterManager object.
* @return None.
* @pre None.
* @post Models are set for managing settings.
*/
void GlobalSettingComponent::setModels(SoundManager* sound, IOManager* IO, OrganicManager * organic, ReverbManager* reverb, FilterManager* filterM)
{
    SoundM.reset(sound);
    SoundM->addObserver(this);
    IOMan.reset(IO);
    OrgMan.reset(organic);
    RevMan.reset(reverb);
    FilterM.reset(filterM);
}

/**
* Handles button click events.
*
* Depending on the button clicked, toggles visibility of associated components,
* applies BPM value, or prints debug messages for other buttons.
*
* @param button Pointer to the button clicked.
* @return None.
* @pre None.
* @post Depending on the button clicked, component visibility may change or debug messages are printed.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::buttonClicked(juce::Button* button)
{
    if (button == &swingButton && swingSlider.isVisible())
    {
        swingButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        hideComponents();
        return;
    }
    else if (button == &organicButton)
    {
        showOrganicPopup();
        return;
    }
    else if (button == &bpmButton && bpmEditor.isVisible())
    {
        bpmButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        hideComponents();
        return;
    }

    hideComponents();

    if (button == &swingButton)
    {
        bpmButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        organicButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        swingButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0, 150, 199));
        swingSlider.setValue(SoundM->getGParam(Gparam::SWING));
        swingSlider.setVisible(!swingSlider.isVisible());
        swingApplyButton.setVisible(swingSlider.isVisible());
    }
    else if (button == &swingApplyButton) {
        swingButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        SoundM->setGParam(swingSlider.getValue(), Gparam::SWING);

        std::vector<std::shared_ptr<Sound>> sounds = SoundM->getSounds();

        for (int index = 0; index < sounds.size(); ++index) {

            if (index % 2 == 0) {
                sounds[index]->applyGain(swingSlider.getValue(), 1);
            }
            else {
                sounds[index]->applyGain(swingSlider.getValue(), 0);
            }
        }

    }
    else if (button == &bpmButton)
    {
        organicButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        swingButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        bpmButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0, 150, 199));
        bpmEditor.setValue(SoundM->getGParam(Gparam::BPM));
        bpmEditor.setVisible(!bpmEditor.isVisible());
    }

    else if (button == &reverbButton)
    {
        swingButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        bpmButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        organicButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);

        RoomSizeSlider.setValue(RevMan->getRParam(RParam::ROOMSIZE));
        DampingSlider.setValue(RevMan->getRParam(RParam::DAMPING));
        DrySlider.setValue(RevMan->getRParam(RParam::DRY));
        WetSlider.setValue(RevMan->getRParam(RParam::WET));
        WidthSlider.setValue(RevMan->getRParam(RParam::WIDTH));


        reverbWindow->setVisible(true);
        reverbWindow->enterModalState();

        if (SoundM->isReverbed()) {
            reverbWindow->getButton(2)->setButtonText("ON");
            reverbWindow->getButton("Apply")->setEnabled(true);
            SoundM->setReverbStatus(true);
            reverbButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0, 150, 199));
        }
        else {
            reverbWindow->getButton(2)->setButtonText("OFF");
            reverbWindow->getButton("Apply")->setEnabled(false);
            SoundM->setReverbStatus(false);
            reverbButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        }

    }

    if (button == reverbWindow->getButton("Cancel"))
    {
        RoomSizeSlider.setValue(RevMan->getRParam(RParam::ROOMSIZE));
        DampingSlider.setValue(RevMan->getRParam(RParam::DAMPING));
        DrySlider.setValue(RevMan->getRParam(RParam::DRY));
        WetSlider.setValue(RevMan->getRParam(RParam::WET));
        WidthSlider.setValue(RevMan->getRParam(RParam::WIDTH));
        reverbWindow->setVisible(false);
        reverbWindow->exitModalState();
    }

    if (button == reverbWindow->getButton("Reset"))
    {
        RoomSizeSlider.setValue(0.5f);
        DampingSlider.setValue(0.5f);
        DrySlider.setValue(0.4f);
        WetSlider.setValue(0.33f);
        WidthSlider.setValue(1.0f);
    }


    if (button == reverbWindow->getButton(2))
    {
        if (reverbWindow->getButton(2)->getButtonText() == "OFF") {
            reverbWindow->getButton(2)->setButtonText("ON");
            reverbWindow->getButton("Apply")->setEnabled(true);
            SoundM->setReverbStatus(true);
            reverbButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0, 150, 199));
        }
        else {
            reverbWindow->getButton(2)->setButtonText("OFF");
            reverbWindow->getButton("Apply")->setEnabled(false);
            SoundM->setReverbStatus(false);
            reverbButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        }
    }


    if (button == reverbWindow->getButton("Apply"))
    {   
        RevMan->setRParam(RParam::ROOMSIZE, RoomSizeSlider.getValue());
        RevMan->setRParam(RParam::DAMPING, DampingSlider.getValue());
        RevMan->setRParam(RParam::DRY, DrySlider.getValue());
        RevMan->setRParam(RParam::WET, WetSlider.getValue());
        RevMan->setRParam(RParam::WIDTH, WidthSlider.getValue());

        RoomSizeSlider.setValue(RevMan->getRParam(RParam::ROOMSIZE));
        DampingSlider.setValue(RevMan->getRParam(RParam::DAMPING));
        DrySlider.setValue(RevMan->getRParam(RParam::DRY));
        WetSlider.setValue(RevMan->getRParam(RParam::WET));
        WidthSlider.setValue(RevMan->getRParam(RParam::WIDTH));

    }
    else if (button == &changesButton)
    {
        swingButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        bpmButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        organicButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        DBG("see changes button clicked");

        juce::String organicname = recentDropdownMenu.getText();

        juce::File organicDir;
#if defined(JUCE_MAC)
        juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

        organicDir = currentDir.getChildFile("Organic");
#else
        juce::File currentDir = juce::File::getCurrentWorkingDirectory();
        juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
        organicDir = grandParentDir.getChildFile("Organic");
#endif

        juce::File dataFile = organicDir.getChildFile(organicname);
        showOrganicDataPopup(dataFile);
        updatecontent();
    }
    else if (button == &filtersButton) {
        swingButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
        bpmButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);

        lowPassOnOffButton.setToggleState(FilterM->getLowPassStatus(), juce::dontSendNotification);
        highPassOnOffButton.setToggleState(FilterM->getHighPassStatus(), juce::dontSendNotification);
        lowPassFreqSlider.setValue(FilterM->getFParam(FParam::LOWFREQUENCY));
        highPassFreqSlider.setValue(FilterM->getFParam(FParam::HIGHFREQUENCY));
        lowPassQSlider.setValue(FilterM->getFParam(FParam::LOWQ));
        highPassQSlider.setValue(FilterM->getFParam(FParam::HIGHQ));

        FilterSettings->setVisible(true);
        FilterSettings->enterModalState();
    }
    else if (button == FilterSettings->getButton("Cancel"))
    {
        //Handle Cancel button click
        //set the values back to their previous
        lowPassOnOffButton.setToggleState(FilterM->getLowPassStatus(), juce::dontSendNotification);
        highPassOnOffButton.setToggleState(FilterM->getHighPassStatus(), juce::dontSendNotification);

        lowPassFreqSlider.setValue(FilterM->getFParam(FParam::LOWFREQUENCY), juce::dontSendNotification);
        highPassFreqSlider.setValue(FilterM->getFParam(FParam::HIGHFREQUENCY), juce::dontSendNotification);

        lowPassQSlider.setValue(FilterM->getFParam(FParam::LOWQ), juce::dontSendNotification);
        highPassQSlider.setValue(FilterM->getFParam(FParam::HIGHQ), juce::dontSendNotification);


        FilterSettings->setVisible(false);
        FilterSettings->exitModalState(0);
    }
    else if (button == FilterSettings->getButton("Reset"))
    {
        //Handle Reset button click
        //reset the values of the slider back to the standard
        lowPassFreqSlider.setValue(2000.0f);
        highPassFreqSlider.setValue(2000.0f);

        lowPassQSlider.setValue(0.707f);
        highPassQSlider.setValue(0.707f);

    }
    else if (button == FilterSettings->getButton("Save"))
    {
        //Handle Save button click

        //get the checkbox value of the filers and set them
        bool lowPassStatus = lowPassOnOffButton.getToggleState();
        FilterM->setFilterStatus(Gparam::LOWPASS, lowPassStatus);

        bool highPassStatus = highPassOnOffButton.getToggleState();
        FilterM->setFilterStatus(Gparam::HIGHPASS, highPassStatus);

        //get the values of the sliders for both the lowpass and the highpass and set them
        float lowPassFrequency = lowPassFreqSlider.getValue();
        float lowPassQ = lowPassQSlider.getValue();
        FilterM->setFParam(FParam::LOWFREQUENCY, lowPassFrequency);
        FilterM->setFParam(FParam::LOWQ, lowPassQ);

        float highPassFrequency = highPassFreqSlider.getValue();
        float highPassQ = highPassQSlider.getValue();
        FilterM->setFParam(FParam::HIGHFREQUENCY, highPassFrequency);
        FilterM->setFParam(FParam::HIGHQ, highPassQ);

        FilterSettings->setVisible(false);
        FilterSettings->exitModalState(1);
    }

    resized();
}

/**
* showOrganicDataPopup
* Displays a popup window showing saved organic changes.
*
* @param dataFile The file containing the saved organic changes.
* @pre None.
* @post Popup window is displayed with the saved organic changes.
* @return None.
*/
void GlobalSettingComponent::showOrganicDataPopup(const juce::File dataFile)
{
    juce::DialogWindow::LaunchOptions options;
    auto* savedDataPopup = new SavedDataPopupComponent(dataFile.getFullPathName());
    options.content.setOwned(savedDataPopup);
    options.dialogTitle = "Saved Organic Changes";
    options.dialogBackgroundColour = juce::Colours::darkgrey;
    options.escapeKeyTriggersCloseButton = true;
    options.useNativeTitleBar = false;
    options.resizable = true;

    options.launchAsync();
}

/**
* updatecontent
* Updates the content of the recentDropdownMenu with the list of recently generated organic sequences.
*
* @pre None.
* @post recentDropdownMenu is updated with the list of recently generated organic sequences.
* @return None.
*/
void GlobalSettingComponent::updatecontent()
{
    recentDropdownMenu.clear();
    recentDropdownMenu.addItem("none", 1);

    std::vector<juce::String> files = IOMan.get()->getRecentGen();
    for (int x = 0; x < files.size(); x++)
    {
        recentDropdownMenu.addItem(files[x], x + 2);
    }

    recentDropdownMenu.setSelectedId(1);
}

/**
* showOrganicPopup
* Displays a popup window for configuring organic settings.
* Allows the user to adjust organic parameters and apply changes.
*
* @pre None.
* @post Popup window for configuring organic settings is displayed.
* @return None.
*/
void GlobalSettingComponent::showOrganicPopup()
{
    juce::DialogWindow::LaunchOptions options;
    auto* organicPopup = new OrganicPopupComponent();
    organicPopup->onApply = [this, organicPopup]() {
        SoundM->setGParam(organicPopup->getOrganicSliderValue(), Gparam::ORGANIC);
        OrgMan->setOrganicView(organicPopup);
        OrgMan->applyOrganic();

        if (organicPopup->shouldSaveChanges()) {
            IOMan->WriteOrganicChanges();
            updatecontent();
        }

        if (auto* parent = organicPopup->findParentComponentOfClass<juce::DialogWindow>())
            parent->exitModalState(0);
        delete organicPopup;
    };
    options.content.setOwned(organicPopup);
    options.dialogTitle = "Organic Settings";
    options.dialogBackgroundColour = juce::Colours::darkgrey;
    options.escapeKeyTriggersCloseButton = true;
    options.useNativeTitleBar = false;
    options.resizable = true;

    options.launchAsync();
}

/**
* hideComponents
* Hides specific components of the GlobalSettingComponent.
*
* @pre None.
* @post Specific components of the GlobalSettingComponent are hidden.
* @return None.
*/
void GlobalSettingComponent::hideComponents()
{
    swingSlider.setVisible(false);
    swingApplyButton.setVisible(false);
    bpmEditor.setVisible(false);
}


/**
* Handles slider value changed events.
*
* Prints debug messages indicating the change in slider values.
*
* @param slider Pointer to the slider whose value changed.
* @return None.
* @pre None.
* @post Debug messages are printed indicating the change in slider values.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &swingSlider)
    {
        DBG("swing slider changed : " << slider->getValue());
    }

    if (slider == &bpmEditor) {
        applyBPM();
    }

    //change the volume of all the steps using the sounds in every page
    if (slider == &masterVolumeSlider) {

        if (!SoundM)
        {
            return;
        }

        SoundM->setGParam(masterVolumeSlider.getValue(), Gparam::MASTERVOLUME);

        std::vector<std::shared_ptr<Sound>> sounds = SoundM->getSounds();

        for (auto s : sounds) {
            for (int i = 0; i < SoundM->getPages(); i++) {
                s->setSoundParam(i, masterVolumeSlider.getValue(), Sparam::VOLUME);
            }
        }
    }
}




/**
* Applies the BPM value retrieved from the text editor.
*
* Retrieves the BPM value from the text editor, converts it to a double, and applies it.
* Prints the applied BPM value to the debug output.
*
* @param None.
* @return None.
* @pre Text editor contains a valid BPM value.
* @post BPM value is applied.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::applyBPM()
{
    // Retrieve BPM value from text editor and apply it
    double bpmValue = bpmEditor.getValue();
    if(!SoundM)
    {
        return;
    }
    SoundM->setGParam(bpmValue, Gparam::BPM);

    // Print the applied BPM value to debug output
    DBG("BPM Applied: " << bpmValue);
}

/**
* Callback function called when the value of a ComboBox changes.
*
* Handles the ComboBox change event and performs actions accordingly.
*
* @param comboBox Pointer to the ComboBox that triggered the change event.
* @return None.
* @pre None.
* @post Action performed based on the ComboBox selection.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::comboBoxChanged(juce::ComboBox* comboBox)
{
    if (comboBox == &recentDropdownMenu)
    {
        int selectedItemIndex = comboBox->getSelectedItemIndex();
        switch (selectedItemIndex)
        {
        case 0:
            break;
        case 1:
            break;
        case 2:
            break;
        }
        DBG("Combobox changed to " << selectedItemIndex);
    }
}

/**
* changeToolTipStatus
* Changes the status of tooltips for various buttons and components within the GlobalSettingComponent.
*
* @param status The new status of the tooltips (true for enabled, false for disabled).
* @pre None.
* @post Tooltips for buttons and components are either enabled or disabled based on the provided status.
* @return None.
*/
void GlobalSettingComponent::changeToolTipStatus(bool status)
{
    showToolTips = status;
    if (showToolTips) {
        bpmButton.setTooltip("Adjust the beats per minute (BPM) of the sequence.");
        swingButton.setTooltip("Adjust the swing of the sequence.");
        reverbButton.setTooltip("Apply reverb to the sound.");
        filtersButton.setTooltip("Apply a low- or high-pass filter with custom variables.");
        organicButton.setTooltip("Toggle organic sound mode. This makes your sequence sound more natural by applying subtle changes to the active steps' settings. Higher values result in more significant changes.");
        changesButton.setTooltip("View the changes made to your sequence by the organic filter.");
        recentDropdownMenu.setTooltip("Select from recently generated organic sequences.");
    }
    else {
        bpmButton.setTooltip("");
        swingButton.setTooltip("");
        reverbButton.setTooltip("");
        filtersButton.setTooltip("");
        organicButton.setTooltip("");
        changesButton.setTooltip("");
        recentDropdownMenu.setTooltip("");
    }

    SoundM->changeToolTipStatus(status);
}


void GlobalSettingComponent::update(int id)
{
    switch (id) {
    case 31:
        changeReverbColor();
        break;
    case 35:
        changeBPMText();
        break;
    }

    resized();
}

/**
* Creates and adds swing components to the editor.
*
* @param None.
* @return None.
* @pre None.
* @post Swing components are added to the editor.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::createSwingComponents()
{
    addAndMakeVisible(swingButton);
    swingButton.setButtonText("Swing");
    swingButton.addListener(this);

    addAndMakeVisible(swingSlider);
    swingSlider.setRange(0, 10, 1);
    swingSlider.setValue(0);
    swingSlider.addListener(this);
    swingSlider.setVisible(false);
    swingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    swingSlider.setPopupDisplayEnabled(true, true, this);
    swingSlider.setTextValueSuffix("");

    addAndMakeVisible(swingApplyButton);
    swingApplyButton.setButtonText("Apply");
    swingApplyButton.addListener(this);
    swingApplyButton.setVisible(false);
}

/**
* Creates and adds organic components to the editor.
*
* @param None.
* @return None.
* @pre None.
* @post Organic components are added to the editor.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::createOrganicComponents()
{
    addAndMakeVisible(organicButton);
    organicButton.setButtonText("Organic");
    organicButton.addListener(this);
}

/**
* Creates and adds BPM components to the editor.
*
* @param None.
* @return None.
* @pre None.
* @post BPM components are added to the editor.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::createBPMComponents()
{
    addAndMakeVisible(bpmButton);
    bpmButton.setButtonText("BPM");
    bpmButton.addListener(this);

    addAndMakeVisible(bpmEditor);
    bpmEditor.setVisible(false);
    bpmEditor.addListener(this);
    bpmEditor.setSliderStyle(juce::Slider::IncDecButtons);
    bpmEditor.setRange(30, 300, 1);
    bpmEditor.setValue(120);
    

    /*addAndMakeVisible(bpmapplyButton);
    bpmapplyButton.setButtonText("Apply");
    bpmapplyButton.setVisible(false);
    bpmapplyButton.addListener(this);*/
}

/**
* Creates and adds reverb components to the editor.
*
* @param None.
* @return None.
* @pre None.
* @post Reverb components are added to the editor.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::createReverbComponents()
{


    auto buttonStyle = [](juce::Button* button) {
        button->setColour(juce::TextButton::buttonColourId, juce::Colours::white); // Set button color
        button->setColour(juce::TextButton::textColourOnId, juce::Colours::black); // Set text color
        button->setColour(juce::TextButton::textColourOffId, juce::Colours::black); // Set text color

    };


    reverbWindow = std::make_unique<juce::AlertWindow>("Reverb",
        "", juce::MessageBoxIconType::NoIcon);
    reverbWindow->addButton("Cancel", 0);
    reverbWindow->getButton("Cancel")->addListener(this);
    buttonStyle(reverbWindow->getButton("Cancel"));

    reverbWindow->addButton("Reset", 1);
    reverbWindow->getButton("Reset")->addListener(this);
    buttonStyle(reverbWindow->getButton("Reset"));

    reverbWindow->addButton("OFF", 2);
    reverbWindow->getButton("OFF")->addListener(this);
    buttonStyle(reverbWindow->getButton("OFF"));

    reverbWindow->addButton("Apply", 3);
    reverbWindow->getButton("Apply")->setEnabled(false);
    reverbWindow->getButton("Apply")->addListener(this);
    buttonStyle(reverbWindow->getButton("Apply"));


    reverbWindow->setColour(juce::AlertWindow::backgroundColourId, juce::Colour(129, 164, 205));
    reverbWindow->setColour(juce::AlertWindow::outlineColourId, juce::Colour(219, 228, 238));

    reverbContainer = std::make_unique<juce::Component>();
    reverbContainer->setBounds(0, 0, 200, 300);
    
    //Room Size
    RoomSizeLabel.setText("Room size", juce::dontSendNotification);
    RoomSizeLabel.setBounds(10, 10, 100, 20);
    reverbContainer->addAndMakeVisible(RoomSizeLabel);

    RoomSizeSlider.setRange(0, 1, 0.01);
    RoomSizeSlider.setValue(0.5f);
    RoomSizeSlider.addListener(this);
    RoomSizeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    RoomSizeSlider.setPopupDisplayEnabled(true, true, reverbWindow.get());
    RoomSizeSlider.setBounds(10, 40, 180, 20);
    reverbContainer->addAndMakeVisible(RoomSizeSlider);

    //Damping
    DampingLabel.setText("Damping", juce::dontSendNotification);
    DampingLabel.setBounds(10, 70, 100, 20);
    reverbContainer->addAndMakeVisible(DampingLabel);

    DampingSlider.setRange(0.0f, 1.0f, 0.01f);
    DampingSlider.setValue(0.5f);
    DampingSlider.addListener(this);
    DampingSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    DampingSlider.setPopupDisplayEnabled(true, true, reverbWindow.get());
    DampingSlider.setBounds(10, 100, 180, 20);
    reverbContainer->addAndMakeVisible(DampingSlider);

    //Wet
    WetLabel.setText("Wet level", juce::dontSendNotification);
    WetLabel.setBounds(10, 130, 100, 20);
    reverbContainer->addAndMakeVisible(WetLabel);

    WetSlider.setRange(0.0f, 1.0f, 0.01f);
    WetSlider.setValue(0.33f);
    WetSlider.addListener(this);
    WetSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    WetSlider.setPopupDisplayEnabled(true, true, reverbWindow.get());
    WetSlider.setBounds(10, 160, 180, 20);
    reverbContainer->addAndMakeVisible(WetSlider);
    
    //Dry
    DryLabel.setText("Dry level", juce::dontSendNotification);
    DryLabel.setBounds(10, 190, 100, 20);
    reverbContainer->addAndMakeVisible(DryLabel);

    DrySlider.setRange(0.0f, 1.0f, 0.01f);
    DrySlider.setValue(0.4f);
    DrySlider.addListener(this);
    DrySlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    DrySlider.setPopupDisplayEnabled(true, true, reverbWindow.get());
    DrySlider.setBounds(10, 220, 180, 20);
    reverbContainer->addAndMakeVisible(DrySlider);

    //Width
    WidthLabel.setText("Width", juce::dontSendNotification);
    WidthLabel.setBounds(10, 250, 100, 20);
    reverbContainer->addAndMakeVisible(WidthLabel);

    WidthSlider.setRange(0.0f, 1.0f, 0.01f);
    WidthSlider.setValue(0.5f);
    WidthSlider.addListener(this);
    WidthSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    WidthSlider.setPopupDisplayEnabled(true, true, reverbWindow.get());
    WidthSlider.setBounds(10, 280, 180, 20);
    reverbContainer->addAndMakeVisible(WidthSlider);

    // Ensure all items in the container are visible
    reverbContainer->setVisible(true);
    reverbWindow->addCustomComponent(reverbContainer.get());

    reverbButton.setButtonText("Reverb");
    reverbButton.addListener(this);
    addAndMakeVisible(reverbButton);

}

/**
* Creates and adds dropdown menu to the editor.
*
* @param None.
* @return None.
* @pre None.
* @post Dropdown menu is added to the editor.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::createRecentDropdownMenu()
{
    addAndMakeVisible(recentDropdownMenu);
    recentDropdownMenu.setText("recente generaties (3)");
    recentDropdownMenu.addItem("none", 1);
    recentDropdownMenu.setLookAndFeel(&PopUpMenuDesign);
    std::vector<juce::String> files = IOMan.get()->getRecentGen();
    for (int x = 0; x < files.size(); x++)
    {
        recentDropdownMenu.addItem(files[x], x+2);
    }
    recentDropdownMenu.setSelectedId(1);
    recentDropdownMenu.addListener(this);
}

/**
* Creates and adds changes button to the editor.
*
* @param None.
* @return None.
* @pre None.
* @post Changes button is added to the editor.
* @author Faruk Kazankaya
*/
void GlobalSettingComponent::createChangesButton()
{
    addAndMakeVisible(changesButton);
    changesButton.setButtonText("See changes");
    changesButton.addListener(this);
}

/**
 * Creates filter components for the GlobalSettingComponent.
 *
 * Initializes and configures UI elements for controlling filter settings,
 * including buttons, sliders, and labels.
 *
 * @pre None.
 * @post Filter components are created and added to the GUI.
 * @param None.
 * @return None.
 */
void GlobalSettingComponent::createFilterComponents()
{
    // Set up the Filters button
    filtersButton.setButtonText("Filters");
    filtersButton.addListener(this);
    addAndMakeVisible(filtersButton);

    auto buttonStyle = [](juce::Button* button) {
        button->setColour(juce::TextButton::buttonColourId, juce::Colours::white); // Set button color
        button->setColour(juce::TextButton::textColourOffId, juce::Colours::black); // Set text color
        };

    // Create AlertWindow for filter settings
    FilterSettings = std::make_unique<juce::AlertWindow>(
        "Filter Settings",
        "Adjust the filter settings below:",
        juce::AlertWindow::NoIcon);

    FilterSettings->addButton("Cancel", 0);
    FilterSettings->getButton("Cancel")->addListener(this);
    buttonStyle(FilterSettings->getButton("Cancel"));

    FilterSettings->addButton("Reset", 1);
    FilterSettings->getButton("Reset")->addListener(this);
    buttonStyle(FilterSettings->getButton("Reset"));

    FilterSettings->addButton("Save", 2);
    FilterSettings->getButton("Save")->addListener(this);
    buttonStyle(FilterSettings->getButton("Save"));

    // Set colors for the alert window
    FilterSettings->setColour(juce::AlertWindow::backgroundColourId, juce::Colour(129, 164, 205));
    FilterSettings->setColour(juce::AlertWindow::outlineColourId, juce::Colour(219, 228, 238));

    // Create a container for filter components
    FilterContainer = std::make_unique<juce::Component>();
    FilterContainer->setBounds(0, 0, 250, 330);

    // Add low-pass filter components
    lowPassLabel.setText("Low Pass Filter", juce::dontSendNotification);
    lowPassLabel.setBounds(10, 10, 150, 20);
    FilterContainer->addAndMakeVisible(lowPassLabel);

    lowPassOnOffButton.setButtonText("On/Off");
    lowPassOnOffButton.setBounds(170, 10, 60, 20);
    FilterContainer->addAndMakeVisible(lowPassOnOffButton);

    lowPassFreqLabel.setText("Frequency", juce::dontSendNotification);
    lowPassFreqLabel.setBounds(10, 40, 100, 20);
    FilterContainer->addAndMakeVisible(lowPassFreqLabel);

    lowPassFreqSlider.setRange(0, 22050, 100);
    lowPassFreqSlider.setValue(2000.0f);
    lowPassFreqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    lowPassFreqSlider.setBounds(10, 70, 220, 20);
    lowPassFreqSlider.setPopupDisplayEnabled(true, true, FilterSettings.get());
    FilterContainer->addAndMakeVisible(lowPassFreqSlider);

    lowPassQLabel.setText("Q", juce::dontSendNotification);
    lowPassQLabel.setBounds(10, 100, 100, 20);
    FilterContainer->addAndMakeVisible(lowPassQLabel);

    lowPassQSlider.setRange(0.001, 100);
    lowPassQSlider.setValue(0.707f);
    lowPassQSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    lowPassQSlider.setBounds(10, 130, 220, 20);
    lowPassQSlider.setPopupDisplayEnabled(true, true, FilterSettings.get());
    FilterContainer->addAndMakeVisible(lowPassQSlider);

    // Add high-pass filter components
    highPassLabel.setText("High Pass Filter", juce::dontSendNotification);
    highPassLabel.setBounds(10, 170, 150, 20);
    FilterContainer->addAndMakeVisible(highPassLabel);

    highPassOnOffButton.setButtonText("On/Off");
    highPassOnOffButton.setBounds(170, 170, 60, 20);
    FilterContainer->addAndMakeVisible(highPassOnOffButton);

    highPassFreqLabel.setText("Frequency", juce::dontSendNotification);
    highPassFreqLabel.setBounds(10, 200, 100, 20);
    FilterContainer->addAndMakeVisible(highPassFreqLabel);

    highPassFreqSlider.setRange(0, 22050, 100);
    highPassFreqSlider.setValue(2000.0f);
    highPassFreqSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    highPassFreqSlider.setBounds(10, 230, 220, 20);
    highPassFreqSlider.setPopupDisplayEnabled(true, true, FilterSettings.get());
    FilterContainer->addAndMakeVisible(highPassFreqSlider);

    highPassQLabel.setText("Q", juce::dontSendNotification);
    highPassQLabel.setBounds(10, 260, 100, 20);
    FilterContainer->addAndMakeVisible(highPassQLabel);

    highPassQSlider.setRange(0.001, 100);
    highPassQSlider.setValue(0.707f);
    highPassQSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    highPassQSlider.setBounds(10, 290, 220, 20);
    highPassQSlider.setPopupDisplayEnabled(true, true, FilterSettings.get());
    FilterContainer->addAndMakeVisible(highPassQSlider);

    // Ensure all items in the container are visible
    FilterContainer->setVisible(true);

    // Add the container to the alert window
    FilterSettings->addCustomComponent(FilterContainer.get());
}


/**
 * Creates the master volume slider component.
 *
 * Adds and configures a slider and its corresponding label for controlling
 * the master volume.
 *
 * @pre None.
 * @post Master volume slider component is created and added to the GUI.
 * @param None.
 * @return None.
 */
void GlobalSettingComponent::createMasterVolumeSlider()
{
    //define the label for the master volume
    masterVolumeLabel.setText("Master Volume", juce::dontSendNotification);
    masterVolumeLabel.setJustificationType(juce::Justification::centredLeft);
    addAndMakeVisible(masterVolumeLabel);

    //define the slider for the master volume
    addAndMakeVisible(masterVolumeSlider);
    masterVolumeSlider.addListener(this);
    masterVolumeSlider.setRange(0, 100, 1);
    masterVolumeSlider.setValue(50);
    masterVolumeSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    masterVolumeSlider.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
    masterVolumeSlider.setPopupDisplayEnabled(true, true, this);
}

void GlobalSettingComponent::changeReverbColor()
{
    if (SoundM->isReverbed()) {
        reverbButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0, 150, 199));
    }
    else {
        reverbButton.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    }
}

void GlobalSettingComponent::changeBPMText()
{
    bpmEditor.setValue(SoundM->getGParam(Gparam::BPM));
}





