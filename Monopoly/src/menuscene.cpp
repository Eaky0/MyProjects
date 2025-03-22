#include "menuscene.h"

MenuScene::MenuScene(QObject * parent) : QGraphicsScene(parent)
{
    makeButtons();
    m_logo = this->addPixmap(QPixmap(":/board.bile.images/Monopolylogo.png"));
    m_logo->setPos(-10, -150);

    m_ChoiceAmountofPlayers = this->addText(tr("Amount of Players: "));
    m_ChoiceAmountofPlayers->hide();
    m_AmountOfPlayers = new QListWidget{};
    for (int i = 2; i < 7; ++i){
        m_AmountOfPlayers->addItem(QString::number(i));
    }

    m_AmountOfPlayersProxy = this->addWidget(m_AmountOfPlayers);
    m_AmountOfPlayers->setFixedHeight(100);
    m_ChoiceInfoText = this->addText(tr("Info:\n"
                                        "'New Game': will start an new game\n'"
                                        "Load Game': will allow you to load an previous save\n "
                                        "'Quit': will end the progam"));

    setScale();
    setPosition();

    m_StartGameButtonProxy->hide();
    m_CancelButtonProxy->hide();
    m_AmountOfPlayersProxy->hide();
    m_OkeyButtonProxy->hide();
    m_ChoiceInfoText->hide();
}

QPushButton *MenuScene::getNewGameButton()
{
    return m_NewGameButton;
}

QPushButton *MenuScene::getLoadGameButton()
{
    return m_LoadGameButton;
}

QPushButton *MenuScene::getQuitButton()
{
    return m_QuitButton;
}

QPushButton *MenuScene::getInfoButton()
{
    return m_InfoButton;
}

QPushButton *MenuScene::getOkeyButton()
{
    return m_OkeyButton;
}

QPushButton *MenuScene::getCancelButton()
{
    return m_CancelButton;
}

QPushButton *MenuScene::getStartGameButton()
{
    return m_StartGameButton;
}

QGraphicsTextItem * MenuScene::getInfoText()
{
    return m_ChoiceInfoText;
}

QListWidget * MenuScene::getPlayerSelect()
{
    return m_AmountOfPlayers;
}

QGraphicsPixmapItem * MenuScene::getLogo()
{
    return m_logo;
}

void MenuScene::makeButtons()
{
    m_NewGameButton = new QPushButton(tr("&New Game"));
    m_LoadGameButton = new QPushButton(tr("&Load Game"));
    m_QuitButton = new QPushButton(tr("&Quit"));
    m_InfoButton = new QPushButton(tr("&Info"));
    m_OkeyButton = new QPushButton(tr("&Ok"));
    m_CancelButton = new QPushButton (tr("&Cancel"));
    m_StartGameButton = new QPushButton (tr("&Start Game"));

    m_NewGameButtonProxy = this->addWidget(m_NewGameButton);
    m_LoadGameButtonProxy = this->addWidget(m_LoadGameButton);
    m_QuitButtonProxy = this->addWidget(m_QuitButton);
    m_InfoButtonProxy = this->addWidget(m_InfoButton);
    m_OkeyButtonProxy = this->addWidget(m_OkeyButton);
    m_StartGameButtonProxy = this->addWidget(m_StartGameButton);
    m_CancelButtonProxy = this->addWidget(m_CancelButton);
}

void MenuScene::setScale()
{
    const int BIGBUTTON = 5;
    const int SMALLBUTTON = 4;
    const int TEXT = 3;
    m_NewGameButtonProxy->setScale(BIGBUTTON);
    m_LoadGameButtonProxy->setScale(BIGBUTTON);
    m_QuitButtonProxy->setScale(BIGBUTTON);
    m_CancelButtonProxy->setScale(SMALLBUTTON);
    m_StartGameButtonProxy->setScale(SMALLBUTTON);
    m_ChoiceInfoText->setScale(TEXT);
    m_InfoButtonProxy->setScale(BIGBUTTON);
    m_OkeyButtonProxy->setScale(BIGBUTTON);
    m_AmountOfPlayersProxy->setScale(SMALLBUTTON);
}

void MenuScene::setPosition()
{
    m_NewGameButtonProxy->setPos(325,150);
    m_LoadGameButtonProxy->setPos(325, 300);
    m_QuitButtonProxy->setPos(325,600);
    m_InfoButtonProxy->setPos(325,450);
    m_OkeyButtonProxy->setPos(325,300);
    m_AmountOfPlayersProxy->setPos(30, 200);
    m_CancelButtonProxy->setPos(130, 600);
    m_StartGameButtonProxy->setPos(570, 600);
    m_ChoiceInfoText->setPos(225, 100);
}
