#include "playerview.h"

PlayerView::PlayerView(const int PlayerNumber, Player* Player) : m_Player{Player}
{
    setBrush(Qt::cyan);
    setRect(0,0, 150, 50);

    m_PlayerNumberText = new QGraphicsSimpleTextItem{this};
    m_BalanceText = new QGraphicsSimpleTextItem{this};

    QString Number = "Player: " + QString::number(PlayerNumber + 1);
    m_PlayerNumberText->setText(Number);
    m_PlayerNumberText->setScale(2);

    updateBalance();
    m_BalanceText->setScale(2);
    m_BalanceText->setPos(0,22);
}

void PlayerView::updateBalance() const
{
    int BalanceOfPlayer = m_Player->getBalance();
    QString PlayerBalance = "Balance: " + QString::number(BalanceOfPlayer);
    m_BalanceText->setText(PlayerBalance);
}

Figure PlayerView::getFigure()
{
    return m_Player->getFigure();
}

