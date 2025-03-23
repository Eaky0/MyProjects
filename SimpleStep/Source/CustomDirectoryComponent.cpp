/*
  ==============================================================================

    CustomDirectoryComponent.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "CustomDirectoryComponent.h"

CustomDirectoryComponent::CustomDirectoryComponent(bool showBackButton = true) : showBackButton(showBackButton)
{
    if (showBackButton) {
        addAndMakeVisible(backButton);
        backButton.addListener(this);
        backButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2e4a62));
        backButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    }
    
    addAndMakeVisible(addButton);
    addButton.addListener(this);
    addButton.setColour(juce::TextButton::buttonColourId, juce::Colour(0xff2e4a62));
    addButton.setColour(juce::TextButton::textColourOffId, juce::Colours::white);
    addButton.setEnabled(false); // Initially disabled

    addAndMakeVisible(currentDirLabel);
    currentDirLabel.setJustificationType(juce::Justification::centredLeft);
    currentDirLabel.setColour(juce::Label::textColourId, juce::Colours::white);
    currentDirLabel.setColour(juce::Label::backgroundColourId, juce::Colour(0xff2e4a62));

    addAndMakeVisible(errorLabel);
    errorLabel.setJustificationType(juce::Justification::centred);
    errorLabel.setColour(juce::Label::textColourId, juce::Colours::red);

    fileList.setModel(&fileListModel);
    addAndMakeVisible(fileList);

    setDirectory(juce::File::getSpecialLocation(juce::File::userHomeDirectory));
}

CustomDirectoryComponent::~CustomDirectoryComponent()
{
    if (showBackButton) {
        backButton.removeListener(this);
    }
    addButton.removeListener(this);
}

/**
* setDirectory
* Sets the current directory and updates the file list.
*
* @param directory The directory to be set as the current directory.
* @pre directory is a valid juce::File object representing a directory.
* @post The current directory is set and the file list is updated.
*/
void CustomDirectoryComponent::setDirectory(const juce::File& directory)
{
    currentDirectory = directory;
    currentDirLabel.setText("Current Directory: " + directory.getFullPathName(), juce::dontSendNotification);
    updateFileList();
}

/**
* getSelectedFile
* Returns the currently selected file in the file list.
*
* @return The selected juce::File object, or an invalid file if no selection.
* @pre None.
* @post Returns the selected file if a valid selection is made, otherwise returns an invalid file.
*/
juce::File CustomDirectoryComponent::getSelectedFile() const
{
    int selectedRow = fileList.getSelectedRow();
    if (selectedRow >= 0 && selectedRow < files.size())
        return files[selectedRow];

    return juce::File();
}

/**
* paint
* Paints the background of the component.
*
* @param g The graphics context to use for painting.
* @pre g is a valid juce::Graphics object.
* @post The background of the component is painted.
*/
void CustomDirectoryComponent::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(0xff4b7299)); // Background color similar to the app
}

/**
* resized
* Resizes and positions the child components.
*
* @pre None.
* @post The child components are resized and positioned within the component.
*/
void CustomDirectoryComponent::resized()
{
    int padding = 10;
    int labelHeight = 30;
    int buttonHeight = 30;
    int errorLabelHeight = 30;
    int listHeight = getHeight() - (4 * padding + labelHeight + buttonHeight + errorLabelHeight);

    if (showBackButton) {
        backButton.setBounds(padding, padding, getWidth() / 2 - 2 * padding, buttonHeight);
        addButton.setBounds(getWidth() / 2 + padding, padding, getWidth() / 2 - 2 * padding, buttonHeight);
        currentDirLabel.setBounds(padding, backButton.getBottom() + padding, getWidth() - 2 * padding, labelHeight);
    }
    else {
        addButton.setBounds(padding, padding, getWidth() - 2 * padding, buttonHeight);
        currentDirLabel.setBounds(padding, addButton.getBottom() + padding, getWidth() - 2 * padding, labelHeight);
    }

    fileList.setBounds(padding, currentDirLabel.getBottom() + padding, getWidth() - 2 * padding, listHeight);
    errorLabel.setBounds(padding, fileList.getBottom() + padding, getWidth() - 2 * padding, errorLabelHeight);
}

/**
* updateFileList
* Updates the file list with the contents of the current directory.
*
* @pre currentDirectory is set to a valid directory.
* @post The file list is updated with the files and directories in the current directory.
*/
void CustomDirectoryComponent::updateFileList()
{
    files.clear();
    files.addArray(currentDirectory.findChildFiles(juce::File::findFilesAndDirectories, false));
    fileList.updateContent();
}

