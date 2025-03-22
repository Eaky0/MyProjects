//Author: Kumas Atakan
#ifndef CARD_H
#define CARD_H

#include <transactiontype.h>
#include <cardtype.h>

#include <QStringLiteral>
#include <QString>
#include <QList>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>
#include <QIODevice>
#include <QStringLiteral>

class Card
{
public:

    //Constructor
    //PARAM: A JSON value containing all information about cards, the type of card, the number of the cards (used to easily detect the card whenever it is needed)
    Card(QJsonValue CardInfo, CardType CardSort, int CardNumber);

    //Method:
    //Returns the type of the card, this could either be CHANCE or COMMUNITYCHEST.
    CardType TypeOfCard();

    //Method:
    //Returns the chore that is written on the card, in order to be able to display it.
    QString getChore() const;

    //Method:
    //Returns the card number of the card.

    int getCardNumber();

    virtual void DynamicFunc(){};  //Empty function Used for making this class polymorphic and effective for dynamic casting;

private:
    //Members:
    QString m_Chore;
    CardType m_CardSort;
    int m_CardNumber;
};

#endif // CARD_H
