/*
  ==============================================================================

    IOManager.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "IOClass.h"
#include <JuceHeader.h>
using namespace juce;

/**
* IOManager constructor
* Constructs an IOManager object.
*
* @param projName A pointer to the project name string.
* @pre None.
* @post An IOManager object is created with a SoundManager instance and a project name.
* @return None.
*/
IOManager::IOManager(String* projName)
{
    SoundM = std::make_shared<SoundManager>();
    projectName = projName;
}

/**
* IOManager destructor
* Destructs an IOManager object.
*
* @param None.
* @pre None.
* @post None.
* @return None.
*/
IOManager::~IOManager()
{

}


/*
 * Sets the SoundManager instance to be used by the IOManager.
 * 
 * @param manager Pointer to the SoundManager instance to be set.
 * @return None.
 * 
 * @pre The pointer 'manager' must not be null.
 * @post The SoundManager instance used by the IOManager is set to the specified 'manager'.
 * 
 */
void IOManager::setSoundManager(SoundManager* manager, std::shared_ptr<SoundLibrary> soundLibraryModel)
{
    SoundM.reset(manager);
    SoundLIB = soundLibraryModel;
}

/**
 * Sets the ReverbManager for the IOManager.
 *
 * Updates the ReverbManager used by the IOManager.
 *
 * @param manager A pointer to the new ReverbManager.
 * @pre None.
 * @post The ReverbManager is updated to the provided manager.
 * @return None.
 */
void IOManager::setReverbManager(ReverbManager* manager)
{
    ReverbM.reset(manager);
}

/**
 * Sets the FilterManager for the IOManager.
 *
 * Updates the FilterManager used by the IOManager.
 *
 * @param manager A pointer to the new FilterManager.
 * @pre None.
 * @post The FilterManager is updated to the provided manager.
 * @return None.
 */
void IOManager::setFilterManager(FilterManager* manager)
{
    FilterM.reset(manager);
}

/**
* Retrieves the names of the three most recent organic generation files.
*
* @param None.
* @pre None.
* @post Returns a vector containing the names of the three most recent organic generation files.
* @return A vector of strings containing the names of the recent organic generation files.
*/
std::vector<juce::String> IOManager::getRecentGen()
{
    std::vector<juce::String> files;

    juce::File organicDir;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    organicDir = currentDir.getChildFile("Organic");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    organicDir = grandParentDir.getChildFile("Organic");
#endif

    if (organicDir.isDirectory())
    {
        std::vector<juce::File> allFiles;

        // Iterate through the files in the directory, filtering for .json files
        for (juce::DirectoryIterator iter(organicDir, false, "*.json", juce::File::findFiles); iter.next();)
        {
            allFiles.push_back(iter.getFile());
        }

        // Sort the files by modification time, most recent first
        std::sort(allFiles.begin(), allFiles.end(), [](const juce::File& a, const juce::File& b) {
            return a.getLastModificationTime() > b.getLastModificationTime();
            });

        // Get the three most recent files
        for (int i = 0; i < std::min(static_cast<int>(allFiles.size()), 3); ++i)
        {
            files.push_back(allFiles[i].getFileName());
        }
    }
    else
    {
        DBG("Organic Directory was not found!");
    }

    return files;
}

/**
* Adds a sound file to the Sound Library directory.
*
* @param file The file to be added to the Sound Library directory.
* @pre The file exists.
* @post The file is copied to the Sound Library directory if it doesn't already exist there.
* @return None.
*/
void IOManager::addSoundtoFolder(juce::File file)
{
    juce::File libDirectory;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    libDirectory = currentDir.getChildFile("Sound Library");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    libDirectory = grandParentDir.getChildFile("Sound Library");
#endif

    if (!libDirectory.exists())
    {
        bool directoryCreated = libDirectory.createDirectory();
        if (directoryCreated)
        {
            juce::Logger::writeToLog("Sound Library directory created.");
        }
        else
        {
            juce::Logger::writeToLog("Failed to create Sound Library directory.");
            return;
        }
    }

    juce::File destinationFile = libDirectory.getChildFile(file.getFileName());
    if (file.copyFileTo(destinationFile))
    {
        juce::Logger::writeToLog("File copied successfully to: " + destinationFile.getFullPathName());
    }
    else
    {
        juce::Logger::writeToLog("Failed to copy file to: " + destinationFile.getFullPathName());
    }
}

