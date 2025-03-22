//Author: Kumas Atakan
#ifndef MENUSCENE_H
#define MENUSCENE_H


#include <QGraphicsScene>
#include <QListWidget>
#include <QGraphicsProxyWidget>
#include <QGraphicsTextItem>
#include <QPushButton>
#include <QVBoxLayout>

class MenuScene : public QGraphicsScene
{
public:
    //Constructor
    MenuScene(QObject * parent = nullptr);

    //Methods:
    //Return their corresponding button address.
    QPushButton* getNewGameButton();
    QPushButton* getLoadGameButton();
    QPushButton* getQuitButton();
    QPushButton *getInfoButton();
    QPushButton *getOkeyButton();
    QPushButton *getCancelButton();
    QPushButton *getStartGameButton();

    //Method:
    //Retrns the address of the infoText
    QGraphicsTextItem * getInfoText();

    //Method:
    //Returns the address of the QListWidget
    QListWidget * getPlayerSelect();

    //Method:
    //Returns the address of the QGraphicsPixmapItem
    QGraphicsPixmapItem * getLogo();

private:
    //Method:
    //Make all the buttons and their proxy's
    void makeButtons();

    //Method:
    //Set all buttons and text on an size
    void setScale();

    //Method:
    //Set all buttons and text on an appropiate place
    void setPosition();

    //members:
    QPushButton* m_NewGameButton;
    QPushButton* m_LoadGameButton;
    QPushButton* m_QuitButton;
    QPushButton* m_InfoButton;
    QPushButton* m_OkeyButton;
    QPushButton* m_CancelButton;
    QPushButton* m_StartGameButton;
    QGraphicsPixmapItem * m_logo;

    QListWidget * m_AmountOfPlayers;

    QGraphicsProxyWidget *m_NewGameButtonProxy;
    QGraphicsProxyWidget *m_LoadGameButtonProxy;
    QGraphicsProxyWidget *m_QuitButtonProxy;
    QGraphicsProxyWidget *m_AmountOfPlayersProxy;
    QGraphicsProxyWidget *m_InfoButtonProxy;
    QGraphicsProxyWidget *m_OkeyButtonProxy;
    QGraphicsProxyWidget *m_CancelButtonProxy;
    QGraphicsProxyWidget *m_StartGameButtonProxy;
    QGraphicsTextItem *m_ChoiceAmountofPlayers;


    QGraphicsTextItem *m_ChoiceInfoText;

};

#endif // MENUSCENE_H
