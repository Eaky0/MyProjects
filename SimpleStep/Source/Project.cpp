/*
  ==============================================================================

    Project.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "Project.h"

/**
* Project
* Constructor for the Project class.
*
* @pre None.
* @post Initializes instances of various manager classes used in the project.
*
*/
Project::Project()
{
    OrganicManagerModel = new OrganicManager();
    ReverbManagerModel = new ReverbManager();
    SoundManagerModel = new SoundManager();
    IOManagerModel = new IOManager(&projectName);
    FilterManagerModel = new FilterManager();
    SoundLibraryModel = std::make_shared<SoundLibrary>();
    PlayerModel = new Player();

    PlayerModel->setModels(SoundManagerModel, ReverbManagerModel, FilterManagerModel);
    IOManagerModel->setSoundManager(SoundManagerModel, SoundLibraryModel);
    IOManagerModel->setReverbManager(ReverbManagerModel);
    IOManagerModel->setFilterManager(FilterManagerModel);
    OrganicManagerModel->setSMPtr(SoundManagerModel);
}

/**
* ~Project
* Destructor for the Project class.
*
* @pre None.
* @post Deallocates memory used by instances of various manager classes.
*
*/
Project::~Project()
{
    delete SoundManagerModel;
    delete OrganicManagerModel;
    delete ReverbManagerModel;
    delete IOManagerModel;
    delete FilterManagerModel;
    delete PlayerModel;
}

/**
* getPlayer
* Retrieves a pointer to the Player instance.
*
* @pre None.
* @post None.
* @return A pointer to the Player instance.
*
*/
Player* Project::getPlayer()
{
    return PlayerModel;
}

/**
* getSoundManager
* Retrieves a pointer to the SoundManager instance.
*
* @pre None.
* @post None.
* @return A pointer to the SoundManager instance.
*
*/
SoundManager* Project::getSoundManager()
{
    return SoundManagerModel;
}

/**
* getIOmanager
* Retrieves a pointer to the IOManager instance.
*
* @pre None.
* @post None.
* @return A pointer to the IOManager instance.
*
*/
IOManager* Project::getIOmanager()
{
    return IOManagerModel;
}

/**
* getOrganicManager
* Retrieves a pointer to the OrganicManager instance.
*
* @pre None.
* @post None.
* @return A pointer to the OrganicManager instance.
*
*/
OrganicManager* Project::getOrganicManager()
{
    return OrganicManagerModel;
}

/**
* getReverbManager
* Retrieves a pointer to the ReverbManager instance.
*
* @pre None.
* @post None.
* @return A pointer to the ReverbManager instance.
*
*/
ReverbManager* Project::getReverbManager()
{
    return ReverbManagerModel;
}

/**
* getFilterManager
* Retrieves a pointer to the FilterManager instance.
*
* @pre None.
* @post None.
* @return A pointer to the FilterManager instance.
*
*/
FilterManager* Project::getFilterManager()
{
    return FilterManagerModel;
}

/**
* getSoundLibrary
* Retrieves a shared pointer to the SoundLibrary instance.
*
* @pre None.
* @post None.
* @return A shared pointer to the SoundLibrary instance.
*
*/
std::shared_ptr<SoundLibrary> Project::getSoundLibrary()
{
    return SoundLibraryModel;
}

void Project::startinitialise()
{
    PlayerModel->initializePlayerPoolAsync();
}
