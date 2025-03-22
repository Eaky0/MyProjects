#include "advancement.h"

Advancement::Advancement(QJsonValue CardInfo, CardType CardSort, int CardNumber) : Card{CardInfo, CardSort, CardNumber}
{
    m_AdvanceTo = CardInfo["advancement"].toString();
}

QString Advancement::getAdvancement()
{
    return m_AdvanceTo;
}
