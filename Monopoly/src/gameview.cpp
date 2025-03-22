#include "gameview.h"

GameView::GameView(QWidget *parent)
    : QMainWindow(parent)
{

    m_MenuScene = new MenuScene{this};
    m_View = new QGraphicsView{m_MenuScene, this};

    //Put view Correctly
    m_View->setSceneRect(-100, -200, 1300, 1300);
    m_View->fitInView(0, 0, 150, 100, Qt::AspectRatioMode::KeepAspectRatioByExpanding);
    setCentralWidget(m_View);

    //connects:
    MenuConnects();
}

void GameView::buildMenu()
{
    m_TurnInfoText = m_Scene->addText(tr("Player 1's Turn"));

    makeButtons();
    setScale();
    setPosition();
    beginStatusButtons();

    m_MenuScene->getLogo()->hide();
    m_Card.hide();

}

void GameView::showThrowDiceButton()
{
    m_EndTurnButtonProxy->hide();
    //    m_BuildingOptions->getBuyBuilding()->hide();
    m_DiceButtonProxy->show();
}

void GameView::showBuyMenu(const int &Price)
{
    m_Scene->showYesNoButtons(Price);
    m_DiceButtonProxy->hide();
    m_EndTurnButtonProxy->hide();
    m_BuildingOptions->getBuyBuilding()->hide();
}

void GameView::showEndTurn()
{
    m_EndTurnButtonProxy->show();
}

void GameView::showBuyBuilding()
{
    m_BuildingOptions->getBuyBuilding()->show();
}

void GameView::showPayRent(const bool &IsCompany)
{
    if (IsCompany)
        m_Bank->showPayUtilty();
    else
        m_Bank->showPayRent();

    m_EndTurnButton->hide();
    m_BuildingOptions->getBuyBuilding()->hide();
}

void GameView::showPayTax()
{
    m_Bank->showPayTax();
}

void GameView::showPullCard(CardType &Type, Card &Action)
{
    m_Card.setCard(Type, Action);
    m_Card.show();
    m_PullCardButtonProxy->show();
}

void GameView::showPrisonOptions(bool throwDiceAllowed, bool JailCardObtained)
{
    if (throwDiceAllowed)
        m_DiceButtonProxy->show();

    m_PrisonButtons->showPrisonView(JailCardObtained);
    m_EndTurnButtonProxy->hide();
}



void GameView::ErrorReason(const QString Window, const QString Reason)
{
    QMessageBox::information(this, Window, Reason);
}


void GameView::hideBail_JailCard()
{
    m_PrisonButtons->hidePrisonView();
}

void GameView::GameConnects() const
{
    connect(m_SaveGameButton, &QPushButton::clicked, this, &GameView::saveGame);
    connect(m_EndGameButton, &QPushButton::clicked, this, &GameView::endGame);
    connect(m_DiceButton, &QPushButton::clicked, this, &GameView::throwDice);
    connect(m_Scene->getYesButton(), &QPushButton::clicked, this, &GameView::yes);
    connect(m_Scene->getNoButton(), &QPushButton::clicked, this, &GameView::no);

    connect(m_EndTurnButton, &QPushButton::clicked, this, &GameView::endTurn);
    connect(m_PullCardButton, &QPushButton::clicked, this, &GameView::playCard);

    connect(m_PrisonButtons->getBailButtton(), &QPushButton::clicked, this, &GameView::payBail);
    connect(m_PrisonButtons->getJailCardButton(), &QPushButton::clicked, this, &GameView::useJailCard);

    auctionConnects();
    gameRulesConnects();
    bankConnects();
    propertyConnects();
}

