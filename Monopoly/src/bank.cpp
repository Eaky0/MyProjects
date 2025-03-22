#include "bank.h"


Bank::Bank(int AmountPlayers) : m_Board{AmountPlayers}, m_Houses{12}, m_Hotels{12} {}

int Bank::getCosts(const Figure &CurrentPlayer)
{
    return m_Board.getPriceRentTax(CurrentPlayer);
}

void Bank::passedStartMoney(Player *Player)
{
    const int STARTMONEY = 200;
    Player->moneyTransaction(STARTMONEY, TransactionType::Recieve);
}

void Bank::buyProperty(Player* CurrentPlayer)
{
    //First we get the cost of the property and let the player pay the amount
    const int costs = m_Board.getPriceRentTax(CurrentPlayer->getFigure());
    CurrentPlayer->moneyTransaction(costs, TransactionType::Pay);

    //Next we get the position of the player, and set the
    int Position = getPlayerPos(CurrentPlayer->getFigure());
    m_Board.setPropertyOwner(Position, CurrentPlayer->getFigure());
}

void Bank::moveToken(const Figure CurrentPlayer, const int Amount)
{
    m_Board.moveToken(CurrentPlayer, Amount);
}

int Bank::getAmountHouses()
{
    return m_Houses;
}

bool Bank::colorSetHasSameAmountHouses(const int &TileNumber)
{
    return m_Board.sameAmountHouses(TileNumber);
}


bool Bank::propertyBuyable(const int &posToken)
{
    return m_Board.isBuyable(posToken);
}

Board *Bank::getBoard()
{
    return &m_Board;
}

void Bank::moneyPayAndOwe(int *Costs, const int Balance, Player* Owner)
{
    const Figure BANK = Figure::NONE;

    //If the player can't pay the amount, he has debt
    if (Balance - (*Costs) < 0){
        int MoneyOwed = (*Costs) - Balance;
        *Costs = Balance;

        m_DebtTo = {Owner, MoneyOwed};
        if (Owner != nullptr)
            emit debtToPay(MoneyOwed, Owner->getFigure());
        else
            emit debtToPay(MoneyOwed, BANK);
    }
}

bool Bank::propertyHasOwner(const Figure CurrentPlayer)
{
    return m_Board.propertyHasOwner(CurrentPlayer);
}

bool Bank::ownsAnFullColor(const Figure &Player)
{
    std::vector<Street::Color> Owned = m_Board.ownedColorSets(Player);
    return (Owned.size() > 0);
}

Figure Bank::getPropertyOwner(const int &newTile)
{
    return m_Board.getPropertyOwner(newTile);
}

bool Bank::payOffDebt(Player *PlayerToPay)
{
    Player* ToPay = m_DebtTo.first;
    int Amount = m_DebtTo.second;
    const int Balance = PlayerToPay->getBalance();

    if (Balance < 0){
        cantPayDebt(PlayerToPay);
        return false;
    }
    else{
        ToPay->moneyTransaction(Amount, TransactionType::Recieve);
        m_DebtTo = {nullptr, 0};
        return true;
    }
}

Tile  * Bank::getProperty(const int &TileNumber)
{
    return m_Board.getProperty(TileNumber);
}

Player *Bank::getDebtToPlayer()
{
    return m_DebtTo.first;
}



void Bank::payRent(Player* CurrentPlayer, Player* PlayerOwningProperty)
{
    const int Cost = m_Board.getPriceRentTax(CurrentPlayer->getFigure());
    const int Balance = CurrentPlayer->getBalance();
    int AmountCanBePayed = Cost;

    moneyPayAndOwe(&AmountCanBePayed, Balance, PlayerOwningProperty);
    PlayerOwningProperty->moneyTransaction(Cost, TransactionType::Recieve);
    CurrentPlayer->moneyTransaction(Cost, TransactionType::Pay);
}

void Bank::payRent(Player *CurrentPlayer, Player *PlayerOwningProperty, const int DiceRollAmount)
{
    const int Cost = m_Board.getUtilityRent(CurrentPlayer->getFigure(), DiceRollAmount);
    int AmountCanBePayed = Cost;
    const int Balance = CurrentPlayer->getBalance();

    moneyPayAndOwe(&AmountCanBePayed, Balance, PlayerOwningProperty);
    PlayerOwningProperty->moneyTransaction(AmountCanBePayed, TransactionType::Recieve);
    CurrentPlayer->moneyTransaction(Cost, TransactionType::Pay);
}