/**
* Adds a sound file to the Sound Library.
*
* @param selectedFile The selected sound file to be added to the Sound Library.
* @pre The selected file exists and has a valid extension (.wav or .mp3).
* @post The selected file is added to the Sound Library.
* @return None.
*/
void IOManager::addSoundtoLib(juce::File selectedFile)
{
    if (selectedFile.existsAsFile() && selectedFile.hasFileExtension(".wav;.mp3"))
    {
        DBG(selectedFile.getFileName());
        addSoundtoFolder(selectedFile);
        SoundLIB->updateYourLib(selectedFile);
        juce::Logger::writeToLog("Sound file added: " + selectedFile.getFullPathName());
    }
    else
    {
        juce::Logger::writeToLog("Selected file does not exist.");
    }
}


/**
* Writes the organic changes data to a JSON file.
*
* @param None.
* @pre SoundM and its associated objects are properly initialized.
* @post The organic changes data is saved to a JSON file in the Organic directory.
* @return None.
*/
void IOManager::WriteOrganicChanges()
{
    // Create a DynamicObject object to store the data
    std::unique_ptr<juce::DynamicObject> jsonData = std::make_unique<juce::DynamicObject>();

    int numSounds = SoundM->getRows();
    int numPages = SoundM->getPages();

    // Iterate through each sound
    for (int i = 0; i < numSounds; ++i)
    {
        Sound* sound = SoundM->getSoundAt(i);
        // Create a DynamicObject object to store sound data
        std::unique_ptr<juce::DynamicObject> soundData = std::make_unique<juce::DynamicObject>();

        // Get sound name
        juce::String soundName = sound->getSoundName();

        // Get number of steps for the sound
        int numSteps = SoundM->getSteps();

        juce::Array<juce::var> PageData;

        // Create a JSON array to store step data
        for (int page = 0; page < numPages; ++page)
        {
            std::unique_ptr<juce::DynamicObject> Page = std::make_unique<juce::DynamicObject>();
            juce::Array<juce::var> stepsData;

            // Iterate through each step
            for (int i = 0; i < numSteps; ++i)
            {
                // Get step at index i
                Step* step = sound->getStepAt(page, i);

                // Create a DynamicObject to store step properties
                std::unique_ptr<juce::DynamicObject> stepProperties = std::make_unique<juce::DynamicObject>();
                stepProperties->setProperty("Status", step->getStatus());
                stepProperties->setProperty("volume", step->getVolume());
                stepProperties->setProperty("Delay", step->getDelay());
                stepProperties->setProperty("pitch", step->getPitch());
                stepProperties->setProperty("Manipulated", step->getManipulated());

                // Convert DynamicObject to var
                juce::var stepVar(stepProperties.get());

                // Add step properties to stepsData array
                stepsData.add(stepVar);

                stepProperties.release();
                delete stepProperties.get();
            }

            // Add StepData to Page
            Page->setProperty(juce::String("Page ") + std::to_string(page + 1), juce::var(stepsData));
            juce::var PageVar(Page.get());
            PageData.add(PageVar);
            Page.release();
            delete Page.get();
        }

        // Add sound data to jsonData
        soundData->setProperty("name", juce::var(soundName));
        soundData->setProperty("pages", juce::var(PageData));

        juce::var soundVar(soundData.get());
        jsonData->setProperty(soundName + "_" + std::to_string(i), soundVar);
        soundData.release();
        delete soundData.get();
    }

    juce::File organicDir;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    organicDir = currentDir.getChildFile("Organic");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    organicDir = grandParentDir.getChildFile("Organic");
#endif

    // Ensure the directory exists
    if (!organicDir.exists())
    {
        organicDir.createDirectory();
    }

    // Get the current time
    juce::String timeStamp = juce::Time::getCurrentTime().formatted("%Y-%m-%d_%H-%M-%S");

    // Create the filename based on the current date and time
    juce::String filename = "organic_output_" + timeStamp + ".json";

    // Combine the directory path with the filename
    juce::File outputFile = organicDir.getChildFile(filename);
    juce::FileOutputStream outputStream(outputFile);

    if (outputStream.openedOk())
    {
        juce::JSON::writeToStream(outputStream, juce::var(jsonData.get()), true);
        outputStream.flush();
    }
    else
    {
        // Handle file opening error
        std::cerr << "Error opening file location" << std::endl;
    }

    jsonData.release();
    delete jsonData.get();
}