void GameView::propertyConnects() const
{
    connect(m_BuildingOptions->getBuyHouse(), &QPushButton::clicked, this, &GameView::buyHouse);
    connect(m_BuildingOptions->getBuyHotel(), &QPushButton::clicked, this, &GameView::buyHotel);
    connect(m_BuildingOptions->getBuyBuilding(), &QPushButton::clicked, this, &GameView::StreetOptions);
    connect(m_BuildingOptions->getCancelButton(), &QPushButton::clicked, this, &GameView::Cancel);
    connect(m_BuildingOptions->getSellHouse(), &QPushButton::clicked, this, &GameView::sellHouse);
    connect(m_BuildingOptions->getSellHotel(), &QPushButton::clicked, this, &GameView::sellHotel);
    connect(m_BuildingOptions->getMortgagePayOffButton(), &QPushButton::clicked, this, &GameView::payOffMortgage);
    connect(m_BuildingOptions->getMortgageTakeOutButton(), &QPushButton::clicked, this, &GameView::takeOutMortgage);
    connect(m_BuildingOptions->getKeepMortgageButton(), &QPushButton::clicked, this , &GameView::keepMortgage);
    connect(m_BuildingOptions->getStreetsButton(), &QPushButton::clicked, this, &GameView::StreetOptions);
    connect(m_BuildingOptions->getStationsButton(), &QPushButton::clicked, this, &GameView::StationOptions);
    connect(m_BuildingOptions->getCompaniesButton(), &QPushButton::clicked, this, &GameView::CompanyOptions);
}

void GameView::auctionConnects() const
{
    connect(m_Auction->getPlusOneButton(), &QPushButton::clicked, this, &GameView::plusOne);
    connect(m_Auction->getPlusFiveButton(), &QPushButton::clicked, this, &GameView::plusFive);
    connect(m_Auction->getPlusTenButton(), &QPushButton::clicked, this, &GameView::plusTen);
    connect(m_Auction->getPlusTwentyButton(), &QPushButton::clicked, this, &GameView::plusTwenty);
    connect(m_Auction->getPlusFiftyButton(), &QPushButton::clicked, this, &GameView::plusFifty);
    connect(m_Auction->getPlusHundredButton(), &QPushButton::clicked, this, &GameView::plusHundred);
    connect(m_Auction->getPlusFiveHundredButton(), &QPushButton::clicked, this, &::GameView::plusFiveHunderd);
    connect(m_Auction->getConfirmButton(), &QPushButton::clicked, this, &GameView::ConfirmBid);
    connect(m_Auction->getPassButton(), &QPushButton::clicked, this, &GameView::pass);

}

void GameView::gameRulesConnects() const
{
    GameRules* GameRules = m_Game->getGameRules();
    connect(GameRules, &GameRules::showDice, this, &GameView::showThrowDiceButton);
    connect(GameRules, &GameRules::JailOptions, this, &GameView::showPrisonOptions);
    connect(GameRules, &GameRules::showBuyProperty, this, &GameView::showBuyMenu);
    connect(GameRules, &GameRules::showEndTurn, this, &GameView::showEndTurn);
    connect(GameRules, &GameRules::hideBail_JailCard, this, &GameView::hideBail_JailCard);
    connect(GameRules, &GameRules::showTax, this, &GameView::showPayTax);
    connect(GameRules, &GameRules::startAuction, this, &GameView::startAuction);
    connect(GameRules, &GameRules::endAuction, this, &GameView::endAuction);
    connect(GameRules, &GameRules::updatePlayerBalance, this, &GameView::updateBalances);
    connect(GameRules, &GameRules::showPullCard, this, &GameView::showPullCard);
    connect(GameRules, &GameRules::showPropertyOptions, this, &GameView::showBuyBuilding);
    connect(GameRules, &GameRules::ErrorReason, this, &GameView::ErrorReason);
    connect(GameRules, &GameRules::UpdateBuildingTable, this, &GameView::UpdateTable);
    connect(GameRules, &GameRules::showRent, this, &GameView::showPayRent);
    connect(GameRules, &GameRules::showCaseWinner, this, &GameView::showCaseWinner);
}

void GameView::bankConnects() const
{
    //Bank
    Bank * Bank = m_Game->getBank();
    connect(Bank, &Bank::highestBid, this, &GameView::HighestBid);
    connect(Bank, &Bank::inheritedMortgages, this, &GameView::inheritedMortgages);
    connect(Bank, &Bank::debtToPay, this, &GameView::payOffDebt);

    connect(m_Bank->getPayUtiltyButton(), &QPushButton::clicked, this, &GameView::payUtility);
    connect(m_Bank->getPayRentButton(), &QPushButton::clicked, this, &GameView::payRent);
    connect(m_Bank->getPayTaxButton(), &QPushButton::clicked, this, &GameView::payTax);
    connect(m_Bank->getPayOffDebtButton(), &QPushButton::clicked, this, &GameView::PayDebt);
}

