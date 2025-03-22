//Author: Kumas Atakan
#ifndef ADVANCEMENT_H
#define ADVANCEMENT_H

#include <card.h>

class Advancement : public Card
{
public:
    //Constructor:
    Advancement(QJsonValue CardInfo, CardType CardSort, int CardNumber);

    void DynamicFunc(){}; //Empty function Used for making class Card polymorphic and effective for dynamic casting;

    //Method:
    //Returns a name (QString) where the card says to advance to
    QString getAdvancement();
private:
    //Members:
    QString m_AdvanceTo;
};

#endif // ADVANCEMENT_H