/**
* Saves the project data to a JSON file.
*
* @param audioManager A shared pointer to the Player object.
* @pre The SoundM and its associated objects are properly initialized.
* @post The project data is saved to a JSON file in the Projects directory.
* @return None.
*/
void IOManager::saveFile(std::shared_ptr<Player> audioManager)
{
    juce::File projectDir;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    projectDir = currentDir.getChildFile("Projects");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    projectDir = grandParentDir.getChildFile("Projects");
#endif

    // Ensure the directory exists
    if (!projectDir.exists())
    {
        projectDir.createDirectory();
    }

    juce::String projectFileName;

    //check if the project has a name or not
    if (projectName->compare("") == 0) {
        //this is a new project
        // notify the observers to show the alertwindow
        notifyObservers(20);
        if (projectName->compare("") == 0) {
            return;
        }
        projectFileName = *projectName;
    }
    else {
        //we overwrite the existing file
        projectFileName = *projectName;
    }

    //get the general info
    int steps = SoundM->getSteps();
    int pages = SoundM->getPageCount();
    int rows = SoundM->getRows();
    int currentPage = SoundM->getCurrentPage();
    int currentColumn = SoundM->getCurrentPlayingColumn();
    int currentPlayingPage = SoundM->getCurrentPlayingPage();
    float masterVolume = SoundM->getGParam(Gparam::MASTERVOLUME);
    bool toolTipStatus = SoundM->getToolTipStatus();

    //get the global settings
    float bpm = SoundM->getGParam(Gparam::BPM);
    float swing = SoundM->getGParam(Gparam::SWING);

    //get the reverb settings
    auto reverbManager = audioManager->getReverbManager();
    float roomSize = reverbManager->getRParam(RParam::ROOMSIZE);
    float damping = reverbManager->getRParam(RParam::DAMPING);
    float width = reverbManager->getRParam(RParam::WIDTH);
    float dry = reverbManager->getRParam(RParam::DRY);
    float wet = reverbManager->getRParam(RParam::WET);
    bool isReverbed = SoundM->isReverbed();

    //get the filter settings
    auto filterManager = audioManager->getFilterManager();
    float lowFrequency = filterManager->getFParam(FParam::LOWFREQUENCY);
    float highFrequency = filterManager->getFParam(FParam::HIGHFREQUENCY);
    float lowQ = filterManager->getFParam(FParam::LOWQ);
    float highQ = filterManager->getFParam(FParam::HIGHQ);
    bool lowPassActive = filterManager->getLowPassStatus();
    bool highPassActive = filterManager->getHighPassStatus();

    //rootObject is used to hold all of the data
    std::unique_ptr<juce::DynamicObject> rootObject = std::make_unique<juce::DynamicObject>();

    //add the global settings
    std::unique_ptr<juce::DynamicObject> globalSettings = std::make_unique<juce::DynamicObject>();
    globalSettings->setProperty("BPM", bpm);
    globalSettings->setProperty("Swing", swing);
    rootObject->setProperty("GlobalSettings", juce::var(globalSettings.get()));
    globalSettings.release();
    delete globalSettings.get();

    //add the reverb settings
    std::unique_ptr<juce::DynamicObject> reverbSettings = std::make_unique<juce::DynamicObject>();
    reverbSettings->setProperty("RoomSize", roomSize);
    reverbSettings->setProperty("Damping", damping);
    reverbSettings->setProperty("Width", width);
    reverbSettings->setProperty("Dry", dry);
    reverbSettings->setProperty("Wet", wet);
    reverbSettings->setProperty("IsReverbed", isReverbed);
    rootObject->setProperty("ReverbSettings", juce::var(reverbSettings.get()));
    reverbSettings.release();
    delete reverbSettings.get();

    //add the filter settings
    std::unique_ptr<juce::DynamicObject> filterSettings = std::make_unique<juce::DynamicObject>();
    filterSettings->setProperty("LowFrequency", lowFrequency);
    filterSettings->setProperty("HighFrequency", highFrequency);
    filterSettings->setProperty("LowQ", lowQ);
    filterSettings->setProperty("HighQ", highQ);
    filterSettings->setProperty("LowPassActive", lowPassActive);
    filterSettings->setProperty("HighPassActive", highPassActive);
    rootObject->setProperty("FilterSettings", juce::var(filterSettings.get()));
    filterSettings.release();
    delete filterSettings.get();

    //add the general info
    rootObject->setProperty("steps", steps);
    rootObject->setProperty("pages", pages);
    rootObject->setProperty("rows", rows);
    rootObject->setProperty("currentPage", currentPage);
    rootObject->setProperty("currentColumn", currentColumn);
    rootObject->setProperty("currentPlayingPage", currentPlayingPage);
    rootObject->setProperty("MasterVolume", masterVolume);
    rootObject->setProperty("ToolTipStatus", toolTipStatus);

    //get al the sounds
    std::vector<std::shared_ptr<Sound>> sounds = SoundM->getSounds();
    juce::Array<juce::var> soundsData;

    for (const auto& sound : sounds)
    {
        //get the sound settings and info this will be in soundData
        std::unique_ptr<juce::DynamicObject> soundData = std::make_unique<juce::DynamicObject>();
        soundData->setProperty("name", sound->getSoundName());
        soundData->setProperty("volume", sound->getSoundParam(Sparam::VOLUME));
        soundData->setProperty("pitch", sound->getSoundParam(Sparam::PITCH));
        soundData->setProperty("delay", sound->getSoundParam(Sparam::DELAY));

        juce::Array<juce::var> pagesData;


        for (int page = 0; page < 4; ++page)//alays 4 pages made using the pre processing
        {
            //pageData will hold the info for every page
            std::unique_ptr<juce::DynamicObject> pageData = std::make_unique<juce::DynamicObject>();
            juce::Array<juce::var> stepsData;

            for (int stepIndex = 0; stepIndex < 16; ++stepIndex) //always 16 steps made for every steprow using the pre processing
            {
                Step* step = sound->getStepAt(page, stepIndex);

                if (step != nullptr)
                {
                    //get all the step data and put it in stepData
                    std::unique_ptr<juce::DynamicObject> stepData = std::make_unique<juce::DynamicObject>();
                    stepData->setProperty("isActive", step->getStatus());
                    stepData->setProperty("reverbLocked", step->getLockState(Gparam::REVERB));
                    stepData->setProperty("organicLocked", step->getLockState(Gparam::ORGANIC));
                    stepData->setProperty("volume", step->getVolume());
                    stepData->setProperty("delay", step->getDelay());
                    stepData->setProperty("pitch", step->getPitch());
                    stepData->setProperty("manipulated", step->getManipulated());

                    juce::var stepVar(stepData.get());
                    stepsData.add(stepVar);

                    stepData.release();
                    delete stepData.get();
                }
            }

            pageData->setProperty("steps", stepsData);
            juce::var pageVar(pageData.get());
            pagesData.add(pageVar);

            pageData.release();
            delete pageData.get();
        }

        soundData->setProperty("pages", pagesData);
        juce::var soundVar(soundData.get());
        soundsData.add(soundVar);

        soundData.release();
        delete soundData.get();
    }

    rootObject->setProperty("sounds", soundsData);

    juce::var jsonData(rootObject.get());

    // Combine the directory path with the filename
    juce::File outputFile = projectDir.getChildFile(projectFileName + ".json");

    
    //delete the existing file to make a new one with the same name
    if (outputFile.existsAsFile())
    {
        outputFile.deleteFile();
    }

    juce::FileOutputStream outputStream(outputFile);

    if (outputStream.openedOk())
    {
        juce::JSON::writeToStream(outputStream, juce::var(jsonData), true);
        outputStream.flush();
    }
    else
    {
        // Handle file opening error
        std::cerr << "Error opening file location" << std::endl;
    }

    // Release and delete the rootObject
    rootObject.release();
    delete rootObject.get();
}