void GameView::setDiceRolls(QPair<int, int> &DiceRolls)
{
    m_Dices[0]->setNumber(DiceRolls.first);
    m_Dices[1]->setNumber(DiceRolls.second);
}

void GameView::makeButtons()
{
    m_SaveGameButton = new QPushButton(tr("&Save Game"));
    m_EndGameButton = new QPushButton(tr("&End Game"));
    m_DiceButton = new QPushButton(tr("&Throw Dice"));
    m_EndTurnButton = new QPushButton(tr("&End Turn"));
    m_PullCardButton = new QPushButton(tr("&Perform Card"));

    m_DiceButtonProxy = m_Scene->addWidget(m_DiceButton);
    m_EndTurnButtonProxy = m_Scene->addWidget(m_EndTurnButton);
    m_PullCardButtonProxy = m_Scene->addWidget(m_PullCardButton);
    m_SaveGameButtonProxy = m_Scene->addWidget(m_SaveGameButton);
    m_EndGameButtonProxy = m_Scene->addWidget(m_EndGameButton);
}

void GameView::beginStatusButtons()
{
    m_MenuScene->getPlayerSelect()->hide();
    m_MenuScene->getCancelButton()->hide();
    m_MenuScene->getStartGameButton()->hide();

    m_Bank->hidePayUtility();
    m_Bank->hidePayRent();
    m_Bank->hidePayTax();
    m_Bank->hidePayOffDebt();

    m_EndTurnButton->hide();
    m_PullCardButton->hide();
    m_SaveGameButton->hide();
    m_Scene->hideYesNoButtons();
}

void GameView::setScale()
{
    const int SCALE = 2;
    const int BIGBUTTON_SCALE = 3;
    const int TEXTSCALE = 5;

    m_DiceButtonProxy->setScale(SCALE);
    m_EndTurnButtonProxy->setScale(SCALE);
    m_PullCardButtonProxy->setScale(SCALE);
    m_SaveGameButtonProxy->setScale(BIGBUTTON_SCALE);
    m_EndGameButtonProxy->setScale(BIGBUTTON_SCALE);
    m_TurnInfoText->setScale(TEXTSCALE);
}

void GameView::setPosition()
{
    m_DiceButtonProxy->setPos(1105,55);
    m_EndTurnButtonProxy->setPos(1105, 55);
    m_PullCardButtonProxy->setPos(1105, 105);
    m_SaveGameButtonProxy->setPos(425, 1150);
    m_EndGameButtonProxy->setPos(825, 1150);
    m_TurnInfoText->setPos(0, -100);
}

void GameView::makeDice()
{
    m_Scene->addItem(&m_Card);
    m_Card.setPos(1150,300);

    DiceView *FirstDice = new DiceView;
    DiceView *SecondDice = new DiceView;

    //Add all items
    m_Scene->addItem(FirstDice);
    m_Scene->addItem(SecondDice);
    m_Dices.append(FirstDice);
    m_Dices.append(SecondDice);

    //Place all Items in their respective space
    FirstDice->setPos(820,120);
    SecondDice->setPos(900,120);
}

void GameView::mortgageAction(const bool &TakeOut)
{
    int TileNumber;
    bool Inherted = false;
    const int SelectedRow = m_BuildingOptions->getSelectedRow();

    if (m_BuildingOptions->getOptionMode() == OptionMode::STREET){
        streetMorgage(&TileNumber, SelectedRow, TakeOut);
    }

    else if (m_BuildingOptions->getOptionMode() == OptionMode::STATION){
        stationMorgage(&TileNumber, SelectedRow, TakeOut);
    }

    else if (m_BuildingOptions->getOptionMode() == OptionMode::COMPANY){
        companyMorgage(&TileNumber, SelectedRow, TakeOut);
    }
    else{
        instantMortgageChoice(&TileNumber, SelectedRow);
        Inherted = true;
    }
    m_Game->mortgage(TileNumber, TakeOut, Inherted);
}

