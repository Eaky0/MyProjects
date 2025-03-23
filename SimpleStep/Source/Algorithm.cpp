#include "Algorithm.h"
/*
  ==============================================================================

    Algorithm.cpps
    Author:  Faruk Kazankaya, Atakan Kumas, Eren Karabalut

  ==============================================================================
*/

/**
* getRandomNumber
* Generates a random integer between min and max, inclusive.
*
* @param min The minimum integer value for the random number.
* @param max The maximum integer value for the random number.
* @pre min and max are valid integers with min <= max.
* @post Returns a random integer between min and max.
* @return The generated random integer.
*/
int Algorithm::getRandomNumber(int min, int max)
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator(seed);
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}