/**
 * Creates a new project by loading a template file.
 *
 * Resets the project name to the default value and loads the template file from the "Template" directory.
 *
 * @pre The "Template" directory exists and contains a file named "template.json".
 * @post The project is loaded from the template file, and the project name is reset to the default value.
 * @exception Displays an error message if the template file does not exist.
 * @return None.
 */
void IOManager::newProject()
{
    //we reset the name to default
    *projectName = "";

    juce::File templateDir;
#if defined(JUCE_MAC)
    juce::File currentDir = juce::File::getSpecialLocation(juce::File::currentExecutableFile).getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory().getParentDirectory();

    templateDir = currentDir.getChildFile("Template");
#else
    juce::File currentDir = juce::File::getCurrentWorkingDirectory();
    juce::File grandParentDir = currentDir.getParentDirectory().getParentDirectory();
    templateDir = grandParentDir.getChildFile("Template");

#endif

    //we define the template filewich is an empty project
    juce::File templateFile = templateDir.getChildFile("template.json");

    if (!templateFile.existsAsFile())
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon, "Error", "The template file does not exist.");
        return;
    }

    //we load the empty project
    loadProject(templateFile);
}

/**
 * Loads a project from the specified file.
 *
 * Parses the project file and sets various parameters for the project, including global settings, reverb settings, filter settings,
 * general information, and sound data.
 *
 * @param projectFile The file containing the project data to be loaded.
 * @pre The project file exists and is a valid JSON file.
 * @post The project settings and data are loaded from the file. Displays an error message if the file does not exist, cannot be opened, or cannot be parsed.
 * @exception Displays an error message if the project file does not exist, cannot be opened, or cannot be parsed.
 * @return None.
 */
