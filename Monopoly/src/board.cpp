#include "board.h"
#include "action.h"

Board::Board(const int AmountPlayers, QObject *parent)
    : QObject{parent}, m_AmountPlayers(AmountPlayers)
{

    QFile TileInfo(QStringLiteral(":/Json_files/tiles.json"));

    if (!TileInfo.open(QIODevice::ReadOnly)){
        qDebug() << "JSON file not accesible :(";
        return;
    }

    initializeTiles(&TileInfo);
    //Initializes all chance and community cards
    InitChance();
    InitCommunityChest();
}

QPair<int, int> Board::getAmountHousesHotels(const int &TileNumber)
{
    Street *Street = dynamic_cast<class Street *> (m_Board[TileNumber].get());
    std::pair<int, int> AmountHousesHotels = Street->getHousesAndHotels();
    return AmountHousesHotels;
}

bool Board::isCompanyTile(const int &PosToken)
{
    if (Company *Company = dynamic_cast<class Company *> (m_Board[PosToken].get()))
        return true;
    return false;
}

void Board::placeOrRemoveHouseHotel(const int &TileNumber, const bool &House, const bool &Place)
{
    Street *Street = dynamic_cast<class Street *> (m_Board[TileNumber].get());
    Street->placeOrRemoveHouseHotel(House, Place);
}

void Board::initializeTiles(QFile *TileInfo)
{
    QByteArray TileData = TileInfo->readAll();
    QJsonDocument TileDocument = QJsonDocument::fromJson(TileData);
    QJsonObject TileObject = TileDocument.object();
    QJsonValue JsonTile;

    for (int index = 0; index < M_BOARDSIZE; ++index){
        JsonTile = TileObject[QString::number(index)];
        //Action Tiles
        if (index == 0 || index == 2 || index == 17 || index == 33 || index == 4 || index == 38 ||
            index == 7 || index == 22 || index == 36 || index == 30 || index == 20){

            m_Board[index] = std::unique_ptr<Tile>(new Action{JsonTile});
        }

        //JAIL or FREE PARKING tile (default tiles)
        else if (index == 10){
            m_Board[index] = std::unique_ptr<Tile>(new Tile{false});
        }

        //Station tiles
        else if (index == 5 || index == 15 || index == 25 || index == 35){
            m_Board[index] = std::unique_ptr<Tile>(new Station{JsonTile});
        }

        //Company Tiles
        else if (index == 12 || index == 28){
            m_Board[index] = std::unique_ptr<Tile>(new Company{JsonTile});
        }
        //Street tiles
        else{
            m_Board[index] = std::unique_ptr<Tile>(new Street{JsonTile});
        }
    }
}

void Board::InitChance(){
    QFile ChanceInfo(QStringLiteral(":/Json_files/Chance.json"));

    if (!ChanceInfo.open(QIODevice::ReadOnly)){
        qDebug() << "JSON file not accesible :(";
        return;
    }


    QByteArray ChanceData = ChanceInfo.readAll();
    QJsonDocument ChanceDocument = QJsonDocument::fromJson(ChanceData);
    QJsonObject ChanceObject = ChanceDocument.object();

    QJsonValue JsonChanceCard;

    for (int index = 0; index < M_CARDSETSIZE; ++index){
        JsonChanceCard = ChanceObject[QString::number(index)];
        if (index < 6 || index == 9 || index == 12 || index == 15)
            m_ChanceCards.push_back(new Advancement{JsonChanceCard, CardType::CHANCE, index});

        else if (index == 8 || index == 7){
            m_ChanceCards.push_back(new Card{JsonChanceCard, CardType::CHANCE, index});

        }
        else{
            m_ChanceCards.push_back(new Payment{JsonChanceCard, CardType::CHANCE, index});
        }


    }

    unsigned time = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(m_ChanceCards), std::end(m_ChanceCards), std::default_random_engine(time));
}