void Bank::pay(Player* CurrentPlayer)
{
    const int Cost = m_Board.getPriceRentTax(CurrentPlayer->getFigure());
    int AmountThatCanBePayed = Cost;
    const int Balance = CurrentPlayer->getBalance();
    bool InJail = (CurrentPlayer->getPlayerStatus());

    moneyPayAndOwe(&AmountThatCanBePayed, Balance, nullptr);
    CurrentPlayer->moneyTransaction(Cost, TransactionType::Pay);

    //If the player is in jail, that means that this is the bail he is paying
    if (InJail)
        CurrentPlayer->playerInJail(false);
}

bool Bank::checkTax(const int postoken)
{
    return m_Board.checkTax(postoken);
}

int Bank::getPlayerPos(const Figure &Player)
{
    return m_Board.getPlayerPos(Player);
}


void Bank::auctionProperty(Player* CurrentBidder, const int &BidAmount, const bool &LastBid)
{
    if (BidAmount > 0){
        m_HighestAmount += BidAmount;
        m_HighestBidder = CurrentBidder;
        emit highestBid(m_HighestAmount, m_HighestBidder);
    }

    if (LastBid && (m_HighestBidder != nullptr)){
        m_Board.setPropertyOwner(m_AuctionItems[0], CurrentBidder->getFigure());
        m_HighestBidder->moneyTransaction(m_HighestAmount, TransactionType::Pay);

        const int BEGINAMOUNT = 10;
        m_HighestBidder = nullptr;
        m_HighestAmount = BEGINAMOUNT;
    }

    if(LastBid)
        m_AuctionItems.pop_front();
}

void Bank::setAuctionItem(const int &TileToAuction)
{
    m_AuctionItems.append(TileToAuction);
}

void Bank::setAuctionItem(Player *WentBankrupt)
{
    QList<int> PropretiesToAuction = m_Board.getProperties(WentBankrupt->getFigure());
    m_AuctionItems = PropretiesToAuction;
}

bool Bank::hasHighestBidder()
{
    return (m_HighestBidder != nullptr);
}

bool Bank::hasDebt()
{
    //To check if an player has debt, we check the amount the player
    //should owe. If 0 than false, if higher than 0 he has debt an thus
    //return true
    return (m_DebtTo.second > 0);
}

Card * Bank::getCardAction(CardType CardToPull)
{
    return m_Board.getCardAction(CardToPull);
}


bool Bank::checkCard(const int postoken)
{
    return m_Board.checkCard(postoken);
}

CardType Bank::getCardType(Player* currentPlayer)
{
    return m_Board.getCardType(currentPlayer->getFigure());
}

//Get's de card at the top of the deck
Card *Bank::getCard(const CardType &CardToPull)
{
    return m_Board.getCard(CardToPull);
}

//removes the pulled card from the deck
void Bank::removeCard(const CardType Type)
{
    m_Board.removeCardFromDeck(Type);
}

//Put the card at the bottem of the deck
void Bank::returnCardToDeck(Card *ReturnCard)
{
    m_Board.returnCardToDeck(ReturnCard);
}

std::tuple<QList<Street *>, QList<Station*>,QList<Company*>> Bank::searchBelongings(const Figure Player)
{
    return m_Board.searchBelongings(Player);
}

QPair<int, int> Bank::getAmountBankBuildings()
{
    return {m_Houses, m_Hotels};
}

bool Bank::isCompanyTile(const int &PosToken)
{
    return m_Board.isCompanyTile(PosToken);
}

QPair<int, int> Bank::getAmountStreetBuildings(const int &TileNumber)
{
    return m_Board.getAmountHousesHotels(TileNumber);
}

int Bank::getAuctionItem()
{
    return m_AuctionItems[0];
}

bool Bank::hasAuctionItem()
{
    return m_AuctionItems.size();
}

void Bank::buyHouseHotel(const int &TileNumber, Player* Player, const bool &House)
{
    //First get the build price
    const int PRICE = m_Board.getBuildingCosts(TileNumber);
    const int PLACE = true;
    const int AMOUNT = 1;

    Player->moneyTransaction(PRICE, TransactionType::Pay);
    m_Board.placeOrRemoveHouseHotel(TileNumber, House, PLACE);

    //We remove an bought house or hotel from the bank
    if (House){
        m_Houses -= AMOUNT;
    }
    else{
        m_Houses += 4;
        m_Hotels -= AMOUNT;
    }

}

void Bank::sellHouseHotel(const int &TileNumber, Player *Player, const bool &House)
{
    //If an player decides to sell an house or hotel, he recieves half the value of it.
    const int HALF = 2;
    const int HALFPRICE = m_Board.getBuildingCosts(TileNumber) / HALF;
    const int REMOVE = false;

    Player->moneyTransaction(HALFPRICE, TransactionType::Recieve);
    m_Board.placeOrRemoveHouseHotel(TileNumber, House, REMOVE);

    //We return the sold house or hotel to the bank
    const int AMOUNTHOUSES = 1;
    if (House)
        m_Houses += AMOUNTHOUSES;
    else
        m_Hotels += AMOUNTHOUSES;
}

