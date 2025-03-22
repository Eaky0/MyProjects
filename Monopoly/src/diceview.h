//Author : Ieracitano Alessio
#ifndef DICEVIEW_H
#define DICEVIEW_H

#include <QGraphicsItem>
#include <qfont.h>
#include <QBrush>

class DiceView : public QGraphicsRectItem
{
public:
    //constructor
    DiceView();

    //Method:
    //Sets the number that needs to be displayed on the dice
    void setNumber(const int n);
private:
    QGraphicsSimpleTextItem *m_TextNumber;
};

#endif // DICEVIEW_H
