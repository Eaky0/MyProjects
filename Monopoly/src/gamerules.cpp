#include "gamerules.h"

GameRules::GameRules(int AmountPlayers) : m_Bank{AmountPlayers} {}

bool GameRules::isCompanyTile(const int &PosToken)
{
    return m_Bank.isCompanyTile(PosToken);
}

void GameRules::decideWinner(std::vector<Player> Players)
{
    const int AMOUNTPLAYERS = (int) Players.size();

    for (int i = 0 ; i < AMOUNTPLAYERS; ++i){
        if (!Players[i].isPlayerBankrupt()){
            int Player = i + 1;
            emit showCaseWinner(Player);
        }
    }
}

void GameRules::playerWentBankrupt(Player *Player)
{
    m_Bank.setAuctionItem(Player);
    m_Bank.cantPayDebt(Player);

    if(m_Bank.hasAuctionItem())
        emit startAuction(m_Bank.getAuctionItem());
}

void GameRules::playerOptions()
{
    bool InJail = m_CurrentPlayer->getPlayerStatus();
    if (InJail){
        bool DiceAllowed = !(m_CurrentPlayer->getRoundsInJail() == 3);
        bool PlayerHasJailCard = m_CurrentPlayer->hasJailCard();
        emit JailOptions(DiceAllowed, PlayerHasJailCard);
    }
    else{
        emit showDice();
    }
}

void GameRules::checkForDoubleThrows(const int &AmountDoubleThrows)
{
    bool InJail = m_CurrentPlayer->getPlayerStatus();
    if (!InJail && AmountDoubleThrows > 0)
            emit showDice();
    else{
        emit updatePlayerBalance();
        emit showEndTurn();
        emit showPropertyOptions();
    }
}

bool GameRules::buyPropertyRule(const bool &Buy)
{
    const int BalancePlayer = m_CurrentPlayer->getBalance();
    const int PriceProperty = m_Bank.getCosts(m_CurrentPlayer->getFigure());
    const bool CanAfford = (BalancePlayer >= PriceProperty);
    const bool NoAuction = (Buy && CanAfford);

    if (NoAuction){
        m_Bank.buyProperty(m_CurrentPlayer);
        emit updatePlayerBalance();
    }

    else{
        m_CurrentPlayer->setPlayerPassed(true);
        const int AuctionTile = m_Bank.getPlayerPos(m_CurrentPlayer->getFigure());
        m_Bank.setAuctionItem(AuctionTile);
        emit startAuction(AuctionTile);
    }
    return (NoAuction);
}


bool GameRules::payRent(Player *Owner)
{
    m_Bank.payRent(m_CurrentPlayer, Owner);
    return paymentSucceeded();
}

bool GameRules::payRent(Player *Owner, const int DiceRollAmount)
{
    m_Bank.payRent(m_CurrentPlayer, Owner, DiceRollAmount);
    return paymentSucceeded();
}

bool GameRules::pay()
{
    m_Bank.pay(m_CurrentPlayer);
    return paymentSucceeded();
}

bool GameRules::payDebt()
{
    bool Succeeded = m_Bank.payOffDebt(m_CurrentPlayer);

    if (!Succeeded){
        playerWentBankrupt(m_CurrentPlayer);
        return false;
    }

    return true;
}

void GameRules::jailCardRule()
{
    Card* ReturnCard = m_CurrentPlayer->removeCard();
    m_Bank.returnCardToDeck(ReturnCard);
    m_CurrentPlayer->playerInJail(false);
}

void GameRules::moveToken(const int &TotalAmountJumps, const int &AmountDoubleThrows)
{
    const int GOTOPRISON_TILE = 30;
    const int PRISONTILE = 10;

    bool InJail = m_CurrentPlayer->getPlayerStatus();
    bool IsDoubleThrow = (0 < AmountDoubleThrows);
    bool IsTripleDoubleThrow = (3 == AmountDoubleThrows);

    prisonRules(IsDoubleThrow, InJail, IsTripleDoubleThrow);
    int NewPosToken = PRISONTILE;

    if (!InJail){
        const int LAST_TILENUMBER = 39;
        const int AMOUNT_TILES = 40;

        int CurrentPosToken = m_Bank.getPlayerPos(m_CurrentPlayer->getFigure());
        NewPosToken = CurrentPosToken + TotalAmountJumps;

        //We make sure the TileIndex isn't out of bounds
        if (NewPosToken > LAST_TILENUMBER){
            NewPosToken -= AMOUNT_TILES;
            m_Bank.passedStartMoney(m_CurrentPlayer);
        }
        //If the Tile says to go to prison
        if (NewPosToken == GOTOPRISON_TILE){
            goToJail();
            NewPosToken = PRISONTILE;
        }
        //Else we move to token
        else
            m_Bank.moveToken(m_CurrentPlayer->getFigure(), NewPosToken);
    }
    tileCheck(NewPosToken, m_CurrentPlayer->getFigure());
}