void Board::InitCommunityChest(){
    QFile CChestInfo(QStringLiteral(":/Json_files/CommunityChest.json"));

    if (!CChestInfo.open(QIODevice::ReadOnly)){
        qDebug() << "JSON file not accesible :(";
        return;
    }

    QByteArray CChestData = CChestInfo.readAll();
    QJsonDocument CChestDocument = QJsonDocument::fromJson(CChestData);
    QJsonObject CChestObject = CChestDocument.object();

    QJsonValue JsonCChestCard;

    for (int index = 0; index < M_CARDSETSIZE; ++index){
        JsonCChestCard = CChestObject[QString::number(index)];

        if (index == 0 || index == 5){
            m_CChestCards.push_back(new Advancement{JsonCChestCard, CardType::COMMUNITYCHEST, index});
        }
        else if (index == 4){
            m_CChestCards.push_back(new Card{JsonCChestCard, CardType::COMMUNITYCHEST, index});


        }
        else{
            m_CChestCards.push_back(new Payment{JsonCChestCard, CardType::COMMUNITYCHEST, index});

        }

    }

    unsigned time = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(std::begin(m_CChestCards), std::end(m_CChestCards), std::default_random_engine(time));

}

int Board::getPriceRentTax(const Figure &Player)
{
    int PlayerNumber = getPlayerNumber(Player);
    int TileNumber = Coordinates[PlayerNumber].second;
    bool IsTaxTile = checkTax(TileNumber);

    if (IsTaxTile){
        Tile* TaxTile = m_Board[TileNumber].get();
        return TaxTile->getPrice();
    }
    else if (Street *Street = dynamic_cast<class Street *> (m_Board[TileNumber].get()) ){
        Street::Color Color = Street->getColor();
        Figure StreetOwner = Street->getOwner();
        bool OwnsColorSet = false;

        if (StreetOwner != Figure::NONE){       //Incase it has an owner we need to check if he owns the hole set of the color
            std::vector<Street::Color> ColorsOwned = ownedColorSets(StreetOwner);
            OwnsColorSet = std::find(ColorsOwned.begin(), ColorsOwned.end(), Color) != ColorsOwned.end();
        }

        return Street->getPriceOrRent(OwnsColorSet);
    }

    else if (Station *Station = dynamic_cast<class Station *> (m_Board[TileNumber].get())){
        int AmountStationsOwned = 0;

        if (Station->hasOwner()){   //If it has an owner we need to get the amount of stations he owns to get the corresponding rent.
            const Figure Owner = m_Board[TileNumber]->getOwner();
            AmountStationsOwned = getAmountStationOwned(Owner);
        }

        return Station->getRentOrPrice(AmountStationsOwned);
    }
    //If it is an Company we will only retrieve the price, we use an different function to get the rent
    //of an company tile
    else if (Company *Company = dynamic_cast<class Company *> (m_Board[TileNumber].get())){
        return Company->getPrice();
    }
    else{   //If it nothing of the above it will be the prison cost (bail)
        const int BAILCOST = 50;
        return BAILCOST;
    }
}

int Board::getUtilityRent(const Figure &CurrentPlayer, const int &DiceRollAmount)
{
    //First we get the player his position on the board, and the owner of the tile he is on
    const int PlayerPosition = getPlayerPos(CurrentPlayer);
    const Figure Owner = getPropertyOwner(PlayerPosition);

    //The we get the amount of companies the owner owns
    const int AmountCompaniesOwned = getAmountCompaniesOwned(Owner);

    //Together with this information we get the rent that needs to be paid
    Company *Company = static_cast<class Company *> (m_Board[PlayerPosition].get());
    const int Rent = Company->getRent(AmountCompaniesOwned, DiceRollAmount);
    return  Rent;
}


int Board::getPropertyValue(const int &TileNumber)
{
    Tile* Tile = m_Board[TileNumber].get();

    if (Tile == nullptr)
        return 0;

    if (Street *Street = dynamic_cast<class Street *>(Tile))
        return Street->getValue();

    else
        return Tile->getPrice();
}

int Board::getBuildingCosts(const int &TileNumber)
{
    Street *Street = static_cast<class Street *>( m_Board[TileNumber].get());
    return Street->getBuildingCost();
}

int Board::getMortgageCosts(const int &TileNumber, bool What)
{
    return m_Board[TileNumber].get()->getMortgageValue(What);
}


