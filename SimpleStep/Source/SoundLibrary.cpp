/*
  ==============================================================================

    SoundLibrary.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "SoundLibrary.h"

/**
* SoundLibrary constructor
* Constructs a SoundLibrary object and initializes it by scanning the directory for sound files.
*
* @pre None
* @post SoundLibrary object is constructed and initialized with sound files from the directory
*/
SoundLibrary::SoundLibrary()
{
    juce::File Exporter = juce::File::getCurrentWorkingDirectory();
    DBG("Current Working Directory: " << Exporter.getFullPathName());

    juce::File Workspace;
    juce::File Builds;
    //MacOS
    if (Exporter.getFullPathName() == "/")
    {
        Exporter = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();
        DBG("Adjusted Working Directory: " << Exporter.getFullPathName());

        LibDirectory = Exporter.getChildFile("Sound Library");
        DBG("Resources Directory: " << LibDirectory.getFullPathName());

    }
    else {
        Builds = Exporter.getParentDirectory();
        DBG("Current Working Directory: " << Builds.getFullPathName());


        Workspace = Builds.getParentDirectory();
        DBG("Current Working Directory: " << Workspace.getFullPathName());

        LibDirectory = Workspace.getChildFile("Sound Library");
        DBG("Resources Directory: " << LibDirectory.getFullPathName());
    }

    if (LibDirectory.isDirectory())
    {
        juce::DirectoryIterator iter(LibDirectory, false);

        while (iter.next())
        {
            juce::File file = iter.getFile();


#if defined(JUCE_MAC)
            if (file.getFileExtension() == ".wav")
                Sounds.push_back(file);

#else
            Sounds.push_back(file);
#endif

        }
    }
    else
    {
        DBG("Directory Sound Library was not found!");
    }
}

/**
* UpdateYourLib function
* Updates the SoundLibrary with a new sound file and notifies the observers.
*
* @param file The new sound file to add to the library
* @pre None
* @post SoundLibrary is updated with the new sound file and observers are notified
*/
void SoundLibrary::updateYourLib(juce::File file)
{
    addSoundToList(file);
    notifyObservers(file);
}

/**
* AddSoundToList function
* Adds a new sound file to the SoundLibrary.
*
* @param file The sound file to add to the library
* @pre None
* @post The sound file is added to the SoundLibrary
*/
void SoundLibrary::addSoundToList(juce::File file)
{
    Sounds.push_back(file);
}

/**
* GetSoundList function
* Retrieves the list of sound files in the SoundLibrary.
*
* @pre None
* @post None
* @return A vector containing all the sound files in the library
*/
std::vector<juce::File> SoundLibrary::getSoundList() {
    return Sounds;
}

/**
* SoundLibrary destructor
* Destroys the SoundLibrary object.
*
* @pre None
* @post SoundLibrary object is destroyed
*/
SoundLibrary::~SoundLibrary()
{

}
