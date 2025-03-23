/*
  ==============================================================================

    Parameters.h

    This has general parameters for the code

    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

#pragma once


/*
* Parameters:
* These enum classes define parameters which are used generally and specifically for various parameters and subparameters.
*/


//Standard step/sound parameters
enum class Sparam
{
    VOLUME,
    PITCH, 
    DELAY
};

//Global parameters
enum class Gparam {
    BPM,
    SWING,
    REVERB,
    ORGANIC,
    LOWPASS,
    HIGHPASS,
    MASTERVOLUME
};

//Filter parameters
enum class FParam {
    LOWFREQUENCY,
    HIGHFREQUENCY,
    LOWQ,
    HIGHQ
};

//Reverb Parameters
enum class RParam {
    ROOMSIZE,
    DAMPING,
    WIDTH,
    DRY,
    WET
};