void GameRules::goToJail()
{
    const int PRISONTILE = 10;
    m_CurrentPlayer->playerInJail(true);
    m_Bank.moveToken(m_CurrentPlayer->getFigure(), PRISONTILE);
}

bool GameRules::mortgageStreetRules(const int TileNumber)
{
    bool Permision;
    if (m_Bank.ownsFullColorSet(TileNumber, m_CurrentPlayer->getFigure())){
        if(m_Bank.colorSetHasNoBuilding(TileNumber)){
            Permision = true;
        }
        else{
            Permision = false;
            emit ErrorReason(tr("Can't Take Out Mortgage"), tr("Colorset of street contains buildings"));
        }

    }
    else{
        Permision = false;
        emit ErrorReason(tr("Can't Take Out Mortgage"), tr("Player doesn't own the full color set"));
    }
    return Permision;
}

void GameRules::mortgageAction(const int TileNumber, const bool &What, const bool &Inherted)
{
    Player * ActionOf;
    if (!Inherted)
        ActionOf = m_CurrentPlayer;
    else{
        ActionOf = m_Bank.getDebtToPlayer();
    }

    m_Bank.payOrTakeMortgage(TileNumber, ActionOf, What, Inherted);
    emit UpdateBuildingTable();
    emit updatePlayerBalance();
}

void GameRules::prisonRules(const bool &IsDoubleThrow, bool &InJail, const bool &IsTripleDoubleThrow)
{
    if (InJail){
        //if the player threw an double he is free and is allowed to move the thrown amount
        if (IsDoubleThrow){
            m_CurrentPlayer->playerInJail(false);
            InJail = false;
        }
        //Indepentdent of the result of the prisoner his throw, the bail option will be set to hidden.
        emit hideBail_JailCard();
    }

    //If the player isn't in jail, and he has thrown triple doubles in an row,
    //he will be sent to jail.
    else if (IsTripleDoubleThrow){
        goToJail();
        InJail = true;
    }
}

bool GameRules::paymentSucceeded()
{
    emit updatePlayerBalance();

    const bool PaySucceeded = (!m_Bank.hasDebt());
    return PaySucceeded;
}

void GameRules::passBid(Player* CurrentBidder, const int &Amount, const bool &LastBid)
{
    m_Bank.auctionProperty(CurrentBidder, Amount, LastBid);

    //if it is the last bid we emit the end of the auction
    //and update the player balance.
    if (LastBid){
        emit updatePlayerBalance();
        emit endAuction();

        //Incase we have more items in the auction list
        //then that means we are selling properties of an bankrupt player
        //and we need to start the auction for the next item
        if (m_Bank.hasAuctionItem()){
            emit startAuction(m_Bank.getAuctionItem());
        }
    }
}

bool GameRules::hasHighestBidder()
{
    return m_Bank.hasHighestBidder();
}

Figure GameRules::getPropertyOwner(const int &TileNumber)
{
    return m_Bank.getPropertyOwner(TileNumber);
}

bool GameRules::propertyHasOwner(const Figure &PlayerFigure)
{
    return m_Bank.propertyHasOwner(PlayerFigure);
}

void GameRules::setCurrentPlayer(Player *CurrentPlayer)
{
    m_CurrentPlayer = CurrentPlayer;
}

Board *GameRules::getBoard()
{
    return m_Bank.getBoard();
}

Bank *GameRules::getBank()
{
    return &m_Bank;
}

