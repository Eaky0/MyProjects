#include "cardview.h"

CardView::CardView()
{

    setRect(0,0, 600, 300);

    m_CardType = new QGraphicsSimpleTextItem{this};
    m_CardInfo = new QGraphicsSimpleTextItem{this};

    QString Type = "No card set!";
    QString Info = "No card set!";

    m_CardType->setText(Type);
    m_CardType->setScale(2);


    m_CardInfo->setText(Info);
    m_CardInfo->setScale(2);
    m_CardInfo->setPos(10,100);
}

void CardView::setCard(CardType Type, Card CardInfo)
{
    QString CardType = getType(Type);
    QString CardChore = CardInfo.getChore();

    if (Type == CardType::CHANCE){
        m_CardType->setPos(250, 10);
        setBrush(QColor(255, 140, 0));
    }
    else{
        m_CardType->setPos(175, 10);
        setBrush(QColor(212, 175, 55));
    }

    m_CardType->setText(CardType);
    m_CardInfo->setText(CardChore);
}

QString CardView::getType(CardType Type)
{
    if (Type == CardType::CHANCE)
        return "CHANCE";
    else
        return "COMMUNITY CHEST";
}

