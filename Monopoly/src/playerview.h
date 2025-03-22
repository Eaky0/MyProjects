//Author: Ieracitano Alessio
#ifndef PLAYERVIEW_H
#define PLAYERVIEW_H

#include "player.h"

#include <QGraphicsRectItem>
#include <QBrush>

class PlayerView : public QGraphicsRectItem
{
public:
    //Constructor
    PlayerView(const int PlayerNumber, Player* Player);

    //Method:
    //Sets the balance text to the player his current balance
    void updateBalance() const;

    //Method:
    //Returns the figure of the corresponding player
    Figure getFigure();
private:
    Player* m_Player;
    QGraphicsSimpleTextItem *m_PlayerNumberText;
    QGraphicsSimpleTextItem *m_BalanceText;
};

#endif // PLAYERVIEW_H
