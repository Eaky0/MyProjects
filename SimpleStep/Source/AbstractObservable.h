/*
  ==============================================================================

    AbstractObservable.h
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "AbstractObserver.h"

class AbstractObservable
{
public:
    ~AbstractObservable() = default;

    /**
    * addObserver
    * Adds an observer to the list.
    *
    * @param observer Pointer to the observer to be added.
    * @pre observer is a valid pointer and not already in the list.
    * @post observer is added to the Observers list.
    */
    void addObserver(AbstractObserver* observer) { Observers.add(observer); };

    /**
    * removeObserver
    * Removes an observer from the list.
    *
    * @param observer Pointer to the observer to be removed.
    * @pre observer is a valid pointer and is in the list.
    * @post observer is removed from the Observers list.
    */
    void removeObserver(AbstractObserver* observer) { Observers.remove(observer); };

    /**
    * notifyObservers
    * Notifies all observers of an event with an integer ID.
    *
    * @param eventID The ID of the event to notify observers about.
    * @pre eventID is a valid integer.
    * @post All observers are notified with the given eventID.
    */
    void notifyObservers(int eventID)
    {
        Observers.call([eventID](AbstractObserver& observer) {
            observer.update(eventID);
            });
    }

    /**
    * notifyObservers
    * Notifies all observers of an event with a file.
    *
    * @param file The file to notify observers about.
    * @pre file is a valid juce::File object.
    * @post All observers are notified with the given file.
    */
    void notifyObservers(juce::File file)
    {
        Observers.call([file](AbstractObserver& observer) {
            observer.update(file);
            });
    }

    /**
    * notifyObservers
    * Notifies all observers of an event with a vector of floats.
    *
    * @param data The vector of floats to notify observers about.
    * @pre data is a valid vector of floats.
    * @post All observers are notified with the given data.
    */
    void notifyObservers(std::vector<float> data)
    {
        Observers.call([data](AbstractObserver& observer) {
            observer.update(data);
            });
    }

private:
    juce::ListenerList<AbstractObserver> Observers;

};
