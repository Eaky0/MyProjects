#include "dice.h"

Dice::Dice()
{
    //Set an random seed
    srand(time(nullptr));
}

QPair<int, int> Dice::throwDice()
{
    int firstNumber = (rand()% 7);
    int secondNumber = (rand()% 7);

    if (firstNumber == 0)
        ++firstNumber;

    if (secondNumber == 0)
        ++secondNumber;

    QPair<int,int> rolledNumbers(firstNumber, secondNumber);
    m_Numbers = rolledNumbers;

    return rolledNumbers;
}

QPair<int, int> Dice::getNumbers()
{
    return m_Numbers;
}