void GameView::buySellBuilding(const bool &House, const bool &Buy)
{
    if (!m_BuildingOptions->getBuildingTable()->selectedItems().empty()){
        int TileNumber;
        int SelectedRow = m_BuildingOptions->getSelectedRow();
        for (int i = 0; i < m_PlayerStreets.size(); ++i){
            if (m_PlayerStreets[SelectedRow].first->getStreetName() == m_PlayerStreets[i].first->getStreetName()){
                TileNumber = m_PlayerStreets[i].second;
                break;
            }
        }
        m_Game->buyOrSellHouseHotel(TileNumber, House, Buy);    //if house == true en buy == true an house will be bougth
    }
    else
        ErrorReason(tr("No street has been selected"), tr("You have to select a street in order to purchase a building"));
}

void GameView::streetMorgage(int *TileNumber, const int &SelectedRow, const bool &TakeOut)
{

    *TileNumber = m_PlayerStreets[SelectedRow].second;

    if (m_PlayerStreets[SelectedRow].first->isMortgaged() && TakeOut)
        ErrorReason(tr("Can't Take Out Mortgage"), tr("Property is already mortgaged"));

    else if (!m_PlayerStreets[SelectedRow].first->isMortgaged() && !TakeOut)
        ErrorReason(tr("Can't pay off Mortgage"), tr("Property has not been not mortgaged"));

}

void GameView::stationMorgage(int *TileNumber, const int &SelectedRow, const bool &TakeOut)
{

    *TileNumber = m_PlayerStations[SelectedRow].second;
    if (m_PlayerStations[SelectedRow].first->isMortgaged() && TakeOut)
        ErrorReason(tr("Can't Take Out Mortgage"), tr("Property is already mortgaged"));

    else if (!m_PlayerStations[SelectedRow].first->isMortgaged() && !TakeOut)
        ErrorReason(tr("Can't pay off Mortgage"), tr("Property has not been not mortgaged"));

}

void GameView::companyMorgage(int *TileNumber, const int &SelectedRow, const bool &TakeOut)
{
    *TileNumber = m_PlayerCompanies[SelectedRow].second;

    if (m_PlayerCompanies[SelectedRow].first->isMortgaged()&& TakeOut)
        ErrorReason(tr("Can't Take Out Mortgage"), tr("Property is already mortgaged"));

    else if (!m_PlayerCompanies[SelectedRow].first->isMortgaged() && !TakeOut)
        ErrorReason(tr("Can't pay off Mortgage"), tr("Property has not been not mortgaged"));
}

void GameView::instantMortgageChoice(int *TileNumber, const int &SelectedRow)
{
    QList<QPair<Tile*, int>> Properties = m_Game->getBank()->getInheritedProperties();
    *TileNumber = Properties[SelectedRow].second;
}

void GameView::makePlayerInfoCards(const int &AmountPlayers)
{
    const int SPACEBETWEEN = 100;
    const int PosX = -200;
    int PosY = 30;

    for (int i = 0; i < AmountPlayers; ++i){
        Player* Player = m_Game->getPlayer(i);
        PlayerView* NewPlayer = new PlayerView{i, Player};

        m_Scene->addItem(NewPlayer);
        m_Players.push_back(NewPlayer);
        m_Players[i]->setPos(PosX,PosY);

        //To put some space between de players infoCards
        PosY += SPACEBETWEEN;
    }
}

void GameView::MenuConnects() const
{
    connect(m_MenuScene->getNewGameButton(), &QPushButton::clicked, this, &GameView::PlayerSelectionMenu);
    connect(m_MenuScene->getStartGameButton(), &QPushButton::clicked, this, &GameView::newGame);
    connect(m_MenuScene->getCancelButton(), &QPushButton::clicked, this, &GameView::returnToMenuFromInfo);
    connect(m_MenuScene->getLoadGameButton(), &QPushButton::clicked, this, &GameView::loadGame);
    connect(m_MenuScene->getQuitButton(), &QPushButton::clicked, &QApplication::quit);
    connect(m_MenuScene->getInfoButton(), &QPushButton::clicked, this, &GameView::gameInfo);
    connect(m_MenuScene->getOkeyButton(), &QPushButton::clicked, this, &GameView::returnToMenuFromInfo);
}

