/*
  ==============================================================================

    IOManager.h

    This class is responsible for writing to and reading from files.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AbstractObservable.h"
#include "SoundManager.h"
#include "SoundLibrary.h"
#include "PlayClass.h"

class IOManager : public AbstractObservable
{
public:
    IOManager() {};
	IOManager(String * projName);
	~IOManager();

    void addSoundtoLib(juce::File selectedFile);
    void addSoundtoFolder(juce::File file);
    void setSoundManager(SoundManager* manager, std::shared_ptr<SoundLibrary> soundLibraryModel);
    void setReverbManager(ReverbManager* manager);
    void setFilterManager(FilterManager* manager);
    void WriteOrganicChanges();
    void saveFile(std::shared_ptr<Player> audioManager);
    void newProject();
    void loadProject(const juce::File& projectFile);
    void setProjectName(const juce::String& name);
    std::vector<juce::String> getRecentGen();
private:
    std::shared_ptr<SoundManager> SoundM;
    std::shared_ptr<ReverbManager> ReverbM;
    std::shared_ptr<FilterManager> FilterM;
    std::shared_ptr<SoundLibrary> SoundLIB;
    String* projectName;
    bool isTemplate = false;
};