void GameRules::applyHouseHotelRules(const int &TileNumber, bool *ToAuction, bool *MaxBuildings, bool *PlacementRule, const bool &BuyHouse)
{
    QPair<int, int> AmountBankBuildings = m_Bank.getAmountBankBuildings();
    QPair<int, int> AmountSteetBuildings = m_Bank.getAmountStreetBuildings(TileNumber);

    const int MAXHOUSES = 4;
    const int MAXHOTELS = 1;
    const int LASTBUILDING = 1;

    bool EnoughHousesOnAll = m_Bank.colorSetHasSameAmountHouses(TileNumber);
    bool Mortgaged = m_Bank.checkMortgageState(TileNumber);

    //Next we check if we need to place an house or hotel, and adjust to the corresponding rules
    if (BuyHouse){
        *ToAuction = AmountBankBuildings.first == LASTBUILDING;
        *MaxBuildings = (AmountSteetBuildings.first == MAXHOUSES || AmountSteetBuildings.second == MAXHOTELS);
        *PlacementRule = (EnoughHousesOnAll && !Mortgaged);
    }
    else {
        bool HotelRule = (AmountSteetBuildings.first == 4);
        *PlacementRule = (EnoughHousesOnAll && HotelRule && !Mortgaged);

        *ToAuction = AmountBankBuildings.second == LASTBUILDING;
        *MaxBuildings = (AmountSteetBuildings.second == MAXHOTELS);
    }
}

void GameRules::buyHouseHotelRule(const int &TileNumber, const bool &House)
{
    bool OwnsFullColorSet = m_Bank.ownsFullColorSet(TileNumber, m_CurrentPlayer->getFigure());
    if (!OwnsFullColorSet){
        emit ErrorReason("Color set not owned", "You don't fully own the entire color set!");
        return;
    }

    bool PlacementRule;
    bool ToAuction;     //if there is only one building left to buy
    bool MaxBuildings;  //if all houses or an hotel has been placed

    //We Adjust to the corresponding rules (house rules or hotels rules)
    applyHouseHotelRules(TileNumber, &ToAuction, &MaxBuildings, &PlacementRule, House);

    //if it isn't the last house or hotel to be bought and if the max amount of buildings aren't already placed
    //And it fullfills the placemnt rule we will pas the transaction and placemnt to bank
    if (!ToAuction && PlacementRule && !MaxBuildings){
        m_Bank.buyHouseHotel(TileNumber, m_CurrentPlayer, House);
        emit UpdateBuildingTable();
        emit updatePlayerBalance();
    }

    else if (ToAuction){      //If it is an auction we will need to start one for the last building.
        emit ErrorReason(tr("Building can't be placed"), tr("Only one builing of this type left, an auction should commence"));
    }

    else
        emit ErrorReason(tr("Building can't be placed"), tr("Possible reasons:\n-Maximum amount of buildings limit reached for the street\n-Same color streets are behind on buildings\n-The street is mortgaged"));
}

void GameRules::sellHouseHotelRule(const int &TileNumber, const bool &SellHouse)
{
    QPair<int, int> AmountBuildings = m_Bank.getAmountStreetBuildings(TileNumber);
    const int AmountHouses = AmountBuildings.first;
    const int AmountHotel = AmountBuildings.second;

    if (m_Bank.ownsFullColorSet(TileNumber, m_CurrentPlayer->getFigure())){
        if (SellHouse && AmountHouses <= 0){
            emit ErrorReason("Error", "Not enough houses to sell");
            return;
        }

        const bool SellHotel = !SellHouse;
        if (SellHotel && AmountHotel <= 0){
            emit ErrorReason("Error", "No hotel to sell");
            return;
        }
    }
    else{
        emit ErrorReason(tr("Color set not owned"), tr("You don't fully own the entire color set!"));
        return;
    }

    m_Bank.sellHouseHotel(TileNumber, m_CurrentPlayer, SellHouse);
    emit UpdateBuildingTable();
    emit updatePlayerBalance();
}

void GameRules::tileCheck(const int &posToken, const Figure &CurrentPlayer)
{
    Figure PropertyOwner = m_Bank.getPropertyOwner(posToken);
    bool PropertyBuyable = m_Bank.propertyBuyable(posToken);
    bool isCompany = m_Bank.isCompanyTile(posToken);
    bool HasOwner = m_Bank.propertyHasOwner(CurrentPlayer);
    bool IsMortgaged = m_Bank.checkMortgageState(posToken);
    bool PlayerIsOwner = (PropertyOwner == CurrentPlayer);
    bool TaxToPay = m_Bank.checkTax(posToken);
    bool PullCard = m_Bank.checkCard(posToken);

    if (PropertyBuyable){
        const int Price = m_Bank.getCosts(CurrentPlayer);
        emit showBuyProperty(Price);
    }
    else if (!PlayerIsOwner && HasOwner && !IsMortgaged){
        emit showRent(isCompany);
    }
    else if (TaxToPay){
        emit showTax();
    }
    else if(PullCard){
        CardType Type = m_Bank.getCardType(m_CurrentPlayer);
        Card * InfoTopCard = m_Bank.getCard(Type);
        emit showPullCard(Type, *InfoTopCard);
    }
    else{
        emit showEndTurn();
        emit showPropertyOptions();
    }
}

