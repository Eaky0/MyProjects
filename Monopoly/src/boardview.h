//Author: Kumas Atakan, Ieracitano Alessio
//------------------------
//Methods made by Alessio:
//getYesButton, getNoButton, hideYesNoButtons, showYesNoButtons
//------------------------
//Methods made by Atakan:
//BoardView, moveViewToken, getNewPos, InitTokens
//-----------------------
#ifndef BOARDVIEW_H
#define BOARDVIEW_H

#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPushButton>
#include <QGraphicsProxyWidget>


#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>
#include <QIODevice>
#include <QStringLiteral>


#include <QBrush>
#include <tileview.h>
#include <QList>
#include <QColor>
#include <board.h>



class BoardView : public QGraphicsScene
{
public:
    //Constructor
    BoardView(Board * model, int NPlayers, QObject * parent = nullptr);

    //Method:
    //PARAM: Number of the player (int), his oldposition (int), and his newposistion
    //Moves the figure of the corresponding, player from the old position to the new one
    void moveViewToken(int Playernumber, int prevPos, int newPos);

    //Method:
    //PARAM: The amount of players
    //inisialize the tokens
    void InitTokens(int Players = 2);

    //Methods:
    //Returns the address of the corresponding button
    QPushButton* getYesButton();
    QPushButton* getNoButton();

    //Method:
    //Hides the yes and no button, with the text that should be displayed
    void hideYesNoButtons();

    //Method:
    //displays the yes and no button together with the price of the property
    void showYesNoButtons(const int Price);
private:

    QGraphicsTextItem *m_BuyInfoText;
    QPushButton* m_YesButton;
    QPushButton* m_NoButton;

    QGraphicsProxyWidget *m_YesButtonProxy;
    QGraphicsProxyWidget *m_NoButtonProxy;

    QGraphicsRectItem * m_board;
    QGraphicsPixmapItem * m_Logo;
    QList<TileView *> m_Tiles{40};
    Board * m_ModelBoard;
};

#endif // BOARDVIEW_H