void Board::setPropertyMortgageState(const int &TileNumber, const bool What)
{
    if (What){
        m_Board[TileNumber].get()->mortgage(What);
    }
    else{
        m_Board[TileNumber].get()->mortgage(What);
    }
}

QList<QPair<Tile *, int>> Board::getMorgageProperties(const Figure &Player)
{
    QList<QPair<Tile *, int>> Properties;

    for (int i = 0; i < M_BOARDSIZE; ++i){
        Tile* Property = m_Board[i].get();

        bool PlayerIsOwner = (Property->getOwner() == Player);
        bool IsMortgaged =  Property->isMortgaged();
        if (PlayerIsOwner && IsMortgaged)
            Properties.append({Property, i});
    }

    return Properties;
}

bool Board::checkMortgageState(int TileNumber)
{
   return m_Board[TileNumber].get()->isMortgaged();
}


void Board::setPropertyOwner(const int &TileNumber, const Figure &Player)
{
    Tile* Property = m_Board[TileNumber].get();
    Property->setOwner(Player);
}

void Board::resetOwner(const int &TileNumber)
{
    m_Board[TileNumber]->removeOwner();
}

QList<int> Board::getProperties(const Figure &Player)
{
    QList<int> Properties;
    for (int i = 0; i < M_BOARDSIZE; ++i){

        Tile* Property = m_Board[i].get();
        bool PlayerIsOwner = (Property->getOwner() == Player);
        if (PlayerIsOwner)
            Properties.append(i);
    }

    return Properties;
}

Figure Board::getPropertyOwner(const int &TileNumber)
{
    return m_Board[TileNumber]->getOwner();
}



Tile  * Board::getProperty(const int &TileNumber)
{
    return m_Board[TileNumber].get();
}

int Board::getPlayerNumber(const Figure &Player)
{
    int Number = 0;
    for (int i = 0; i < m_AmountPlayers; ++i){
        Figure PlayerToken = Coordinates[i].first;

        if (Player == PlayerToken){
            Number = i;
            break;
        }
    }
    return Number;
}


int Board::getAmountStationOwned(const Figure &Player)
{
    int Amount = 0;

    for (auto &i : m_Board){
        //if the tile is an station and it is owned by the player we increase the amount
        if (Station *Station = dynamic_cast<class Station *>(i.get())){
            if (Station->getOwner() == Player)
                ++Amount;
        }
    }

    return Amount;
}


int Board::getAmountCompaniesOwned(const Figure &Player)
{
    int AmountOwned = 0;

    for (auto &i : m_Board){
        //if the tile is an company and it is owned by the player we increase the amount
        if (Company *Company = dynamic_cast<class Company *>(i.get())){
            if (Company->getOwner() == Player)
                ++AmountOwned;
        }
    }

    return AmountOwned;
}



std::vector<Street::Color> Board::ownedColorSets(const Figure &Player)
{
    Street::Color StreetColor = Street::Color::BROWN;
    std::vector<Street::Color> ColorsOwned;
    int AmountOfColorOwned = 0;
    int AmountColor = 0;

    for (auto &i : m_Board){
        if (Street *street = dynamic_cast<Street *>(i.get())){
            //First we check if the Color is still the same
            if (StreetColor != street->getColor()){

                if (AmountColor == AmountOfColorOwned){
                    ColorsOwned.push_back(StreetColor);
                }

                StreetColor = street->getColor();
                AmountOfColorOwned = 0;
                AmountColor = 1;
            }
            else
                ++AmountColor;

            //if the owner is the same
            if (i.get()->getOwner() == Player)
                ++AmountOfColorOwned;
        }
    }

    return ColorsOwned;
}


int Board::getPlayerPos(const Figure &Player)
{
    const int PlayerNumber = getPlayerNumber(Player);
    const int Posistion = Coordinates[PlayerNumber].second;
    return Posistion;
}

void Board::moveToken(const Figure &CurrentPlayer, const int &NewPosition)
{
    const int PlayerNumber = getPlayerNumber(CurrentPlayer);
    const int OldPos = Coordinates[PlayerNumber].second;

    Figure* PlayerToken = &Coordinates[PlayerNumber].first;
    Tile * oldTile = m_Board[OldPos].get();
    oldTile->removeToken(PlayerToken);

    Coordinates[PlayerNumber].second = NewPosition;
    Tile * newTile = m_Board[NewPosition].get();
    newTile->addToken(PlayerToken);

    emit TokenWillMove(PlayerNumber, OldPos, NewPosition);
}

