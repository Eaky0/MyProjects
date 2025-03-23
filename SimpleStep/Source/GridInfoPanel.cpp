/*
  ==============================================================================

    GridInfoPanel.cpp
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#include "GridInfoPanel.h"

/**
* GridInfoPanel Constructor
* Initializes the GridInfoPanel with default size and sets up step number labels.
*
* @param None.
* @pre None.
* @post GridInfoPanel is initialized with default size and step number labels.
* @return None.
*/
GridInfoPanel::GridInfoPanel()
{
    setSize(450, 25);

    for (int page = 0; page < 4; ++page) {

        juce::Array<std::shared_ptr<juce::Label>> initialInfo;

        for (int i = 0; i < 16; ++i) {
            std::shared_ptr<juce::Label> StepNumber = std::make_shared<juce::Label>();
            StepNumber->setFont(15.0f);
            StepNumber->setText(juce::String((page * 16) + (i + 1)), juce::dontSendNotification);
            StepNumber->setColour(juce::Label::textColourId, juce::Colours::white);
            initialInfo.add(StepNumber);
            addAndMakeVisible(StepNumber.get());
        }

        StepNumbers.add(initialInfo);
    }

    SoundText.setFont(20.0f);
    SoundText.setText("Sounds", juce::dontSendNotification);
    SoundText.setColour(juce::Label::textColourId, juce::Colours::white);

    addAndMakeVisible(SoundText);
}

/**
* GridInfoPanel Destructor
* Cleans up any resources associated with the GridInfoPanel.
*
* @param None.
* @pre None.
* @post GridInfoPanel is destructed, releasing associated resources.
* @return None.
*/
GridInfoPanel::~GridInfoPanel()
{
    for (int page = 0; page < StepNumbers.size(); ++page) {
        for (int step = 0; step < StepNumbers[page].size(); ++step) {
            StepNumbers[page][step].reset();
        }
    };

    SoundM.reset();
}

/**
* setModels
* Sets the model for the GridInfoPanel.
*
* @param sound Pointer to the SoundManager object.
* @pre None.
* @post Model for the GridInfoPanel is set.
* @return None.
*/
void GridInfoPanel::setModels(SoundManager* sound)
{
    SoundM.reset(sound);
    SoundM->addObserver(this);

}

/**
* paint
* Paints the GridInfoPanel.
*
* @param g Reference to the Graphics object for drawing.
* @pre None.
* @post GridInfoPanel is painted with appropriate colors and borders.
* @return None.
*/
void GridInfoPanel::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colour(129, 164, 205));
    g.setColour(juce::Colour(219, 228, 238));
}

/**
* resized
* Resizes the GridInfoPanel.
*
* @param None.
* @pre None.
* @post GridInfoPanel is resized to fit the available space.
* @return None.
*/
void GridInfoPanel::resized()
{
    juce::FlexBox InfoRow;
    InfoRow.flexDirection = juce::FlexBox::Direction::row;
    InfoRow.flexWrap = juce::FlexBox::Wrap::wrap;

    InfoRow.items.add(juce::FlexItem(SoundText).withMinWidth(95.0f).withMinHeight(25.0f));

    float area;
    if (SoundM != nullptr) {
        area = (getWidth() - 100.0f) / SoundM->getSteps();

        for (std::shared_ptr<juce::Label> StepNumber : StepNumbers[SoundM->getCurrentPage() - 1]) {
            InfoRow.items.add(juce::FlexItem(*StepNumber).withMinWidth(area).withMinHeight(25.0f));
        }
    }
    else {
        area = (getWidth() - 100.0f) / 16;

        for (std::shared_ptr<juce::Label> StepNumber : StepNumbers[0]) {
            InfoRow.items.add(juce::FlexItem(*StepNumber).withMinWidth(area).withMinHeight(25.0f));
        }
    }

    InfoRow.performLayout(getLocalBounds());
}

/**
* update
* Updates the GridInfoPanel based on the provided identifier.
*
* @param id Integer identifier indicating the type of update.
* @pre None.
* @post GridInfoPanel is updated based on the provided identifier.
* @return None.
*/
void GridInfoPanel::update(int id)
{
    switch (id) {
    case 1:
    case 2:
    case 11:
    case 12:
        ReorganizeStepNumbers();
        break;
    case 4:
        ColourizeCurrentStep();
        break;
    case 5:
        UnColourizeCurrentStep();
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
    ReorganizeStepNumbers();
    resized();
}

/**
* nextPage
* Shows the next page of step numbers.
*
* @param None.
* @pre None.
* @post Next page of step numbers is displayed.
* @return None.
*/
void GridInfoPanel::nextPage() {

    int NewPage = SoundM->getCurrentPage() - 1;
    int PrevPage = NewPage - 1;

    for (int i = 0; i < SoundM->getSteps(); i++) {
        StepNumbers[PrevPage][i].get()->setVisible(false);
    }

    for (int i = 0; i < SoundM->getSteps(); i++) {
        StepNumbers[NewPage][i]->setVisible(true);
    }
}

/**
* prevPage
* Shows the previous page of step numbers.
*
* @param None.
* @pre None.
* @post Previous page of step numbers is displayed.
* @return None.
*/
void GridInfoPanel::prevPage() {

    int NewPage = SoundM->getCurrentPage() - 1;
    int PrevPage = NewPage + 1;

    for (int i = 0; i < SoundM->getSteps(); i++) {
        StepNumbers[PrevPage][i].get()->setVisible(false);
    }

    for (int i = 0; i < SoundM->getSteps(); i++) {
        StepNumbers[NewPage][i]->setVisible(true);
    }
}

/**
* ColourizeCurrentStep
* Highlights the currently playing step.
*
* @param None.
* @pre None.
* @post Current playing step is highlighted.
* @return None.
*/
void GridInfoPanel::ColourizeCurrentStep() {

    int CurrentColumn = SoundM->getCurrentPlayingColumn();
    int CurrentPlayingPage = SoundM->getCurrentPlayingPage();

    UnColourizeCurrentStep();
    StepNumbers[CurrentPlayingPage][CurrentColumn]->setColour(juce::Label::backgroundColourId, juce::Colour(3, 4, 94));
}


/**
* UnColourizeCurrentStep
* Removes highlight from the currently playing step.
*
* @param None.
* @pre None.
* @post Highlight from the currently playing step is
* removed.
*
* @return None.
*/
void GridInfoPanel::UnColourizeCurrentStep() {


    for (int page = 0; page < SoundM->getPages(); ++page) {
        for (int step = 0; step < SoundM->getSteps(); ++step) {
            StepNumbers[page][step]->setColour(juce::Label::backgroundColourId, juce::Colour(129, 164, 205));
        }
    }


}

/**
* ReorganizeStepNumbers
* Updates and reorganizes the step numbers based on the current page.
*
* @param None.
* @pre None.
* @post Step numbers are updated and reorganized based on the current page.
* @return None.
*/
void GridInfoPanel::ReorganizeStepNumbers() {

    for (int page = 0; page < SoundM->getPages(); ++page) {
        for (int step = 0; step < SoundM->getSteps(); ++step) {
            StepNumbers[page][step]->setText(juce::String((page * SoundM->getSteps()) + step + 1), juce::dontSendNotification);
            if (page == SoundM->getCurrentPage() - 1) {
                StepNumbers[page][step]->setVisible(true);
            }
            else {
                StepNumbers[page][step]->setVisible(false);
            }
        }
    }

}