/*
  ==============================================================================

    Utilities.h

    This class contains basic utilities for the GUI.
    
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/


#include <JuceHeader.h>

#pragma once

/*
  ==============================================================================

    LockButton
    A custom button for locking and unlocking with icons.
*/
class LockButton : public juce::TextButton
{
public:
    /**
    * Constructor
    * Creates a LockButton with specified text and icons.
    *
    * @param text The text to display on the button.
    * @param LockIcon The icon to display when the button is locked.
    * @param UnlockIcon The icon to display when the button is unlocked.
    * @pre None.
    * @post None.
    * @return None.
    */
    LockButton(const juce::String& text, const juce::Image& LockIcon, const juce::Image& UnlockIcon)
        : TextButton(text), LockImage(LockIcon), unLockImage(UnlockIcon), currentImage(UnlockIcon)
    {}

    /**
    * setState
    * Sets the state of the button (locked or unlocked).
    *
    * @param isLocked True if the button should be locked, false otherwise.
    * @pre None.
    * @post The button's state is updated and repainted.
    * @return None.
    */
    void setState(bool isLocked)
    {
        locked = isLocked;
        currentImage = locked ? LockImage : unLockImage;
        repaint();
    }

    /**
    * getState
    * Gets the current state of the button.
    *
    * @pre None.
    * @post None.
    * @return True if the button is locked, false otherwise.
    */
    bool getState() {
        return locked;
    }

    /**
    * paintButton
    * Paints the button, including the icon.
    *
    * @param g The Graphics context to draw in.
    * @param shouldDrawButtonAsHighlighted Whether the button should be highlighted.
    * @param shouldDrawButtonAsDown Whether the button should be drawn as if it's being pressed.
    * @pre None.
    * @post The button is painted with the appropriate icon.
    * @return None.
    */
    void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        juce::TextButton::paintButton(g, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

        auto bounds = getLocalBounds();
        auto imageArea = bounds.removeFromRight(bounds.getHeight()).reduced(5);

        g.drawImageWithin(currentImage, imageArea.getX(), imageArea.getY(), imageArea.getWidth(), imageArea.getHeight(),
            juce::RectanglePlacement::centred, false);
    }

private:
    juce::Image LockImage;      // Icon for locked state
    juce::Image unLockImage;    // Icon for unlocked state
    juce::Image currentImage;   // Current icon
    bool locked = false;        // Current lock state
};



/*
  ==============================================================================

    IconButton
    A custom button for toggling between play and stop with icons.
*/
class IconButton : public juce::TextButton
{
public:
    /**
    * Constructor
    * Creates an IconButton with specified text and icons.
    *
    * @param text The text to display on the button.
    * @param playIcon The icon to display when the button is in play state.
    * @param stopIcon The icon to display when the button is in stop state.
    * @pre None.
    * @post None.
    * @return None.
    */
    IconButton(const juce::String& text, const juce::Image& playIcon, const juce::Image& stopIcon)
        : TextButton(text), playImage(playIcon), stopImage(stopIcon), currentImage(playIcon)
    {}

    /**
    * setState
    * Sets the state of the button (play or stop).
    *
    * @param isPlaying True if the button should display the stop icon (playing), false otherwise.
    * @pre None.
    * @post The button's state is updated and repainted.
    * @return None.
    */
    void setState(bool isPlaying)
    {
        currentImage = isPlaying ? stopImage : playImage;
        repaint();
    }

    /**
    * paintButton
    * Paints the button, including the icon.
    *
    * @param g The Graphics context to draw in.
    * @param shouldDrawButtonAsHighlighted Whether the button should be highlighted.
    * @param shouldDrawButtonAsDown Whether the button should be drawn as if it's being pressed.
    * @pre None.
    * @post The button is painted with the appropriate icon.
    * @return None.
    */
    void paintButton(juce::Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        juce::TextButton::paintButton(g, shouldDrawButtonAsHighlighted, shouldDrawButtonAsDown);

        auto bounds = getLocalBounds();
        auto imageArea = bounds.removeFromRight(bounds.getHeight()).reduced(5);

        g.drawImageWithin(currentImage, imageArea.getX(), imageArea.getY(), imageArea.getWidth(), imageArea.getHeight(),
            juce::RectanglePlacement::centred, false);
    }

private:
    juce::Image playImage;      // Icon for play state
    juce::Image stopImage;      // Icon for stop state
    juce::Image currentImage;   // Current icon
};



/*
  ==============================================================================

    PopUpMenuLookAndFeel
    A custom look and feel made for Popup Menu's throughout the application
*/
class PopUpMenuLookAndFeel : public juce::LookAndFeel_V4
{
public:
    /**
    * PopUpMenuLookAndFeel
    * Constructor for the PopUpMenuLookAndFeel class. Initializes the custom look and feel for popup menus.
    */
    PopUpMenuLookAndFeel() {}

    /**
    * drawPopupMenuBackground
    * Draws the background of the popup menu with a specified color and border.
    *
    * @param g The graphics context used for drawing
    * @param width The width of the popup menu
    * @param height The height of the popup menu
    * @return void
    *
    */
    void drawPopupMenuBackground(juce::Graphics& g, int width, int height) override
    {
        g.fillAll(juce::Colour(3, 4, 94));

        g.setColour(juce::Colour(129, 164, 205));
        g.drawRect(0, 0, width, height);
    }
};