bool Board::propertyHasOwner(const Figure &Player)
{
    int PlayerNumber = getPlayerNumber(Player);
    int PlayerPos = Coordinates[PlayerNumber].second;
    Tile * CheckTile = m_Board[PlayerPos].get();
    return CheckTile->hasOwner();
}

bool Board::isBuyable(const int &posToken)
{
    bool IsBuyable = m_Board[posToken]->isBuyable();
    return IsBuyable;
}

bool Board::checkTax(const int &postoken)
{
    if (Action * i = dynamic_cast<Action*>(m_Board[postoken].get())){
        bool IsIncomeTax = (i->getActionType() == Action::ActionType::INCOMETAX);
        bool IsSuperTax = (i->getActionType() == Action::ActionType::SUPERTAX);

        if (IsIncomeTax || IsSuperTax)
            return true;
    }

    return false;
}

bool Board::checkCard(const int &postoken){
    if (Action * i = dynamic_cast<Action*>(m_Board[postoken].get())){
        bool IsChanceCard = (i->getActionType() == Action::ActionType::CHANCE);
        bool IsCChestCard = (i->getActionType() == Action::ActionType::COMMUNITYCHEST);

        if (IsChanceCard || IsCChestCard)
            return true;
    }
    return false;
}

CardType Board::getCardType (const Figure &Player)
{
    int postoken;

    for (auto index : Coordinates){
        if (index.first == Player){
            postoken = index.second;
            break;
        }
    }

    Action * CardTile = static_cast<Action *>(m_Board[postoken].get());

    if (CardTile->getActionType() == Action::ActionType::CHANCE){
        return CardType::CHANCE;
    }
    else
        return CardType::COMMUNITYCHEST;

}

Card * Board::getCard(const CardType &CardToPull)
{
    Card* TopCard;
    if (CardToPull == CardType::CHANCE)
        TopCard = m_ChanceCards[0];
    else
        TopCard = m_CChestCards[0];

    return TopCard;
}

Card * Board::getCardAction(const CardType &CardToPull)
{
    Card * Task;

    if (CardToPull == CardType::CHANCE){
        Task = m_ChanceCards[0];
        int AmountCards = (int) m_ChanceCards.size();
        Card * temp = m_ChanceCards[0];

        for (int index = 0; index < AmountCards - 1; ++index){
            m_ChanceCards[index] = m_ChanceCards[index + 1];
        }

        m_ChanceCards[AmountCards - 1] = temp;
    }
    else{
        Task = m_CChestCards[0];
        int AmountCards = (int) m_CChestCards.size();
        Card * temp = m_CChestCards[0];

        for (int index = 0; index < AmountCards - 1; ++index){
            m_CChestCards[index] = m_CChestCards[index + 1];
        }

        m_CChestCards[AmountCards - 1] = temp;
    }

    return Task;
}

void Board::removeCardFromDeck(const CardType &Type)
{
    if (Type == CardType::CHANCE){
        m_ChanceCards.pop_back();
    }
    else
        m_CChestCards.pop_back();
}

void Board::returnCardToDeck(Card *ReturnCard)
{
    CardType Type = ReturnCard->TypeOfCard();
    if (Type == CardType::CHANCE){
        m_ChanceCards.push_back(ReturnCard);
    }
    else
        m_CChestCards.push_back(ReturnCard);
}


bool Board::sameAmountHouses(const int &TileNumber)     //To check if the house is allowed to be placed.
{
    Street *SelectedStreet = static_cast<Street *>(m_Board[TileNumber].get());
    Street::Color SelectedColor = SelectedStreet->getColor();
    const int AmountHousesSelected = SelectedStreet->getHousesAndHotels().first;

    for (auto &i : m_Board){
        //First we check if the tile is an street
        if (Street *Street = dynamic_cast<class Street *>(i.get())){

            //If the color isn't the same we go to the next one.
            if (SelectedColor != Street->getColor()){
                continue;
            }

            //If the streets have the same color but an smaller amount of houses, we return false
            else if ((Street->getHousesAndHotels().first < AmountHousesSelected) && Street->getHousesAndHotels().second == 0){
            return false;
            }
        }
    }

    //if nothing is return yet, then we return true.
    return true;
}