void IOManager::loadProject(const juce::File& projectFile)
{
    if (!projectFile.existsAsFile())
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon, "Error", "The selected project file does not exist.");
        return;
    }

    juce::FileInputStream inputStream(projectFile);

    if (!inputStream.openedOk())
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon, "Error", "Failed to open the project file.");
        return;
    }

    juce::var jsonData = juce::JSON::parse(inputStream);

    if (jsonData.isVoid())
    {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::WarningIcon, "Error", "Failed to parse the project file.");
        return;
    }

    //to know if its an empty template that we are loading
    if (projectFile.getFileNameWithoutExtension() == "template") {
        isTemplate = true;
    }
    else {
        isTemplate = false;
        //set the project name
        setProjectName(projectFile.getFileNameWithoutExtension());
    }


    //get the global settings
    juce::var globalSettingsVar = jsonData.getProperty("GlobalSettings", juce::var());
    if (globalSettingsVar.isObject())
    {
        juce::DynamicObject* globalSettings = globalSettingsVar.getDynamicObject();
        float bpm = globalSettings->getProperty("BPM");
        float swing = globalSettings->getProperty("Swing");

        //set the global settings
        SoundM->setGParam(bpm, Gparam::BPM);
        SoundM->setGParam(swing, Gparam::SWING);
    }

    //get the reverb settings
    juce::var reverbSettingsVar = jsonData.getProperty("ReverbSettings", juce::var());
    if (reverbSettingsVar.isObject())
    {
        juce::DynamicObject* reverbSettings = reverbSettingsVar.getDynamicObject();
        float roomSize = reverbSettings->getProperty("RoomSize");
        float damping = reverbSettings->getProperty("Damping");
        float width = reverbSettings->getProperty("Width");
        float dry = reverbSettings->getProperty("Dry");
        float wet = reverbSettings->getProperty("Wet");
        bool isReverbed = reverbSettings->getProperty("IsReverbed");

        //set the reverb setings
        ReverbM->setRParam(RParam::ROOMSIZE, roomSize);
        ReverbM->setRParam(RParam::DAMPING, damping);
        ReverbM->setRParam(RParam::WIDTH, width);
        ReverbM->setRParam(RParam::DRY, dry);
        ReverbM->setRParam(RParam::WET, wet);
        SoundM->setReverbStatus(isReverbed);
    }

    //get the filter settings
    juce::var filterSettingsVar = jsonData.getProperty("FilterSettings", juce::var());
    if (filterSettingsVar.isObject())
    {
        juce::DynamicObject* filterSettings = filterSettingsVar.getDynamicObject();
        float lowFrequency = filterSettings->getProperty("LowFrequency");
        float highFrequency = filterSettings->getProperty("HighFrequency");
        float lowQ = filterSettings->getProperty("LowQ");
        float highQ = filterSettings->getProperty("HighQ");
        bool lowPassActive = filterSettings->getProperty("LowPassActive");
        bool highPassActive = filterSettings->getProperty("HighPassActive");

        //set the filter settings
        FilterM->setFParam(FParam::LOWFREQUENCY, lowFrequency);
        FilterM->setFParam(FParam::HIGHFREQUENCY, highFrequency);
        FilterM->setFParam(FParam::LOWQ, lowQ);
        FilterM->setFParam(FParam::HIGHQ, highQ);
        FilterM->setFilterStatus(Gparam::LOWPASS, lowPassActive);
        FilterM->setFilterStatus(Gparam::HIGHPASS, highPassActive);
    }

    //get the general information
    int steps = jsonData.getProperty("steps", 0);
    int pages = jsonData.getProperty("pages", 0);
    int rows = jsonData.getProperty("rows", 0);
    /*int currentPage = jsonData.getProperty("currentPage", 0);
    int currentColumn = jsonData.getProperty("currentColumn", 0);
    int currentPlayingPage = jsonData.getProperty("currentPlayingPage", 0);
    float masterVolume = jsonData.getProperty("MasterVolume", 0.0f);
    bool toolTipStatus = jsonData.getProperty("ToolTipStatus", false);*/

    //set the general information
    //adjust the amount of steps if needed
    if (steps > SoundM->getSteps()) {
        int increments = steps - SoundM->getSteps();
        for (int i = 0; i < increments; i++) {
            SoundM->incrementSteps();
        }
    }
    else if (steps < SoundM->getSteps()) {
        int decrements = SoundM->getSteps() - steps;
        for (int i = 0; i < decrements; i++) {
            SoundM->decrementSteps();
        }
    }
    //adjust the amount of pages if needed
    if (pages > SoundM->getPages()) {
        int increments = pages - SoundM->getPages();
        for (int i = 0; i < increments; i++) {
            SoundM->addPage();
        }
    }
    else if (pages < SoundM->getPages()) {
        int decrements = SoundM->getPages() - pages;
        for (int i = 0; i < decrements; i++) {
            SoundM->deletePage();
        }
    }
    //adjust the amount of rows if needed
    if (rows > SoundM->getRows()) {
        int increments = rows - SoundM->getRows();
        for (int i = 0; i < increments; i++) {
            SoundM->incrementRows();
        }
    }
    else if (rows < SoundM->getRows()) {
        int decrements = SoundM->getRows() - rows;
        for (int i = 0; i < decrements; i++) {
            SoundM->decrementRows();
        }
    }

    //get all the sounds
    if (jsonData.hasProperty("sounds"))
    {
        juce::var soundsData = jsonData.getProperty("sounds", juce::var());
        int soundIndex = 0; //we always have 20 sounds
        juce::Array<juce::var>* soundsArray = soundsData.getArray();

        for (int i = 0; i < soundsArray->size(); i++)
        {
            if (soundsArray->getUnchecked(i).isObject())
            {
                juce::DynamicObject* soundData = soundsArray->getUnchecked(i).getDynamicObject();
                //juce::DynamicObject* soundData = soundVar.getDynamicObject();
                juce::String soundName = soundData->getProperty("name");
                float volume = soundData->getProperty("volume");
                float pitch = soundData->getProperty("pitch");
                float delay = soundData->getProperty("delay");

                //set the sound parameters for every sound
                Sound* sound = SoundM->getSoundAt(soundIndex);
                sound->setSoundName(soundName);
                sound->setSoundParam(0, volume, Sparam::VOLUME);
                sound->setSoundParam(0, pitch, Sparam::PITCH);
                sound->setSoundParam(0, delay, Sparam::DELAY);

                //get all the pages for a sound
                if (soundData->hasProperty("pages"))
                {
                    juce::Array<juce::var> pagesData = *soundData->getProperty("pages").getArray();
                    int pageIndex = 0; //we always have 4 pages
                    for (auto& pageVar : pagesData)
                    {
                        if (pageVar.isObject())
                        {
                            juce::DynamicObject* pageData = pageVar.getDynamicObject();

                            //get al te steps of a sound for a page
                            if (pageData->hasProperty("steps"))
                            {
                                juce::Array<juce::var> stepsData = *pageData->getProperty("steps").getArray();
                                int stepIndex = 0; //we always have 16 steps
                                for (auto& stepVar : stepsData)
                                {
                                    if (stepVar.isObject())
                                    {
                                        juce::DynamicObject* stepData = stepVar.getDynamicObject();
                                        bool isActive = stepData->getProperty("isActive");
                                        bool reverbLocked = stepData->getProperty("reverbLocked");
                                        bool organicLocked = stepData->getProperty("organicLocked");
                                        bool isManipulated = stepData->getProperty("manipulated");
                                        float stepVolume = stepData->getProperty("volume");
                                        float stepDelay = stepData->getProperty("delay");
                                        float stepPitch = stepData->getProperty("pitch");

                                        //set the step settings
                                        Step* step = sound->getStepAt(pageIndex, stepIndex);
                                        step->setVolume(stepVolume);
                                        step->setDelay(stepDelay);
                                        step->setPitch(stepPitch);
                                        step->setStatus(isActive);
                                        step->setLock(Gparam::REVERB, reverbLocked);
                                        step->setLock(Gparam::ORGANIC, organicLocked);
                                        step->setManipulationstat(isManipulated);

                                        ++stepIndex;
                                    }
                                }
                                ++pageIndex;
                            }
                        }
                    }
                }
            }
            ++soundIndex;
        }
    }

    if (!isTemplate) {
        juce::AlertWindow::showMessageBox(juce::AlertWindow::InfoIcon, "Success", "Project loaded successfully.");
    }
}


/**
 * Sets the project name.
 *
 * Updates the project name with the specified name.
 *
 * @param name The new name for the project.
 * @pre The project name should be a valid string.
 * @post The project name is updated with the new name.
 * @return None.
 */
void IOManager::setProjectName(const juce::String& name)
{
    *projectName = name;
}