void GameView::throwDice()
{
    const bool MoveToken = true;

    QPair<int,int> RolledNumbers = m_Game->throwDice(MoveToken);
    setDiceRolls(RolledNumbers);

    m_DiceButtonProxy->hide();
    m_SaveGameButtonProxy->hide();
}

void GameView::showCaseWinner(int &Player)
{
    QString Reason = "WINNER: Player " + QString::number(Player);
    QMessageBox::information(this, "GAME END", Reason);
    QApplication::quit();
}

void GameView::inheritedMortgages()
{
    QList<QPair<Tile*, int>> Properties = m_Game->getBank()->getInheritedProperties();
    if (Properties.size() == 0){
        m_EndTurnButtonProxy->show();
        m_BuildingOptions->getBuildingTable()->hide();
        m_BuildingOptions->hideInhertedMortgageOptions();
        return;
    }

    m_BuildingOptions->getBuyBuilding()->hide();
    m_BuildingOptions->getBuildingTable()->show();

    m_BuildingOptions->getStreetsButton()->hide();
    m_BuildingOptions->getStationsButton()->hide();
    m_BuildingOptions->getCompaniesButton()->hide();
    m_BuildingOptions->setOptionMode(OptionMode::INHERTED);

    m_BuildingOptions->AdjustTableOptions();
    m_EndTurnButtonProxy->hide();

    m_BuildingOptions->getBuildingTable()->setRowCount((int)Properties.size());

    for (int index = 0; index < Properties.size(); ++index){
        QString NameToDisplay;

        if (Street* IsAnStreet = dynamic_cast<class Street *> (Properties[index].first))
            NameToDisplay = IsAnStreet->getStreetName() + "\n{Mortgaged}";
        else if (Station* IsAnStation = dynamic_cast<class Station *> (Properties[index].first))
            NameToDisplay = IsAnStation->getStationName() + "\n{Mortgaged}";
        else if (Company* IsAnCompany = dynamic_cast<class Company *> (Properties[index].first))
            NameToDisplay = IsAnCompany->getCompanyName() + "\n{Mortgaged}";
        else
            NameToDisplay = "ERROR\n{Mortgaged}";
        QTableWidgetItem * Item = new QTableWidgetItem{NameToDisplay};
        m_BuildingOptions->getBuildingTable()->setItem(index, 0, Item);
        m_BuildingOptions->getBuildingTable()->setRowHeight(index, 75);
    }
}

void GameView::payOffDebt(const int &Amount, const Figure &DebtTo)
{
    int PlayerNumberToDisplay = 0;
    if (DebtTo != Figure::NONE)
        PlayerNumberToDisplay = m_Game->getPlayerIndex(DebtTo) + 1;

    m_Bank->showPayOffDebt(Amount, PlayerNumberToDisplay);
    m_EndTurnButton->setEnabled(false);
    m_DiceButton->setEnabled(false);
    showBuyBuilding();
}

void GameView::yes()
{
    buyProperty(true);
}

void GameView::no()
{
    buyProperty(false);
}

void GameView::plusOne()
{
    const int AMOUNT = 1;
    m_Auction->increaseBidBy(AMOUNT);
}

void GameView::plusFive()
{
    const int AMOUNT = 5;
    m_Auction->increaseBidBy(AMOUNT);
}

void GameView::plusTen()
{
    const int AMOUNT = 10;
    m_Auction->increaseBidBy(AMOUNT);
}

void GameView::plusTwenty()
{
    const int AMOUNT = 20;
    m_Auction->increaseBidBy(AMOUNT);
}

void GameView::plusFifty()
{
    const int AMOUNT = 50;
    m_Auction->increaseBidBy(AMOUNT);
}

void GameView::plusHundred()
{
    const int AMOUNT = 100;
    m_Auction->increaseBidBy(AMOUNT);
}

void GameView::plusFiveHunderd()
{
    const int AMOUNT = 500;
    m_Auction->increaseBidBy(AMOUNT);
}

void GameView::ConfirmBid()
{
    m_Game->bidAuction(m_Auction->getBid());

    //Display the new bidder:
    int BidderIndex  = m_Game->getCurrentBidder();
    m_Auction->setCurrentBidder(BidderIndex);
    m_Auction->resetBid();

}

