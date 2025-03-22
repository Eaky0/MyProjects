#include "boardview.h"

BoardView::BoardView(Board * model, int NPlayers, QObject * parent) : QGraphicsScene(parent)
{
    m_ModelBoard = model;
    const int TILESIZE = 100;
    const int AMOUNT_TILES = 40;
    const int AMOUNT_TILES_IN_ROW = 10;
    const int BEGIN = 0;
    const int END_LEFT_ROW = 10;
    const int END_TOP_ROW = 20;
    const int END_RIGHT_ROW = 30;

    m_board = this->addRect(0, 0, 1100, 1100, QPen{}, QColor(205, 255, 220));
    m_Logo = this->addPixmap(QPixmap(":/board.bile.images/Monopolylogo.png"));
    m_Logo->setPos(450, 400);
    m_Logo->setScale(0.4);
    m_Logo->setRotation(45);

    QGraphicsRectItem * ChanceCardRect = this->addRect(0, 0, 200, 100, QPen{}, QColor(255, 140, 0));
    QGraphicsTextItem * ChanceText = this->addText("Chance");

    QGraphicsRectItem * CChestCardRect = this->addRect(0, 0, 200, 100, QPen{}, QColor(212, 175, 55));
    QGraphicsTextItem * CChestText = this->addText("Community Chest");


    ChanceCardRect->setRotation(45);
    ChanceCardRect->setScale(1.5);
    ChanceCardRect->setPos(660, 280);
    ChanceCardRect->boundingRect();
    ChanceText->setParentItem(ChanceCardRect);
    ChanceText->setScale(2);
    ChanceText->setPos(50, 25);


    CChestCardRect->setRotation(45);
    CChestCardRect->setScale(1.5);
    CChestCardRect->setPos(325, 600);
    CChestText->setParentItem(CChestCardRect);
    CChestText->setScale(1.5);
    CChestText->setPos(25, 25);


    QFile TileInfo(QStringLiteral(":/Json_files/tiles.json"));

    if (!TileInfo.open(QIODevice::ReadOnly)){
        qDebug() << "JSON file not accesible :(";
        return;
    }

    QByteArray TileData = TileInfo.readAll();
    QJsonDocument TileDocument = QJsonDocument::fromJson(TileData);
    QJsonObject TileObject = TileDocument.object();
    QJsonValue JsonTile;
    QString JsonString;
    QString JsonStreetColor;

    for (int index = 0; index < AMOUNT_TILES; ++index){

        m_Tiles[index] = new TileView{TILESIZE, TILESIZE, index};

        //Starting tile
        if (index == 0){
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["actiontype"].toString();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(15, 20);
            TileText->setScale(2);

        }

        //Community chest tiles
        else if (index == 2 || index == 17 || index == 33){
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["actiontype"].toString();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(0, 40);


        }

        //Income tax tile
        else if (index == 4){
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["actiontype"].toString();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(0, 30);
            TileText->setScale(1.5);

        }

        // Super Tax tile
        else if (index == 38){
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["actiontype"].toString();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(0, 30);
            TileText->setScale(1.5);

        }

        //Chance card tiles
        else if (index == 7 || index == 22 || index == 36){
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["actiontype"].toString();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(10, 30);
            TileText->setScale(1.5);
        }

        //GO TO JAIL
        else if (index == 30){
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["actiontype"].toString().toUpper();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(0, 30);
            TileText->setScale(1.5);

        }

        //JAIL or FREE PARKING tile (default tiles)
        else if (index == 10 || index == 20){
            QGraphicsTextItem * TileText;
            if (index == 10)
                TileText = this->addText("JAIL");
            else
                TileText = this->addText("FREE\nPARKING");

            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(0, 40);
            TileText->setScale(1.5);
        }

        //Station tiles
        else if (index == 5 || index == 15 || index == 25 || index == 35){
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["stationname"].toString();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(0, 20);
            TileText->setScale(1.3);

        }


        //Company Tiles
        else if (index == 12 || index == 28){
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["companyname"].toString();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(0, 30);
            TileText->setScale(1.2);

        }

        //Street tiles
        else{
            JsonTile = TileObject[QString::number(index)];
            JsonString = JsonTile["streetname"].toString();
            JsonStreetColor = JsonTile["color"].toString();
            QGraphicsTextItem * TileText = this->addText(JsonString);
            if (JsonStreetColor == "Brown"){
                m_Tiles[index]->setBrush(QColor(165, 42, 42));
                TileText->setDefaultTextColor(Qt::white);

            }
            else if (JsonStreetColor == "Blue"){
                m_Tiles[index]->setBrush(Qt::blue);
                TileText->setDefaultTextColor(Qt::white);
            }
            else if (JsonStreetColor == "Pink"){
                m_Tiles[index]->setBrush(QColor(255, 192, 203));

            }
            else if (JsonStreetColor == "Orange"){
                m_Tiles[index]->setBrush(QColor(255, 165, 0));

            }
            else if (JsonStreetColor == "Red"){
                m_Tiles[index]->setBrush(Qt::red);

            }
            else if (JsonStreetColor == "Yellow"){
                m_Tiles[index]->setBrush(Qt::yellow);

            }
            else if (JsonStreetColor == "Green"){
                m_Tiles[index]->setBrush(Qt::green);

            }
            else if (JsonStreetColor == "Dark Blue"){
                m_Tiles[index]->setBrush(Qt::darkBlue);
                TileText->setDefaultTextColor(Qt::white);
            }



            TileText->setParentItem(m_Tiles[index]);
            TileText->setPos(0, 30);
            TileText->setScale(1.2);

        }




        m_Tiles[index]->setParentItem(m_board);
        if (BEGIN <=  index && index <= END_LEFT_ROW){
            m_Tiles[index]->setPos(BEGIN, (END_LEFT_ROW - index) * TILESIZE);
        }

        else if (END_LEFT_ROW < index && index <= END_TOP_ROW){
            m_Tiles[index]->setPos((index - END_LEFT_ROW) * TILESIZE, BEGIN);
        }

        else if (END_TOP_ROW < index && index <= END_RIGHT_ROW){
            m_Tiles[index]->setPos(TILESIZE * AMOUNT_TILES_IN_ROW, (index - END_TOP_ROW) * TILESIZE);
        }
        else
            m_Tiles[index]->setPos((AMOUNT_TILES - index) * TILESIZE, TILESIZE * AMOUNT_TILES_IN_ROW);
    }

    InitTokens(NPlayers);

    m_YesButton = new QPushButton(tr("&Yes"));
    m_NoButton = new QPushButton(tr("&No"));

    m_YesButtonProxy = this->addWidget(m_YesButton);
    m_NoButtonProxy = this->addWidget(m_NoButton);

    m_YesButtonProxy->setScale(2);
    m_NoButtonProxy->setScale(2);


    m_YesButtonProxy->setPos(1255,305);
    m_NoButtonProxy->setPos(1105,305);

    m_BuyInfoText = this->addText(tr("Buy?"));
    m_BuyInfoText->setScale(3);
    m_BuyInfoText->setPos(1105 + (1255-1105)/2,205);

    connect(m_ModelBoard, &Board::TokenWillMove, this, &BoardView::moveViewToken);
}

