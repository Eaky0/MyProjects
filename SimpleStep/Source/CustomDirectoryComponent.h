/*
  ==============================================================================

    CustomDirectoryComponent.h

    Component to show a custom directory.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class CustomDirectoryComponent : public juce::Component,
    public juce::Button::Listener
{
public:
    CustomDirectoryComponent() { showBackButton = true; };
    CustomDirectoryComponent(bool showBackButton);
    ~CustomDirectoryComponent() override;

    void setDirectory(const juce::File& directory);
    juce::File getSelectedFile() const;
    bool wasAddButtonClicked() const { return addButtonClicked; }

    void paint(juce::Graphics& g) override;
    void resized() override;

private:
    void updateFileList();
    void buttonClicked(juce::Button* button) override;

    juce::File currentDirectory;
    juce::TextButton backButton{ "Back" };
    juce::TextButton addButton{ "Add" };
    juce::Label currentDirLabel{ {}, "Current Directory: " };
    juce::Label errorLabel{ {}, "" };
    juce::ListBox fileList;
    juce::Array<juce::File> files;

    bool showBackButton;
    bool addButtonClicked = false;

    class FileListModel : public juce::ListBoxModel
    {
    public:
        FileListModel(CustomDirectoryComponent& parent);
        int getNumRows() override;
        void paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) override;
        void listBoxItemClicked(int row, const juce::MouseEvent& e) override;
        void selectedRowsChanged(int lastRowSelected) override;

    private:
        CustomDirectoryComponent& owner;
    };

    FileListModel fileListModel{ *this };
};
