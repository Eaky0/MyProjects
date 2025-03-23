/*
  ==============================================================================

    SoundLibraryView.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "SoundLibraryView.h"

/**
* SoundLibraryView constructor
* Constructs a SoundLibraryView object.
*
* @pre None
* @post SoundLibraryView object is constructed
*/
SoundLibraryView::SoundLibraryView()
{
    setLookAndFeel(&PopupMenuDesign);
}

/**
* MakeVisible function
* Ensures that the Sound Library Window is visible on the GUI.
*
* @return None
* @pre None
* @post The user can now add or change a sound
* @author Atakan Kumas
*/
void SoundLibraryView::MakeVisible()
{
    showMenuAsync(juce::PopupMenu::Options());
}

/**
* ButtonClicked function
* Handles button click events.
*
* @param button The button that was clicked
* @pre None
* @post None
*/
void SoundLibraryView::buttonClicked(juce::Button* button)
{

}

/**
* Paint function
* Paints the component.
*
* @param g The Graphics context to use for painting
* @pre None
* @post The component is painted
*/
void SoundLibraryView::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::lightgrey); // Set the background color here
}

/**
* SoundLibraryView destructor
* Destroys the SoundLibraryView object.
*
* @pre None
* @post SoundLibraryView object is destroyed
*/
SoundLibraryView::~SoundLibraryView()
{
    setLookAndFeel(nullptr);
}

/**
* setSelected function
* Sets the selected sound.
*
* @param s Pointer to the selected sound
* @pre None
* @post The selected sound is set
*/
void SoundLibraryView::setSelected(Sound* s)
{
    if (SelectedSound == nullptr) {
        SelectedSound = std::make_unique<Sound>("Empty");
    }

    if (SelectedSound.get() != s) {
        SelectedSound.release();
        SelectedSound.reset(s);
    }
}

/**
* setModels function
* Sets the models for the SoundLibraryView.
*
* @param play Pointer to the Player model
* @param library Pointer to the SoundLibrary model
* @pre None
* @post Models are set for the SoundLibraryView
*/
void SoundLibraryView::setModels(Player* play, SoundLibrary* library)
{

    SoundLibraryModel = library;

    std::vector<juce::File> Files = SoundLibraryModel->getSoundList();

    for (juce::File& file : Files) {
        Items.add(file.getFileNameWithoutExtension());
    }

    int numItems = Items.size();
    int columnSize = (numItems + 2) / 3; // Split items into 3 columns

    int index = 0;
    for (const auto& item : Items)
    {
        addItem(item, [this, item]() {
            SelectedSound.get()->setSoundName(item);



            });

        ++index;
        if (index % columnSize == 0 && index != numItems)
            addColumnBreak();
    }

    juce::String NoSound = "None";
    addItem(NoSound, [this, NoSound]() {
        SelectedSound.get()->setSoundName("Empty");



        });

    library->addObserver(this);
}

/**
* Update function
* Updates the SoundLibraryView with a new sound file.
*
* @param file The new sound file to update with
* @pre None
* @post SoundLibraryView is updated with the new sound file
*/
void SoundLibraryView::update(juce::File file)
{
    DBG("hello");
    Items.add(file.getFileNameWithoutExtension());

    clear();

    int numItems = Items.size();
    int columnSize = (numItems + 2) / 3;

    int index = 0;
    for (const auto& item : Items)
    {
        addItem(item, [this, item]() {
            SelectedSound.get()->setSoundName(item);


            });

        ++index;
        if (index % columnSize == 0 && index != numItems)
            addColumnBreak();
    }

    juce::String NoSound = "None";
    addItem(NoSound, [this, NoSound]() {
        SelectedSound.get()->setSoundName("Empty");


        });
}