void GameView::pass()
{
    m_Game->bidPass();

    int BidderIndex  = m_Game->getCurrentBidder();
    m_Auction->setCurrentBidder(BidderIndex);
    m_Auction->resetBid();
}

void GameView::endTurn()
{
    m_Game->endTurn();
    int playerturn = m_Game->getCurrentPlayer();

    QString turn = "Player " + QString::number(playerturn + 1) + "'s Turn";
    m_TurnInfoText->setPlainText(turn);
    m_SaveGameButtonProxy->show();
    m_BuildingOptions->getBuyBuilding()->hide();
}

void GameView::payRent()
{
    m_Game->payRent();
    m_Bank->hidePayRent();
}

void GameView::payBail()
{
    m_Game->pay();

    m_PrisonButtons->hidePrisonView();
    m_DiceButtonProxy->hide();
    m_SaveGameButtonProxy->hide();

    m_EndTurnButtonProxy->show();
    m_EndTurnButton->setEnabled(true);
}

void GameView::useJailCard(){

    m_Game->useJailCard();

    m_PrisonButtons->hidePrisonView();
    m_DiceButtonProxy->hide();
    m_SaveGameButtonProxy->hide();

    m_EndTurnButtonProxy->show();
    m_EndTurnButton->setEnabled(true);
}

void GameView::startAuction(const int &AuctionTile)
{
    m_EndTurnButtonProxy->hide();
    m_DiceButton->hide();
    m_Game->setCurrentBidder();

    m_BuildingOptions->getBuyBuilding()->hide();

    const int BidderIndex  = m_Game->getCurrentBidder();
    m_Auction->setCurrentBidder(BidderIndex);
    m_Auction->setAuctionItem(AuctionTile);
    m_Auction->showAuctionView();
}

void GameView::HighestBid(const int amount, Player* HighestBidder)
{
    Figure Bidder = HighestBidder->getFigure();
    int PlayerIndex = m_Game->getPlayerIndex(Bidder);
    m_Auction->setHighestBidder(amount, PlayerIndex);
}

void GameView::endAuction()
{
    m_EndTurnButton->show();
    m_DiceButton->show();
    m_BuildingOptions->getBuyBuilding()->show();

    m_Auction->hideAuctionView();
}

void GameView::payTax()
{
    m_Game->pay();
    m_Bank->hidePayTax();
    m_EndTurnButtonProxy->show();
    m_EndTurnButton->setEnabled(true);
}

void GameView::playCard()
{
    m_PullCardButtonProxy->hide();
    m_Card.hide();
    m_Game->playCard();

}

void GameView::updateBalances()
{
    const int AmountPlayers = (int) m_Players.size();
    for (int i = 0; i < AmountPlayers; ++i){
        m_Players[i]->updateBalance();
    }
}

void GameView::newGame()
{
    QList<QListWidgetItem*> Players = m_MenuScene->getPlayerSelect()->selectedItems();

    if (!Players.isEmpty()){
        QString convert = Players[0]->text();
        const int Playernum = convert.toInt();
        m_Game = new Game{Playernum};
        m_Scene = new BoardView{m_Game->getBoard(), Playernum, this};
        m_PrisonButtons = new PrisonView{m_Scene};
        m_Auction = new AuctionView{m_Scene};
        m_Bank = new BankView{m_Scene};
        m_BuildingOptions = new PropertyView{m_Scene};

        makePlayerInfoCards(Playernum);
        makeDice();

        //Add all buttons:
        buildMenu();

        GameConnects();
        m_View->setScene(m_Scene);
    }
    else
    {
        ErrorReason(tr("Can not start a new game"), tr("User didn't choose an amount of players"));
    }
}

void GameView::PlayerSelectionMenu()
{
    m_MenuScene->getNewGameButton()->hide();
    m_MenuScene->getLoadGameButton()->hide();
    m_MenuScene->getQuitButton()->hide();
    m_MenuScene->getInfoButton()->hide();

    m_MenuScene->getPlayerSelect()->show();
    m_MenuScene->getCancelButton()->show();
    m_MenuScene->getStartGameButton()->show();
}

