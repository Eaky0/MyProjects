/*
  ==============================================================================

    StepPatternPanel.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "StepPatternPanel.h"

/**
 * StepPatternPanel
 *
 * Constructs a StepPatternPanel with the specified sound name, pattern ID, and sound library view.
 * Initializes the sound button and step views.
 *
 * @param SoundName The name of the sound.
 * @param id The pattern ID.
 * @param SL Pointer to the SoundLibraryView.
 * @pre None
 * @post The StepPatternPanel is initialized with the given sound name, ID, and sound library view.
 */
StepPatternPanel::StepPatternPanel(juce::String SoundName, int id, SoundLibraryView* SL) : SoundButton((SoundName == "Empty") ? "+" : SoundName)
{
    addAndMakeVisible(SoundButton);
    SoundLib.reset(SL);
    SoundButton.setLibrary(SL);

    for (int page = 0; page < 4; ++page) {
        juce::Array<std::shared_ptr<StepView>> InitialSteps;

        for (int i = 0; i < 16; i++) {
            std::shared_ptr<StepView> Step;
            if (SoundName == "Empty") {
                Step = std::make_shared<StepView>("Empty : " + juce::String(i + 1));
            }
            else {
                Step = std::make_shared<StepView>(SoundName + " : " + juce::String(i + 1));
            }
            InitialSteps.add(Step);
            if (page == 0) {
                addAndMakeVisible(Step.get());
            }
            else {
                Step->setVisible(false);
                addChildComponent(Step.get());
            }
        }

        Steps.add(InitialSteps);
    }

    PatternID = id;
    setSize(250, 50);
}

/**
 * StepPatternPanel
 *
 * Constructs a StepPatternPanel with the specified sound name, pattern ID, sound library view, step amount, and page amount.
 * Initializes the sound button and step views.
 *
 * @param SoundName The name of the sound.
 * @param id The pattern ID.
 * @param SL Pointer to the SoundLibraryView.
 * @param StepAmount The number of steps per page.
 * @param PageAmount The number of pages.
 * @pre None
 * @post The StepPatternPanel is initialized with the given parameters.
 */
StepPatternPanel::StepPatternPanel(juce::String SoundName, int id, SoundLibraryView* SL, int StepAmount, int PageAmount) : SoundButton((SoundName == "Empty") ? "+" : SoundName)
{
    addAndMakeVisible(SoundButton);
    SoundLib.reset(SL);
    SoundButton.setLibrary(SL);

    for (int page = 0; page < PageAmount; ++page) {
        juce::Array<std::shared_ptr<StepView>> InitialSteps;
        for (int i = 0; i < StepAmount; ++i) {
            std::shared_ptr<StepView> Step;
            if (SoundName == "Empty") {
                Step = std::make_shared<StepView>("Empty : " + juce::String(i + 1));
            }
            else {
                Step = std::make_shared<StepView>(SoundName + " : " + juce::String(i + 1));
            }
            InitialSteps.add(Step);
        }
        Steps.add(InitialSteps);
    }

    PatternID = id;
    setSize(250, 50);
}

/**
 * ~StepPatternPanel
 *
 * Destructor for the StepPatternPanel.
 * Cleans up allocated resources and resets the model pointers.
 *
 * @pre None
 * @post The resources used by the StepPatternPanel are cleaned up.
 */
StepPatternPanel::~StepPatternPanel()
{
    for (int page = 0; page < SoundM->getPages(); ++page) {
        for (int i = 0; i < SoundM->getSteps(); i++) {
            delete Steps[page][i].get();
        }
        Steps[page].clear();
    }

    SoundM.reset();
    SoundLib.reset();
}

/**
 * paint
 *
 * Paints the StepPatternPanel background.
 *
 * @param g Reference to the Graphics context used for drawing.
 * @pre None
 * @post The background of the StepPatternPanel is painted.
 */
void StepPatternPanel::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);
}

/**
 * resized
 *
 * Resizes the components within the StepPatternPanel.
 * Arranges the sound button and step views using a FlexBox layout.
 *
 * @pre None
 * @post The components within the StepPatternPanel are resized and arranged.
 */