/**
* buttonClicked
* Handles button click events.
*
* @param button The button that was clicked.
* @pre button is a valid pointer to a juce::Button object.
* @post Handles the click event based on which button was clicked.
*/
void CustomDirectoryComponent::buttonClicked(juce::Button* button)
{
    if (button == &backButton && currentDirectory != currentDirectory.getParentDirectory())
    {
        setDirectory(currentDirectory.getParentDirectory());
    }
    else if (button == &addButton)
    {
        // Perform the action when the Add button is clicked
        juce::File selectedFile = getSelectedFile();
        if (selectedFile.existsAsFile())
        {
#if defined(JUCE_MAC)
            if (selectedFile.hasFileExtension(".wav"))
            {
                // Valid file, close the component
                errorLabel.setText("", juce::dontSendNotification);
                addButtonClicked = true;
                if (auto* dialogWindow = findParentComponentOfClass<juce::DialogWindow>())
                {
                    dialogWindow->exitModalState(0);
                }
            }
#else
            if (selectedFile.hasFileExtension(".wav;.mp3"))
            {
                // Valid file, close the component
                errorLabel.setText("", juce::dontSendNotification);
                addButtonClicked = true;
                if (auto* dialogWindow = findParentComponentOfClass<juce::DialogWindow>())
                {
                    dialogWindow->exitModalState(0);
                }
            }
#endif
            else if (selectedFile.hasFileExtension(".json") && !showBackButton) {
                // Valid file, close the component
                errorLabel.setText("", juce::dontSendNotification);
                addButtonClicked = true;
                if (auto* dialogWindow = findParentComponentOfClass<juce::DialogWindow>())
                {
                    dialogWindow->exitModalState(0);
                }
            }
            else
            {
                // Invalid file, show error message
                errorLabel.setText("This isn't a valid sound file!", juce::dontSendNotification);
            }
        }
    }
}

CustomDirectoryComponent::FileListModel::FileListModel(CustomDirectoryComponent& parent)
    : owner(parent)
{
}

/**
* getNumRows
* Returns the number of rows in the file list.
*
* @return The number of rows in the file list.
* @pre None.
* @post Returns the number of files in the current directory.
*/
int CustomDirectoryComponent::FileListModel::getNumRows()
{
    return owner.files.size();
}

/**
* paintListBoxItem
* Paints each item in the file list.
*
* @param rowNumber The row number to paint.
* @param g The graphics context to use for painting.
* @param width The width of the item to paint.
* @param height The height of the item to paint.
* @param rowIsSelected True if the row is selected, false otherwise.
* @pre g is a valid juce::Graphics object, rowNumber is within bounds.
* @post The item at rowNumber is painted.
*/
void CustomDirectoryComponent::FileListModel::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected)
{
    if (rowIsSelected)
        g.fillAll(juce::Colours::lightblue);

    if (rowNumber < owner.files.size())
    {
        juce::File file = owner.files[rowNumber];
        if (file.isDirectory())
        {
            g.setColour(juce::Colour(0xff2e4a62));
            g.fillRect(0, 0, width, height);
            g.setColour(juce::Colours::white);
        }
        else
        {
            g.setColour(juce::Colours::white); // Ensure consistency
        }

        g.drawText(file.getFileName(), 10, 0, width - 20, height, juce::Justification::centredLeft);

        g.setColour(juce::Colours::black);
        g.drawLine(0, height - 1, width, height - 1); // Draw a black line between items
    }
}

/**
* listBoxItemClicked
* Handles item click events in the file list.
*
* @param row The row number that was clicked.
* @param e The mouse event associated with the click.
* @pre row is within bounds.
* @post Handles the click event for the item at row.
*/
void CustomDirectoryComponent::FileListModel::listBoxItemClicked(int row, const juce::MouseEvent& e)
{
    if (row < owner.files.size())
    {
        juce::File selectedFile = owner.files[row];
        if (selectedFile.isDirectory())
        {
            owner.setDirectory(selectedFile);
        }
    }
}

/**
* selectedRowsChanged
* Handles the change in selection of rows in the file list.
*
* @param lastRowSelected The last row that was selected.
* @pre None.
* @post Enables the Add button if an item is selected.
*/
void CustomDirectoryComponent::FileListModel::selectedRowsChanged(int lastRowSelected)
{
    // Enable the Add button only if an item is selected
    owner.addButton.setEnabled(owner.fileList.getSelectedRow() != -1);
}
