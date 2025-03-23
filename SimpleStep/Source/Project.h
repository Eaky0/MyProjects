/*
  ==============================================================================

    Project.h

    This class is the central hub where all objects are instantiated and configured. 
    It is the core of the application where everything is initialized.

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include <JuceHeader.h>

#include "SoundManager.h"
#include "OrganicManager.h"
#include "IOclass.h"
#include "PlayClass.h"
#include "SoundLibrary.h"
#include "ReverbManager.h"

#pragma once

class Project
{
public:
    Project();
    ~Project();


    Player* getPlayer();
    SoundManager* getSoundManager();
    IOManager* getIOmanager();
    OrganicManager* getOrganicManager();
    ReverbManager* getReverbManager();
    FilterManager* getFilterManager();
    std::shared_ptr<SoundLibrary> getSoundLibrary();

    void startinitialise();
private:
    OrganicManager* OrganicManagerModel;
    IOManager* IOManagerModel;
    ReverbManager* ReverbManagerModel;
    FilterManager* FilterManagerModel;
    Player* PlayerModel;
    SoundManager* SoundManagerModel;
    std::shared_ptr<SoundLibrary> SoundLibraryModel;
    String projectName = "";
};