void StepPatternPanel::resized()
{
    juce::FlexBox StepRow;
    StepRow.flexDirection = juce::FlexBox::Direction::row;
    StepRow.flexWrap = juce::FlexBox::Wrap::wrap;

    // Add sound view to the flex box
    StepRow.items.add(juce::FlexItem(SoundButton).withMinWidth(95.0f).withMinHeight(50.0f));

    // Calculate area for each step view
    float area;
    if (SoundM != nullptr) {
        area = (getWidth() - 100.0f) / SoundM->getSteps();

        for (int i = 0; i < Steps[SoundM->getCurrentPage() - 1].size(); i++) {
            StepRow.items.add(juce::FlexItem(*Steps[SoundM->getCurrentPage() - 1][i]).withMinWidth(area).withMinHeight(50.0f));
        }

    }
    else {
        area = (getWidth() - 100.0f) / 16;

        for (int i = 0; i < Steps[0].size(); i++) {
            StepRow.items.add(juce::FlexItem(*Steps[0][i]).withMinWidth(area).withMinHeight(50.0f));
        }

    }

    StepRow.performLayout(getLocalBounds());
}

/**
 * setModels
 *
 * Sets the models for the StepPatternPanel, initializing the steps and sound button.
 *
 * @param sound Pointer to the SoundManager instance.
 * @pre None
 * @post The StepPatternPanel models are set, and steps are initialized.
 */
void StepPatternPanel::setModels(SoundManager* sound)
{
    SoundM.reset(sound);
    Sound* s = SoundM.get()->getSoundAt(PatternID);
    SoundButton.setModels(s);

    for (int page = 0; page < 4; ++page) {
        for (int i = 0; i < 16; i++) {
            StepView* Step = Steps[page][i].get();
            Step->setModels(s->getStepAt(page, i));
        }
    }

    SoundM->addObserver(this);
    s->addObserver(this);

    RefreshStepVisibility();
}

/**
 * update
 *
 * Updates the StepPatternPanel based on the provided observer ID.
 *
 * @param id The ID of the observer event.
 * @pre None
 * @post The StepPatternPanel is updated and resized if the ID corresponds to an event requiring such actions.
 */
void StepPatternPanel::update(int id)
{
    switch (id) {
    case 1:
    case 2:
    case 11:
    case 12:
        RefreshStepVisibility();
        break;
    case 3:
        SoundButton.setSoundName();
        setSoundMessage();
        break;
    case 13:
        nextPage();
        break;
    case 14:
        prevPage();
        break;
    default:
        break;
    }
    resized();
}

/**
 * nextPage
 *
 * Advances to the next page of steps, updating visibility.
 *
 * @pre None
 * @post The visibility of steps for the new page is updated.
 */
void StepPatternPanel::nextPage()
{
    int NewPage = SoundM->getCurrentPage() - 1;
    int PrevPage = NewPage - 1;

    for (int i = 0; i < SoundM->getSteps(); i++) {
        Steps[PrevPage][i].get()->setVisible(false);
    }

    for (int i = 0; i < SoundM->getSteps(); i++) {
        Steps[NewPage][i].get()->setVisible(true);
    }
}

/**
 * prevPage
 *
 * Moves to the previous page of steps, updating visibility.
 *
 * @pre None
 * @post The visibility of steps for the new page is updated.
 */
void StepPatternPanel::prevPage()
{
    int NewPage = SoundM->getCurrentPage() - 1;
    int PrevPage = NewPage + 1;

    for (int i = 0; i < SoundM->getSteps(); i++) {
        Steps[PrevPage][i].get()->setVisible(false);
    }

    for (int i = 0; i < SoundM->getSteps(); i++) {
        Steps[NewPage][i].get()->setVisible(true);
    }
}

/**
 * setSoundMessage
 *
 * Sets the sound message for each step based on the sound name.
 *
 * @pre None
 * @post The sound name is updated for each step in the pattern.
 */
void StepPatternPanel::setSoundMessage()
{
    Sound* s = SoundM.get()->getSoundAt(PatternID);
    juce::String sName = s->getSoundName();

    for (int page = 0; page < SoundM->getPages(); ++page) {
        for (int i = 0; i < SoundM.get()->getSteps(); ++i) {
            StepView* Step = Steps[page][i].get();
            Step->setSoundName(sName);
        }
    }
}

/**
 * RefreshStepVisibility
 *
 * Refreshes the visibility of steps based on the current page.
 *
 * @pre None
 * @post The visibility of steps is updated based on the current page.
 */
void StepPatternPanel::RefreshStepVisibility()
{
    for (int page = 0; page < SoundM->getPages(); ++page) {
        for (int step = 0; step < SoundM->getSteps(); ++step) {
            if (page == SoundM->getCurrentPage() - 1) {
                Steps[page][step]->setVisible(true);
            }
            else {
                Steps[page][step]->setVisible(false);
            }
        }
    }
}