void GameRules::cardPerformingRule(std::vector<Player> *AllPLayers, const int &DoubleThrows)
{
    CardType Card = m_Bank.getCardType(m_CurrentPlayer);

    if (Card == CardType::CHANCE){
        playChanceCard(AllPLayers, DoubleThrows);
    }

    else{
        playCChestCard(AllPLayers, DoubleThrows);
    }

    emit updatePlayerBalance();
}

void GameRules::playChanceCard(std::vector<Player> *AllPlayers, int DoubleThrows)
{
    Card * Task = m_Bank.getCardAction(CardType::CHANCE);
    int CardNumber = Task->getCardNumber();
    int position = m_Bank.getPlayerPos(m_CurrentPlayer->getFigure());

    if (Advancement * i = dynamic_cast<Advancement *>(Task)){
        chanceAdvancement(DoubleThrows, i, position);

    }
    else if (Payment * i = dynamic_cast<Payment *>(Task)){
        chancePayment(AllPlayers, DoubleThrows, CardNumber, i);
    }
    else{
        if (CardNumber == 8){
            int threestepsback = position - 3;
            moveToken(threestepsback - position, DoubleThrows);
        }
        //Cardnumber == 7 (Obtain or use get out of Jail Card)
        else{
            m_CurrentPlayer->addCard(Task);
            m_Bank.removeCard(CardType::CHANCE);
            checkForDoubleThrows(DoubleThrows);
        }

    }
    emit updatePlayerBalance();
}

void GameRules::chanceAdvancement(int DoubleThrows, Advancement * AdvanceTo, int position)
{
    QString goTo = AdvanceTo->getAdvancement();
    if (goTo == "Trafalgar Square"){
        moveToken(24 - position, DoubleThrows);
        if (position == 36){
            m_Bank.passedStartMoney(m_CurrentPlayer);
        }
    }
    else if (goTo == "Start"){
        moveToken(0 - position, DoubleThrows);
        m_Bank.passedStartMoney(m_CurrentPlayer);
        checkForDoubleThrows(DoubleThrows);
    }
    else if (goTo == "Mayfair"){
        moveToken(39 - position, DoubleThrows);
    }
    else if (goTo == "Pall Mall"){
        moveToken(11 - position, DoubleThrows);
        if (position == 22 || position == 36){
            m_Bank.passedStartMoney(m_CurrentPlayer);
        }
    }
    else if (goTo == "Station"){
        if (position == 7){
            moveToken(5 - position, DoubleThrows);
        }
        else if (position == 22){
            moveToken(25 - position, DoubleThrows);
        }
        else if (position == 36){
            moveToken(35 - position, DoubleThrows);
        }
    }
    else if(goTo == "Company"){
        if (position == 7){
            moveToken(12 - position, DoubleThrows);
        }
        //If position == 22 || 36
        else{
            moveToken(28 - position, DoubleThrows);
        }
    }
    else if(goTo == "Jail"){
        moveToken(10 - position, DoubleThrows);
        m_CurrentPlayer->playerInJail(true);
    }
    else if (goTo == "Kings Cross Station"){
        moveToken(5 - position, DoubleThrows);
        if (position == 22 || position == 36){
            m_Bank.passedStartMoney(m_CurrentPlayer);
        }
    }
}

void GameRules::chancePayment (std::vector<Player> * AllPlayers, int DoubleThrows, int CardNumber, Payment * payment)
{
    //Pay for each hotel 100 and for each house 25
    if (CardNumber == 10){
        QList<QPair<Street *, int>> PlayerStreets = m_Bank.getPlayerStreets(m_CurrentPlayer->getFigure());
        for (auto index : PlayerStreets){
            Street * currentStreet = index.first;
            m_CurrentPlayer->moneyTransaction(payment->getPayment().at(0) * currentStreet->getHousesAndHotels().first, payment->getTypeOfPayment());
            m_CurrentPlayer->moneyTransaction(payment->getPayment().at(1) * currentStreet->getHousesAndHotels().second, payment->getTypeOfPayment());
        }
    }
    //Pay each player 50 MM
    else if (CardNumber == 13){
        for (auto i : *AllPlayers){
            if (m_CurrentPlayer->getFigure() != i.getFigure()){
                m_CurrentPlayer->moneyTransaction(payment->getPayment().at(0), payment->getTypeOfPayment());
                i.moneyTransaction(payment->getPayment().at(0), TransactionType::Recieve);
            }
        }
    }
    else
        m_CurrentPlayer->moneyTransaction(payment->getPayment().at(0), payment->getTypeOfPayment());
    checkForDoubleThrows(DoubleThrows);

}