bool Bank::ownsFullColorSet(const int &TileNumber, const Figure &Player)
{
    return m_Board.ownsFullColorset(TileNumber, Player);
}


bool Bank::colorSetHasNoBuilding(const int &TileNumber)
{
    return m_Board.colorSetHasNoBuilding(TileNumber);
}

void Bank::cantPayDebt(Player * InDebt)
{
    bool OwesAnPlayer = (m_DebtTo.first != nullptr);
    Figure PlayerWithDebt = InDebt->getFigure();
    Figure PlayerToBePaid;

    if (OwesAnPlayer)
        PlayerToBePaid = m_DebtTo.first->getFigure();
    else
        PlayerToBePaid = Figure::NONE;

    giveUpMortgageProperties(PlayerWithDebt, PlayerToBePaid);
    giveUpCards(InDebt, m_DebtTo.first);
}

void Bank::giveUpMortgageProperties(const Figure PlayerInDebt, const Figure PlayerToPay)
{
    QList<QPair<Tile *, int>> ToInheretProperties = m_Board.getMorgageProperties(PlayerInDebt);
    const int ListSize = (int) ToInheretProperties.size();
    bool DebtToAnPlayer = (PlayerToPay != Figure::NONE);

    //Depening on who the player owes we set an diffrent owner
    //Or we remove the mortgage.
    for (int i = 0; i < ListSize; ++i){
        int TileNumber = ToInheretProperties[i].second;
        if (DebtToAnPlayer)
            m_Board.setPropertyOwner(TileNumber, PlayerToPay);
        else
            ToInheretProperties[i].first->mortgage(false);
    }

    //If the player owes money to another player, we fill in InhertedProperties
    if (DebtToAnPlayer){
        m_InheritedItems = ToInheretProperties;
        emit inheritedMortgages();
    }
}

void Bank::giveUpCards(Player *GiveUp, Player *ToGet)
{
    while(GiveUp->hasJailCard()){
        Card * GetOutJail = GiveUp->removeCard();

        if (ToGet != nullptr)   //If the player owes another player
            ToGet->addCard(GetOutJail);

        else        //Else we return his cards to the deck
            m_Board.returnCardToDeck(GetOutJail);
    }
}

void Bank::removeFromInhertedList(const int &TileNumber)
{
    const int ListSize = m_InheritedItems.size();
    QPair<Tile*, int> Temp;
    bool HasBeenFound = false;

    for (int i = 0; i < ListSize; ++i){
        if (m_InheritedItems[i].second == TileNumber){
            Temp = m_InheritedItems[i];
            HasBeenFound = true;
        }
        else if (HasBeenFound){
            m_InheritedItems[i - 1] = m_InheritedItems[i];
        }
    }

    m_InheritedItems.removeLast();
}

QList<QPair<Street *, int>> Bank::getPlayerStreets(const Figure Player)
{
    return m_Board.getPlayerStreets(Player);
}


QList<QPair<Company *, int>> Bank::getPlayerCompanies(const Figure Player)
{
    return m_Board.getPlayerCompanies(Player);
}

QList<QPair<Station *, int>> Bank::getPlayerStations(const Figure Player){
    return m_Board.getPlayerStations(Player);
}

QList<QPair<Tile *, int> > Bank::getInheritedProperties()
{
    return m_InheritedItems;
}

void Bank::payOrTakeMortgage(int TileNumber, Player *CurrentPlayer, const bool &TakeOut, const bool &Inherted)
{
    const int Mortgageamount = m_Board.getMortgageCosts(TileNumber, TakeOut);
    TransactionType Type;
    int Costs = Mortgageamount;

    if (Inherted){      //If it is inherted we need to remove it from the list
        if (TakeOut)    //If the player decides to keep it he has to pay 10% extra
            Costs += (int) (Mortgageamount * 0.1);
        removeFromInhertedList(TileNumber);
    }

    if (TakeOut)       //IF the player takes out an mortgage he recieves money
        Type = TransactionType::Recieve;
    else                //Else he has to pay
        Type = TransactionType::Pay;

    CurrentPlayer->moneyTransaction(Costs, Type);
    m_Board.setPropertyMortgageState(TileNumber, TakeOut);
}

bool Bank::checkMortgageState(int TileNumber)
{
    return m_Board.checkMortgageState(TileNumber);
}
