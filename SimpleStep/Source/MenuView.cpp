/*
  ==============================================================================

    MenuView.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>
#include "MenuView.h"

void MenuView::setModels(Player* audio, IOManager* io, GlobalSettingComponent* globalSettings)
{
    AudioManager = std::make_shared<Player>();
    ioManager = std::make_shared<IOManager>();
    AudioManager.reset(audio);
    ioManager.reset(io);
    ioManager->addObserver(this);

    this->globalSettings = globalSettings;
}

/**
 * MenuView
 * Constructor for MenuView. Initializes the components and sets the initial size.
 *
 * @pre None
 * @post Components are created and the size is set to 600x100.
 */
MenuView::MenuView()
{
    createComponents();
    setSize(600, 100);
}

/**
 * ~MenuView
 * Destructor for MenuView.
 *
 * @pre None
 * @post Any resources used by MenuView are cleaned up.
 */
MenuView::~MenuView()
{
}

/**
 * paint
 * Paints the background and border of the MenuView.
 *
 * @param g The graphics context used for drawing.
 * @pre None
 * @post The background is filled and the border is drawn.
 */
void MenuView::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(129, 164, 205));
    g.setColour(juce::Colour(219, 228, 238));
    g.drawRect(getLocalBounds(), 1.0f);
}

/**
 * resized
 * Resizes and positions the buttons within the MenuView.
 *
 * @pre None
 * @post The buttons are positioned within the bounds of the MenuView.
 */
void MenuView::resized()
{
    auto bounds = getLocalBounds();
    const int buttonWidth = 120;
    const int buttonHeight = 60;

    fileButton.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));
    settingsButton.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));
    clearButton.setBounds(bounds.removeFromLeft(buttonWidth).reduced(5));

    startStopButton->setBounds(bounds.removeFromRight(buttonWidth).reduced(5));
    recordButton->setBounds(bounds.removeFromRight(buttonWidth).reduced(5));
}

/**
 * buttonClicked
 * Handles button click events.
 *
 * @param button The button that was clicked.
 * @pre None
 * @post The appropriate action is taken based on which button was clicked.
 */
void MenuView::buttonClicked(juce::Button* button)
{
    if (button == &fileButton)
    {
        openFileMenu();
    }
    else if (button == &clearButton)
    {
        openClearMenu();
    }
    else if (button == recordButton.get())
    {
        bool isRecording = recordButton->getButtonText() == "Recording";
        recordButton->setButtonText(isRecording ? "Record" : "Recording");
        recordButton->setState(!isRecording);
    }
    else if (button == startStopButton.get())
    {
        bool isPlaying = startStopButton->getButtonText() == "Start";
        startStopButton->setButtonText(isPlaying ? "Stop" : "Start");
        (isPlaying ? AudioManager->playSequence() : AudioManager->stopSequence());
        startStopButton->setState(isPlaying);
    }
    else if (button == &settingsButton)
    {
        openSettingsMenu();
    }
}

/**
 * createComponents
 * Creates and initializes the buttons and other components within the MenuView.
 *
 * @pre None
 * @post The components are created and added to the view.
 */