void GameRules::playCChestCard(std::vector<Player> *AllPLayers, int DoubleThrows)
{
    Card * Task = m_Bank.getCardAction(CardType::COMMUNITYCHEST);
    int CardNumber = Task->getCardNumber();
    int position = m_Bank.getPlayerPos(m_CurrentPlayer->getFigure());

    if (Advancement * i = dynamic_cast<Advancement *>(Task)){
        cChestAdvancement(DoubleThrows, i, position);
    }
    else if (Payment * i = dynamic_cast<Payment *>(Task)){
        cChestPayment(AllPLayers, DoubleThrows, CardNumber, i);
    }
    //CardNumber == 4 (Obtain or use get out of Jail Card)
    else{
        m_CurrentPlayer->addCard(Task);
        m_Bank.removeCard(CardType::COMMUNITYCHEST);
        checkForDoubleThrows(DoubleThrows);
    }
    emit updatePlayerBalance();
}

void GameRules::cChestAdvancement(int DoubleThrows, Advancement * AdvanceTo, int position)
{
    QString goTo = AdvanceTo->getAdvancement();

    if (goTo == "Start"){
        moveToken(0 - position, DoubleThrows);
        m_Bank.passedStartMoney(m_CurrentPlayer);
        checkForDoubleThrows(DoubleThrows);
    }

    else if (goTo == "Jail"){
        moveToken(10 - position, DoubleThrows);
        m_CurrentPlayer->playerInJail(true);
    }
}

void GameRules::cChestPayment (std::vector<Player> * AllPlayers, int DoubleThrows, int CardNumber, Payment * payment)
{
    //Pay for each hotel 115 and for each house 40
    if (CardNumber == 13){
        QList<QPair<Street *, int>> PlayerStreets = m_Bank.getPlayerStreets(m_CurrentPlayer->getFigure());

        for (auto index : PlayerStreets){
            Street * currentStreet = index.first;
            m_CurrentPlayer->moneyTransaction(payment->getPayment().at(0) * currentStreet->getHousesAndHotels().first, payment->getTypeOfPayment());
            m_CurrentPlayer->moneyTransaction(payment->getPayment().at(1) * currentStreet->getHousesAndHotels().second, payment->getTypeOfPayment());
        }
    }
    //Collect 10 M from each player
    else if (CardNumber == 8){

        for (auto i : *AllPlayers){
            if (m_CurrentPlayer->getFigure() != i.getFigure()){
                m_CurrentPlayer->moneyTransaction(payment->getPayment().at(0), payment->getTypeOfPayment());
                i.moneyTransaction(payment->getPayment().at(0), TransactionType::Pay);
            }
        }
    }
    else
        m_CurrentPlayer->moneyTransaction(payment->getPayment().at(0), payment->getTypeOfPayment());
    checkForDoubleThrows(DoubleThrows);
}

std::tuple<QList<Street *>, QList<Station*>,QList<Company*>> GameRules::searchBelongings(const Figure Player)
{
    return m_Bank.searchBelongings(Player);
}

QList<QPair<Street *, int>> GameRules::getPlayerStreets(){
    return m_Bank.getPlayerStreets(m_CurrentPlayer->getFigure());
}

QList<QPair<Company *, int>> GameRules::getPlayerCompanies(){
    return m_Bank.getPlayerCompanies(m_CurrentPlayer->getFigure());
}

QList<QPair<Station *, int>> GameRules::getPlayerStations(){
    return m_Bank.getPlayerStations(m_CurrentPlayer->getFigure());
}

QList<QPair<Tile *, int> > GameRules::getInhertedProperties()
{
    return m_Bank.getInheritedProperties();
}

int GameRules::getPlayerPosition(const Figure &Player)
{
    return m_Bank.getPlayerPos(Player);
}


void GameRules::mortgage(const int &TileNumber, const bool &What, const bool &Inherted)
{
    Tile * PropertyType = m_Bank.getProperty(TileNumber);
    bool Permission;

    if (Inherted){
        Permission = true;
    }
    else if (Street * street = dynamic_cast<Street *>(PropertyType)){
        Permission = mortgageStreetRules(TileNumber);
    }
    else
        Permission = true;

    if (Permission){
        mortgageAction(TileNumber, What, Inherted);
    }
}