bool Board::ownsFullColorset(const int TileNumber, const Figure Player)
{
    std::vector<Tile*> ColorSet;
    Street *SelectedStreet = dynamic_cast<class Street*> (m_Board[TileNumber].get());
    Street::Color StreetColor = SelectedStreet->getColor();

    //First we collect all streets of the same color
    for (int i = 0; i < M_BOARDSIZE; ++i){
        if (Street *Street = dynamic_cast<class Street*> (m_Board[i].get())){
            if (Street->getColor() == StreetColor)
                ColorSet.push_back(m_Board[i].get());
        }
    }

    //Next we check if the player truly owns the entire color set.
    for (int i = 0 ; i < ColorSet.size(); ++i)
        if (ColorSet[i]->getOwner() != Player)
            return false;

    return true;
}


bool Board::colorSetHasNoBuilding(const int &TileNumber)
{
    std::vector<Street*> ColorSet;
    const QPair<int, int> NoBuildings = {0,0};
    Street *SelectedStreet = dynamic_cast<class Street*> (m_Board[TileNumber].get());
    Street::Color StreetColor = SelectedStreet->getColor();

    //First we collect all streets of the same color
    for (int i = 0; i < M_BOARDSIZE; ++i){
        if (Street *street = dynamic_cast<class Street*> (m_Board[i].get())){
            if (street->getColor() == StreetColor)
                ColorSet.push_back(street);
        }
    }

    //Next we check if the color doesn't contain any buildings.
    for (int i = 0 ; i < ColorSet.size(); ++i)
        if (ColorSet[i]->getHousesAndHotels() != NoBuildings)
            return false;

    return true;
}

std::tuple<QList<Street *>, QList<Station*>,QList<Company*>> Board::searchBelongings(const Figure Player)
{
    QList<Street*> Streets;
    QList<Station *> Stations;
    QList<Company *> Companies;

    for (auto &i : m_Board){
        if (Street *street = dynamic_cast<Street *>(i.get())){
            if (i.get()->getOwner() == Player){
                Streets.append(street);
            }
        }

        else if(Station *station = dynamic_cast<Station *>(i.get())){
            if (i.get()->getOwner() == Player){
                Stations.append(station);

            }
        }

        else if (Company *company = dynamic_cast<Company *>(i.get())){
            if (i.get()->getOwner() == Player){
                Companies.append(company);
            }

        }

    }

    std::tuple<QList<Street *>, QList<Station*>,QList<Company*>> Belongings = {Streets, Stations, Companies};
    return Belongings;
}

QList<QPair<Street *, int>> Board::getPlayerStreets(const Figure Player)
{
    QList<QPair<Street *, int>> PlayerStreets;

    for (int index = 0; index < M_BOARDSIZE; ++index){
        if (Street *street = dynamic_cast<Street *>(m_Board[index].get())){
            if (m_Board[index].get()->getOwner() == Player)
                PlayerStreets.append({street, index});
            }
        }

    return PlayerStreets;
}


QList<QPair<Company *, int>> Board::getPlayerCompanies(const Figure Player)
{
    QList<QPair<Company *, int>> PlayerStreets;

    for (int index = 0; index < M_BOARDSIZE; ++index){
        if (Company *company = dynamic_cast<Company *>(m_Board[index].get())){
            if (m_Board[index].get()->getOwner() == Player)
                PlayerStreets.append({company, index});
            }
        }

    return PlayerStreets;
}

QList<QPair<Station *, int>> Board::getPlayerStations(const Figure Player)
{
    QList<QPair<Station *, int>> PlayerStreets;

    for (int index = 0; index < M_BOARDSIZE; ++index){
        if (Station *station = dynamic_cast<Station *>(m_Board[index].get())){
            if (m_Board[index].get()->getOwner() == Player)
                PlayerStreets.append({station, index});
            }
        }

    return PlayerStreets;
}
