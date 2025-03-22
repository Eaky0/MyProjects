//Author: Ieracitano Alessio
#ifndef BANKVIEW_H
#define BANKVIEW_H

#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QPushButton>

class BankView
{
public:
    BankView(QGraphicsScene* Scene);

    //Methods:
    //Returns the address of the buttons
    QPushButton* getPayOffDebtButton();
    QPushButton* getPayUtiltyButton();
    QPushButton* getPayRentButton();
    QPushButton* getPayTaxButton();

    //Method:
    //Showcases an an button to pay off your debt whith and the amount you
    //owe and to who.
    //PARAM: int (the amount of the debt), and the number to display (of which player)
    void showPayOffDebt(const int &Amount, const int &PlayerNumber);

    //Method:
    //PRE: the player needs to stand on an company tile
    //Showcases an button
    void showPayUtilty();

    //Method:
    //PRE: player stands on an tile that requires you to pay rent
    //Showcases an button
    void showPayRent();

    //Method:
    //PRE: player stands on an  tax tile
    //Showcases an button
    void showPayTax();

    //Method:
    //hides all the buttons and text that are displayed through the method showPayOffDebt
    void hidePayOffDebt();

    //Methods:
    //Hides the corresponding button
    void hidePayUtility();
    void hidePayRent();
    void hidePayTax();
private:
    //Method:
    //Sets the position of all the text and butttons
    void setPositions();
    //Method:
    //Sets the scale of all the text and butttons
    void setScale();

    //members:
    QPushButton* m_PayOffDebtButton;
    QPushButton* m_PayUtiltyButton;
    QPushButton* m_PayRentButton;
    QPushButton* m_PayTaxButton;

    QGraphicsProxyWidget *m_PayOffDebtProxy;
    QGraphicsProxyWidget *m_PayUtiltyProxy;
    QGraphicsProxyWidget *m_PayRentProxy;
    QGraphicsProxyWidget *m_PayTaxProxy;

    QGraphicsTextItem *m_DebtText;
};

#endif // BANKVIEW_H
