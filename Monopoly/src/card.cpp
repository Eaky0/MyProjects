#include "card.h"

Card::Card(QJsonValue CardInfo, CardType CardSort, int CardNumber) : m_CardNumber{CardNumber}, m_CardSort{CardSort},  m_Chore{CardInfo["chore"].toString()}
{}

int Card::getCardNumber()
{
    return m_CardNumber;
}


CardType Card::TypeOfCard()
{
    return m_CardSort;
}

QString Card::getChore() const
{
    return m_Chore;
}