void GameView::saveGame()
{
    m_Game->save();
    m_SaveGameButton->hide();
}


void GameView::endGame()
{
    QPair<int, int> WinnerInfo = m_Game->exit();
    QString WinnerIndex = QString::number(WinnerInfo.first);
    QString WinnerBalance = QString::number(WinnerInfo.second);

    QString Reason = "Player " + WinnerIndex + " with an balance of " + WinnerBalance;
    QMessageBox::information(this, "WINNER :", Reason);
    QApplication::quit();
}

void GameView::loadGame()
{

}

void GameView::gameInfo()
{
    m_MenuScene->getNewGameButton()->hide();
    m_MenuScene->getLoadGameButton()->hide();
    m_MenuScene->getQuitButton()->hide();
    m_MenuScene->getInfoButton()->hide();
    m_MenuScene->getOkeyButton()->show();
    m_MenuScene->getInfoText()->show();
}

void GameView::returnToMenuFromInfo()
{
    m_MenuScene->getNewGameButton()->show();
    m_MenuScene->getLoadGameButton()->show();
    m_MenuScene->getQuitButton()->show();
    m_MenuScene->getInfoButton()->show();
    m_MenuScene->getOkeyButton()->hide();
    m_MenuScene->getInfoText()->hide();
    m_MenuScene->getPlayerSelect()->hide();
    m_MenuScene->getCancelButton()->hide();
    m_MenuScene->getStartGameButton()->hide();
}

void GameView::buyProperty(bool buy)
{
    m_Game->buyProperty(buy);
    m_Scene->hideYesNoButtons();
}

void GameView::UpdateTable()
{
    OptionMode current = m_BuildingOptions->getOptionMode();

    if (current == OptionMode::STREET)
        StreetOptions();
    else if (current == OptionMode::STATION)
        StationOptions();
    else if (current == OptionMode::COMPANY)
        CompanyOptions();
    else
        inheritedMortgages();
}

void GameView::StreetOptions()
{
    m_BuildingOptions->setOptionMode(OptionMode::STREET);
    m_BuildingOptions->AdjustTableOptions();
    m_EndTurnButtonProxy->hide();

    GameRules * GameRules = m_Game->getGameRules();
    m_PlayerStreets = GameRules->getPlayerStreets();
    m_BuildingOptions->getBuildingTable()->setRowCount((int)m_PlayerStreets.size());

    for (int index = 0; index < m_PlayerStreets.size(); ++index){
        QString Street;

        if (m_PlayerStreets[index].first->isMortgaged())
            Street = m_PlayerStreets[index].first->getStreetName() + "\n{Mortgaged}";
        else
            Street = m_PlayerStreets[index].first->getStreetName();

        QString Houses = QString::number(m_PlayerStreets[index].first->getHousesAndHotels().first);
        QString Hotels = QString::number(m_PlayerStreets[index].first->getHousesAndHotels().second);

        QTableWidgetItem * StreetItem = new QTableWidgetItem{Street};
        QTableWidgetItem * HouseItem = new QTableWidgetItem{Houses};
        QTableWidgetItem * HotelItem = new QTableWidgetItem{Hotels};

        m_BuildingOptions->getBuildingTable()->setItem(index, 0, StreetItem);
        m_BuildingOptions->getBuildingTable()->setItem(index, 1, HouseItem);
        m_BuildingOptions->getBuildingTable()->setItem(index, 2, HotelItem);
        m_BuildingOptions->getBuildingTable()->setRowHeight(index, 75);

        Street::Color StreetColor = m_PlayerStreets[index].first->getColor();
        m_BuildingOptions->setStreetColors(StreetColor, index);
    }
}


void GameView::StationOptions()
{
    m_BuildingOptions->setOptionMode(OptionMode::STATION);
    m_BuildingOptions->AdjustTableOptions();

    GameRules * GameRules = m_Game->getGameRules();
    m_PlayerStations = GameRules->getPlayerStations();
    m_BuildingOptions->getBuildingTable()->setRowCount((int)m_PlayerStations.size());


    for (int index = 0; index < m_PlayerStations.size(); ++index){
        QString Station;
        if (m_PlayerStations[index].first->isMortgaged())
            Station = m_PlayerStations[index].first->getStationName() + "\n{Mortgaged}";
        else
            Station = m_PlayerStations[index].first->getStationName();

        QTableWidgetItem * StationItem = new QTableWidgetItem{Station};

        m_BuildingOptions->getBuildingTable()->setItem(index, 0, StationItem);
        m_BuildingOptions->getBuildingTable()->setRowHeight(index, 75);
    }

}