void MenuView::createComponents()
{
    auto buttonStyle = [](juce::TextButton& button, const juce::String& text) {
        button.setButtonText(text);
        button.setSize(120, 60); // Set button size explicitly
        button.setLookAndFeel(nullptr); // Reset look and feel to default
        button.setColour(juce::TextButton::buttonColourId, juce::Colours::white); // Set button color
        button.setColour(juce::TextButton::textColourOnId, juce::Colours::black); // Set text color
        button.setColour(juce::TextButton::textColourOffId, juce::Colours::black); // Set text color
        button.setConnectedEdges(0); // Make it rectangular
    };

    addAndMakeVisible(fileButton);
    buttonStyle(fileButton, "File");
    fileButton.addListener(this);

    addAndMakeVisible(clearButton);
    buttonStyle(clearButton, "Clear");
    clearButton.addListener(this);

    juce::File resourceDir;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    resourceDir = currentDir.getChildFile("resource");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    resourceDir = grandParentDir.getChildFile("resource");

#endif

    juce::File recordIconFile("");
    juce::File recordingIconFile(resourceDir.getChildFile("recording.jpg").getFullPathName());
    auto recordIcon = juce::ImageFileFormat::loadFrom(recordIconFile);
    auto recordingIcon = juce::ImageFileFormat::loadFrom(recordingIconFile);

    recordButton = std::make_unique<IconButton>("Record", recordIcon, recordingIcon);
    buttonStyle(*recordButton, "Record");
    recordButton->addListener(this);
    addAndMakeVisible(*recordButton);

    addAndMakeVisible(settingsButton);
    buttonStyle(settingsButton, "Settings");
    settingsButton.addListener(this);


    juce::File playIconFile(resourceDir.getChildFile("play.png").getFullPathName());
    juce::File pauseIconFile(resourceDir.getChildFile("pause.png").getFullPathName());

    auto playIcon = juce::ImageFileFormat::loadFrom(playIconFile);
    auto pauseIcon = juce::ImageFileFormat::loadFrom(pauseIconFile);

    startStopButton = std::make_unique<IconButton>("Start", playIcon, pauseIcon);
    buttonStyle(*startStopButton, "Start");
    startStopButton->addListener(this);
    addAndMakeVisible(*startStopButton);
}

/**
 * openFileMenu
 * Opens the file menu.
 *
 * @pre None
 * @post The file menu is displayed.
 */
void MenuView::openFileMenu()
{
    juce::PopupMenu fileMenu;
    fileMenu.setLookAndFeel(&PopUpMenuDesign);


    fileMenu.addItem("New File", [this]() { ioManager->newProject(); });
    fileMenu.addItem("Open File...", [this]() { openLoadProjectDialog(); });
    fileMenu.addItem("Save File", [this]() { ioManager->saveFile(AudioManager); });

    fileMenu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&fileButton));

    fileMenu.setLookAndFeel(nullptr);

}

/**
 * SpacebarPressed
 * Handles the spacebar key press event.
 *
 * @param key The key press event.
 * @pre None
 * @post The start/stop button is clicked if the spacebar is pressed.
 */
void MenuView::SpacebarPressed(const juce::KeyPress& key)
{
    if (key == juce::KeyPress::spaceKey)
    {
        buttonClicked(startStopButton.get());
    }
}

/**
 * showAlertWindow
 * Displays an alert window for the user to enter a project name.
 *
 * @pre None
 * @post The project name is obtained from the user or the alert window is redisplayed if the input is invalid.
 */
void MenuView::showAlertWindow()
{
    // Create the alert window to ask the user for a project name
    juce::AlertWindow projectNameWindow("Save Project", "Enter the project name:", juce::AlertWindow::QuestionIcon);
    projectNameWindow.addTextEditor("projectName", "project_name");
    projectNameWindow.addButton("OK", 1, juce::KeyPress(juce::KeyPress::returnKey));
    projectNameWindow.addButton("Cancel", 0, juce::KeyPress(juce::KeyPress::escapeKey));

    projectNameWindow.setColour(juce::AlertWindow::backgroundColourId, juce::Colour(129, 164, 205));
    projectNameWindow.setColour(juce::AlertWindow::outlineColourId, juce::Colour(219, 228, 238));

    // Is "OK" clicked
    if (projectNameWindow.runModalLoop() == 1) {
        juce::String projectFileName = projectNameWindow.getTextEditor("projectName")->getText();

        // Check if empty
        if (projectFileName.isEmpty()) {
            juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon, "Error", "Please enter a project name!");
            return showAlertWindow();
        }
        else if (projectFileName == "template") {
            juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon, "Error", "This name is not permitted to use");
            return showAlertWindow();
        }
        else {
            // Check if the file already exists in the folder
            juce::File projectDir = juce::File::getCurrentWorkingDirectory().getParentDirectory().getParentDirectory().getChildFile("Projects");
            juce::File outputFile = projectDir.getChildFile(projectFileName + ".json");

            if (outputFile.existsAsFile()) {
                // File already exists, show a warning message and prompt again
                juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon, "Error", "A project with the same name already exists. Please choose a different name.");
                return showAlertWindow();
            }
            else {
                // Proceed
                ioManager->setProjectName(projectFileName);
            }
        }
    }
    else {
        // The user cancelled the operation
        return;
    }
}

