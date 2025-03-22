#include "diceview.h"
#include "qfont.h"


DiceView::DiceView()
{
    setBrush(Qt::white);
    setRect(0,0, 70, 70);

    m_TextNumber = new QGraphicsSimpleTextItem{this};
    m_TextNumber->setFont(QFont{"Arial", 20, QFont::Bold});

    const int BeginNumber = 2;
    setNumber(BeginNumber);
}

void DiceView::setNumber(const int n)
{
    m_TextNumber->setText(QString::number(n));
    m_TextNumber->setPos(boundingRect().center() - m_TextNumber->boundingRect().center());
}

