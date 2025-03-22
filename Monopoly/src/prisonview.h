//Author: Ieracitano Alessio
#ifndef PRISONVIEW_H
#define PRISONVIEW_H


#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QGraphicsScene>

class PrisonView
{
public:
    //Constructor
    PrisonView(QGraphicsScene* Scene);

    //Method:
    //Hide bail and jailcard buttons
    void hidePrisonView();

    //Method:
    //PRE: The player is in jail
    //PARAM: an boolean that is true if the player has an get out of jail card
    //Display the bail and jailcard (incase HasJailCard is true)
    void showPrisonView(const bool HasJailCard);

    //Methods:
    //Returns the address of the corresponding button
    QPushButton *getBailButtton();
    QPushButton *getJailCardButton();
private:

    QPushButton *m_PayBailButton;
    QPushButton *m_JailCardButton;

    QGraphicsProxyWidget *m_JailCardButtonProxy;
    QGraphicsProxyWidget *m_PayBailButtonProxy;
};

#endif // PRISONVIEW_H
