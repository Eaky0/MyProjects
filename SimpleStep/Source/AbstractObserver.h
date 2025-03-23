/*
  ==============================================================================

    AbstractObserver.h
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AbstractObserver
{
public:
    ~AbstractObserver() = default;

    /**
    * update
    * Updates the observer with an integer ID.
    *
    * @param id The ID of the event to update the observer with.
    * @pre id is a valid integer.
    * @post The observer is updated with the given id.
    */
    virtual void update(int id) = 0;

    /**
    * update
    * Updates the observer with a file.
    *
    * @param file The file to update the observer with.
    * @pre file is a valid juce::File object.
    * @post The observer is updated with the given file.
    */
    virtual void update(juce::File file) = 0;

    /**
    * update
    * Updates the observer with a vector of floats.
    *
    * @param data The vector of floats to update the observer with.
    * @pre data is a valid vector of floats.
    * @post The observer is updated with the given data.
    */
    virtual void update(std::vector<float> data) = 0;
};