void GameView::CompanyOptions()
{
    m_BuildingOptions->setOptionMode(OptionMode::COMPANY);
    m_BuildingOptions->AdjustTableOptions();

    GameRules * GameRules = m_Game->getGameRules();
    m_PlayerCompanies = GameRules->getPlayerCompanies();
    m_BuildingOptions->getBuildingTable()->setRowCount((int) m_PlayerCompanies.size());

    for (int index = 0; index < m_PlayerCompanies.size(); ++index){
        QString Company;
        if (m_PlayerCompanies[index].first->isMortgaged())
            Company = m_PlayerCompanies[index].first->getCompanyName() + "\n{Mortgaged}";
        else
            Company = m_PlayerCompanies[index].first->getCompanyName();

        QTableWidgetItem * CompanyItem = new QTableWidgetItem{Company};

        m_BuildingOptions->getBuildingTable()->setItem(index, 0, CompanyItem);
        m_BuildingOptions->getBuildingTable()->setRowHeight(index, 75);
    }
}

void GameView::PayDebt()
{
    bool Succeeded = m_Game->payDebt();

    m_EndTurnButton->setEnabled(true);
    m_DiceButton->setEnabled(true);

    if (!Succeeded){
        m_DiceButton->hide();
        m_BuildingOptions->getBuyBuilding()->hide();
    }

    m_Bank->hidePayOffDebt();
}

void GameView::payUtility()
{
    const bool MoveToken = false;
    QPair<int, int> DiceRoll = m_Game->throwDice(MoveToken);
    m_Game->payRent();
    setDiceRolls(DiceRoll);
    m_Bank->hidePayUtility();
}

void GameView::buyHouse()
{
    const bool House = true;
    const bool Buy = true;
    buySellBuilding(House, Buy);
}

void GameView::buyHotel()
{
    const bool House = false;
    const bool Buy = true;
    buySellBuilding(House, Buy);

}

void GameView::sellHouse()
{
    const bool House = true;
    const bool Buy = false; //buy == false, so we are selling it instead
    buySellBuilding(House,Buy);
}

void GameView::sellHotel()
{
    const bool Hotel = false;
    const bool Buy = false;
    buySellBuilding(Hotel, Buy);
}

void GameView::takeOutMortgage()
{
    if (!m_BuildingOptions->getBuildingTable()->selectedItems().empty()){
        const bool TakeOut = true;
        mortgageAction(TakeOut);
    }
    else
        ErrorReason(tr("No property has been selected"), tr("You have to select a property in order to take out a mortgage"));
}


void GameView::payOffMortgage()
{
    if (!m_BuildingOptions->getBuildingTable()->selectedItems().empty()){
        const bool TakeOut = false;
        mortgageAction(TakeOut);
    }
    else
        ErrorReason(tr("No property has been selected"), tr("You have to select a property in order to pay off a mortgage"));

}

void GameView::keepMortgage()
{
    if (!m_BuildingOptions->getBuildingTable()->selectedItems().empty()){
        const bool TakeOut = true;
        mortgageAction(TakeOut);
    }
    else
        ErrorReason(tr("No property has been selected"), tr("You have to select a property in order to Keep a mortgage"));
}

void GameView::Cancel()
{
    m_BuildingOptions->getBuyBuilding()->show();
    m_EndTurnButtonProxy->show();

    OptionMode ModeCancel = m_BuildingOptions->getOptionMode();

    if (ModeCancel == OptionMode::STREET)
        m_BuildingOptions->hideStreetOptionButtons();
    else
        m_BuildingOptions->hideStationCompanyOptionButtons();

    m_BuildingOptions->getBuildingTable()->setFocusPolicy(Qt::NoFocus);
    m_BuildingOptions->setOptionMode(OptionMode::STREET);
    m_BuildingOptions->getBuildingTable()->hide();

}

