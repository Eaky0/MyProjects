
#include "bankview.h"

BankView::BankView(QGraphicsScene* Scene)
{
    //members:
    m_PayOffDebtButton = new QPushButton(QPushButton::tr("&Pay Debt"));
    m_PayUtiltyButton = new QPushButton(QPushButton::tr("&Pay Rent"));
    m_PayRentButton = new QPushButton(QPushButton::tr("&Pay Rent"));
    m_PayTaxButton = new QPushButton(QPushButton::tr("&Pay Tax"));
    m_DebtText = Scene->addText(QGraphicsTextItem::tr("Empty"));

    m_PayOffDebtProxy = Scene->addWidget(m_PayOffDebtButton);
    m_PayUtiltyProxy = Scene->addWidget(m_PayUtiltyButton);
    m_PayRentProxy = Scene->addWidget(m_PayRentButton);
    m_PayTaxProxy = Scene->addWidget(m_PayTaxButton);

    setScale();
    setPositions();
}

QPushButton *BankView::getPayOffDebtButton()
{
    return m_PayOffDebtButton;
}

QPushButton *BankView::getPayUtiltyButton()
{
    return m_PayUtiltyButton;
}

QPushButton *BankView::getPayRentButton()
{
    return m_PayRentButton;
}

QPushButton *BankView::getPayTaxButton()
{
    return m_PayTaxButton;
}

void BankView::showPayOffDebt(const int &Amount, const int &PlayerNumber)
{
    m_PayOffDebtProxy->show();
    QString OwedTo;

    //If the Figure is none the player owes the bank
    if (PlayerNumber == 0)
        OwedTo = "Debt Amount: " + QString::number(Amount) + "\nOwed to the Bank";
    else
        OwedTo = "Debt Amount: " + QString::number(Amount) + "\nOwed to player: " + QString::number(PlayerNumber);

    m_DebtText->setPlainText(OwedTo);
    m_DebtText->show();
}

void BankView::showPayUtilty()
{
    m_PayUtiltyProxy->show();
}

void BankView::showPayRent()
{
    m_PayRentProxy->show();
}

void BankView::showPayTax()
{
    m_PayTaxProxy->show();
}

void BankView::hidePayOffDebt()
{
    m_PayOffDebtProxy->hide();
    m_DebtText->hide();
}

void BankView::hidePayUtility()
{
    m_PayUtiltyProxy->hide();
}

void BankView::hidePayRent()
{
    m_PayRentProxy->hide();
}

void BankView::hidePayTax()
{
    m_PayTaxProxy->hide();
}

void BankView::setPositions()
{
    //Buttons:
    m_PayOffDebtProxy->setPos(1105, 300);
    m_PayUtiltyProxy->setPos(1105, 105);
    m_PayRentProxy->setPos(1105, 105);
    m_PayTaxProxy->setPos(1105, 105);

    //Text:
    m_DebtText->setPos(100, 105);
}

void BankView::setScale()
{
    const int SCALEBUTTON = 2;
    const int SCALETEXT = 3;

    //Buttons:
    m_PayOffDebtProxy->setScale(SCALEBUTTON);
    m_PayUtiltyProxy->setScale(SCALEBUTTON);
    m_PayRentProxy->setScale(SCALEBUTTON);
    m_PayTaxProxy->setScale(SCALEBUTTON);

    //Text:
    m_DebtText->setScale(SCALETEXT);
}

