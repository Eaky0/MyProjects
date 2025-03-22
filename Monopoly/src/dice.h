//Author: Ieracitano Alessio
#ifndef DICE_H
#define DICE_H

#include <random>
#include <QPair>
class Dice
{
public:
    Dice();

    //method:
    //Generates two random numbers
    //Returns two random integers, each inbetween the range of 1 and 6
    QPair<int,int> throwDice();

    //Method:
    //Returns two integers
    QPair<int, int> getNumbers();

private:
    QPair<int, int> m_Numbers;
};

#endif // DICE_H