void BoardView::moveViewToken(int Playernumber, int prevPos, int newPos)
{
    QList<QGraphicsItem *> m_TileChildren = m_Tiles[prevPos]->childItems();

    qDebug() << "BOARDVIEW - PREVPOS: " << prevPos;
    qDebug() << "BOARDVIEW - NEWPOS: " << newPos;

    for (auto i = 0; i < m_TileChildren.size(); ++ i){
        QGraphicsPixmapItem * Child = static_cast<QGraphicsPixmapItem *> (m_TileChildren[i]);
        TokenView * ChildToMove = static_cast<TokenView *>(Child);

        if (ChildToMove->getPlayer() == Playernumber){
            ChildToMove->setParentItem(m_Tiles[newPos]);
        }
    }
}

QPushButton *BoardView::getYesButton()
{
    return m_YesButton;
}

QPushButton *BoardView::getNoButton()
{
    return m_NoButton;
}

void BoardView::hideYesNoButtons()
{
    m_YesButtonProxy->hide();
    m_NoButtonProxy->hide();
    m_BuyInfoText->hide();
}

void BoardView::showYesNoButtons(const int Price)
{
    QString DisplayText = "Buy for " + QString::number(Price) + "?";
    m_BuyInfoText->setPlainText(DisplayText);

    m_YesButtonProxy->show();
    m_NoButtonProxy->show();
    m_BuyInfoText->show();
}

void BoardView::InitTokens(int Players)
{
    TokenView * m_Token1 = new TokenView{0, "car"};
    m_Tiles[0]->setToken(m_Token1);
    TokenView * m_Token2 = new TokenView{1, "hat"};
    m_Tiles[0]->setToken(m_Token2);


    if (2 < Players){
        TokenView * m_Token3 = new TokenView{2, "wheelbarrow"};
        m_Tiles[0]->setToken(m_Token3);
    }
    if (3 < Players){
            TokenView * m_Token4 = new TokenView{3, "boot"};
            m_Tiles[0]->setToken(m_Token4);
    }
    if (4 < Players){
        TokenView * m_Token5 = new TokenView{4, "ship"};
        m_Tiles[0]->setToken(m_Token5);

    }
    if (5 < Players){
        TokenView * m_Token6 = new TokenView{5, "cannon"};
        m_Tiles[0]->setToken(m_Token6);

    }
}
