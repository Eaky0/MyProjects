//author: Ieracitano Alessio
#ifndef CARDVIEW_H
#define CARDVIEW_H


#include "card.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPainterPath>

class CardView : public QGraphicsRectItem
{
public:
    //Constructor:
    CardView();

    //Method:
    //Sets the text of the card to be displayed
    void setCard(CardType Type, Card CardInfo); //fill the membervariables with the correct info;
private:
    //Method:
    //Returns the type of the card as an QString
    QString getType(CardType Type);         //Return the type as an string
    QGraphicsSimpleTextItem *m_CardType;
    QGraphicsSimpleTextItem *m_CardInfo;
};

#endif // CARDVIEW_H