/**
 * update
 * Updates the MenuView based on the provided id.
 *
 * @param id The id indicating what to update.
 * @pre None
 * @post The appropriate update action is performed based on the id.
 */
void MenuView::update(int id)
{
    switch (id) {
    case 20:
        showAlertWindow();
        break;
    }
}

/**
 * openClearMenu
 * Opens the clear menu with options to clear steps, sounds, settings, or all.
 *
 * @pre None
 * @post The clear menu is displayed.
 */
void MenuView::openClearMenu()
{
    juce::PopupMenu ClearMenu;
    ClearMenu.setLookAndFeel(&PopUpMenuDesign);


    ClearMenu.addItem("Clear Steps", [this]() { AudioManager->resetSteps(); });
    ClearMenu.addItem("Clear Sounds", [this]() { AudioManager->resetSounds();  });
    ClearMenu.addItem("Clear Settings", [this]() { AudioManager->resetSettings(); });
    ClearMenu.addItem("Clear All", [this]() {
        AudioManager->resetSteps();
    AudioManager->resetSounds();
    AudioManager->resetSettings();
        });

    ClearMenu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&clearButton));
    ClearMenu.setLookAndFeel(nullptr);
}

/**
 * openSettingsMenu
 * Opens the settings menu with options to enable/disable tooltips and add a new instrument.
 *
 * @pre None
 * @post The settings menu is displayed.
 */
void MenuView::openSettingsMenu()
{
    String toolText = globalSettings->areTooltipsEnabled() ? "Disable tooltips" : "Enable tooltips";
    bool toolTipStatus = globalSettings->areTooltipsEnabled();

    juce::PopupMenu SettingsMenu;

    SettingsMenu.setLookAndFeel(&PopUpMenuDesign);

    SettingsMenu.addItem(toolText, [this, toolTipStatus]() { globalSettings->changeToolTipStatus(!toolTipStatus); });
    SettingsMenu.addItem("Add a new instrument", [this]() { openAddSoundDialog(); });

    SettingsMenu.showMenuAsync(juce::PopupMenu::Options().withTargetComponent(&settingsButton));

    SettingsMenu.setLookAndFeel(nullptr);
}

/**
 * openAddSoundDialog
 * Opens a dialog for the user to select a sound file to add to the library.
 *
 * @pre None
 * @post The selected sound file is added to the library.
 */
void MenuView::openAddSoundDialog()
{
    juce::File initialDir = juce::File::getSpecialLocation(juce::File::userHomeDirectory);
    CustomDirectoryComponent directoryComponent(true);
    directoryComponent.setDirectory(initialDir);

    juce::DialogWindow::LaunchOptions options;
    options.content.setNonOwned(&directoryComponent);
    options.dialogTitle = "Select a File";
    options.dialogBackgroundColour = juce::Colour(0xff4b7299);
    options.escapeKeyTriggersCloseButton = true;
    options.useNativeTitleBar = true;
    options.resizable = false;
    options.useBottomRightCornerResizer = false;

    directoryComponent.setSize(400, 600);

    options.runModal();

    if (directoryComponent.wasAddButtonClicked())
    {
        juce::File selectedFile = directoryComponent.getSelectedFile();
        ioManager->addSoundtoLib(selectedFile);
    }
}

void MenuView::openLoadProjectDialog()
{
    // Define the projects directory
    juce::File projectDir;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    projectDir = currentDir.getChildFile("Projects");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    projectDir = grandParentDir.getChildFile("Projects");
#endif

    CustomDirectoryComponent directoryComponent(false); // False so we disable the back button
    directoryComponent.setDirectory(projectDir);

    juce::DialogWindow::LaunchOptions options;
    options.content.setNonOwned(&directoryComponent);
    options.dialogTitle = "Select a Project File";
    options.dialogBackgroundColour = juce::Colour(0xff4b7299);
    options.escapeKeyTriggersCloseButton = true;
    options.useNativeTitleBar = true;
    options.resizable = false;
    options.useBottomRightCornerResizer = false;

    directoryComponent.setSize(400, 600);

    options.runModal();

    if (directoryComponent.wasAddButtonClicked())
    {
        juce::File selectedFile = directoryComponent.getSelectedFile();
        ioManager->loadProject(selectedFile);
    }
}