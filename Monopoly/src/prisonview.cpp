#include "prisonview.h"

PrisonView::PrisonView(QGraphicsScene* Scene)
{
    m_PayBailButton = new QPushButton(QPushButton::tr("&Pay Bail"));
    m_JailCardButton = new QPushButton(QPushButton::tr("&Use Jail Card"));

    m_PayBailButtonProxy = Scene->addWidget(m_PayBailButton);
    m_JailCardButtonProxy = Scene->addWidget(m_JailCardButton);

    m_PayBailButtonProxy->setScale(2);
    m_JailCardButtonProxy->setScale(2);

    m_PayBailButtonProxy->setPos(1105, 105);
    m_JailCardButtonProxy->setPos(1105, 155);
    hidePrisonView();
}

void PrisonView::hidePrisonView()
{
    m_PayBailButtonProxy->hide();
    m_JailCardButtonProxy->hide();
}

void PrisonView::showPrisonView(const bool HasJailCard)
{
    m_PayBailButtonProxy->show();

    if (HasJailCard)
        m_JailCardButtonProxy->show();
}

QPushButton *PrisonView::getBailButtton()
{
    return m_PayBailButton;
}

QPushButton *PrisonView::getJailCardButton()
{
    return m_JailCardButton;
}

