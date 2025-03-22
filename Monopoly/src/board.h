//Author: Kumas Atakan, Ieraictano Alessio
//--------------------------
//Methods made by Atakan:
//Board, getAmountHousesHotels, isCompanyTile, setPropertyMortgageState, checkMortgageState, getMortgageCosts
//getCardType, checkTax, checkCard, getCardAction, colorSetHasNoBuilding, getPlayerStreets, getPlayerCompanies
//getPlayerStations, searchBelongings, moveToken, InitChance, InitCommunityChest, initializeTiles
//
//-------------------------
//Methods made by Alessio:
//placeOrRemoveHouseHotel, getMorgageProperties, getPriceRentTax, getUtilityRent, getPropertyValue, setPropertyOwner
//getMorgageProperties, resetOwner, getBuildingCosts, getProperties, isBuyable, getCard, removeCardFromDeck, returnCardToDeck
//sameAmountHouses, ownedColorSets, ownsFullColorset, getPlayerPos, getPlayerNumber, getAmountStationOwned, getAmountCompaniesOwned
//-------------------------

#ifndef BOARD_H
#define BOARD_H


#include <QObject>
#include <QList>
#include <QPair>
#include <algorithm>
#include <array>
#include <random>
#include <chrono>
#include <tuple>

#include "figure.h"
#include "payment.h"
#include "street.h"
#include "station.h"
#include "company.h"
#include "advancement.h"

class Board : public QObject
{
    Q_OBJECT

signals:
    void TokenWillMove(int PlayerNumber, int prevPos ,int newPos);
public:
    //constructors and deconstructors:
    Board(const int AMOUNTPLAYERS = 2, QObject *parent = nullptr);

    //Mehthod:
    //PRE: TIleNumber needs to point to an Street
    //Returns the amount of houses an Street has
    QPair<int, int> getAmountHousesHotels(const int &TileNumber);

    //Mehtod:
    //PARAM: Number of the tile you want to check
    //Returns True if the tile is an Company tile
    bool isCompanyTile(const int &PosToken);

    //Method:
    //PRE: TileNumber points to an STREET
    //Places/Removes an hotel (House == false) or house (House == true) from an Street
    void placeOrRemoveHouseHotel(const int &TIleNumber, const bool &House, const bool &Place);

    //Method:
    //Makes the property mortgaged, depending on the
    void setPropertyMortgageState(const int &TileNumber, const bool What);

    //Method:
    //Returns an QList of all the morgaged properties of an player
    QList<QPair<Tile *, int>> getMorgageProperties(const Figure &Player);

    //Method:
    //PARAM: The tile index, of the tile you want to check
    //Returns true if their is an mortgage on the tile.
    bool checkMortgageState(int TileNumber);

    //Method:
    //Returns the price/rent/tax of the Tile, depeding on which tile and it's status
    int getPriceRentTax(const Figure &CurrentPlayer);

    //Method:
    //Returns the amount that the player need to pay for the Utitlity
    int getUtilityRent(const Figure &CurrentPlayer, const int &DiceRollAmount);

    //Method:
    //Returns an interger that represents the entire value of an property
    int getPropertyValue(const int &TileNumber);

    //Method:
    //Returns the cost for building an house or hotel
    int getBuildingCosts(const int &TileNumber);

    //Method:
    //Returns the cost for mortgage take out or Pay off depending on the mode.
    int getMortgageCosts(const int &TileNumber, bool What);

    //Method:
    //Sets the Owner of the "Tile" to player
    void setPropertyOwner(const int &Tile, const Figure &Player);

    //Method:
    //PRE: TileNumber points to an Street, Station, Utility.
    //Resets the Owner of the tile to None, and makes it buyable again
    void resetOwner(const int &TileNumber);

    //Method:
    //Returns an QList<int> that is filled with tile indexes that the player owns.
    QList<int> getProperties(const Figure &Player);

    //Method:
    //Returns the property owner on which the given player is on
    Figure getPropertyOwner(const int &TileNumber);

    //Method:
    //Returns the a PropertyTile
    //PRE: Player tends to Pay off or Take out mortgage of a propety.
    //POST: check whether its a street, station or Company whose mortgage has to be payed off or taken out.
    Tile  * getProperty(const int &TileNumber);

    //Method:
    //PRE: player needs to stand on an Community chest or Fonds Tile.
    //Returns the cardType that the player needst to draw from
    CardType getCardType (const Figure &Player);

    //Method:
    //PARAM: the player Figure on which you want to check
    //Returns true if the property has an owner
    bool propertyHasOwner(const Figure &Player);

    //Method:
    //PARAM: The index of the tile you want to check
    //Returns if tile is buyable
    bool isBuyable(const int &posToken);

    //Method:
    //PARAM: The index of the tile you want to check
    //Returns true if the tile is an tax tile.
    bool checkTax(const int &postoken);

    //Method:
    //PARAM: the index of the tile you want to check
    //Returns true if the Tile is an card tile (community chest of fonds)
    bool checkCard(const int &postoken);

    //Method:
    //PARAM: the type of the card you want to pull
    //Returns the top card of the deck
    Card * getCard(const CardType &CardToPull);

    //Method:
    //Takes the top card of the deck, and put's it at the bottom of the deck
    //PARAM: the type of the card you want to pull
    //Returns the top card
    Card * getCardAction(const CardType &CardToPull);

    //Method:
    //PARAM: type of the card to take
    //Card will be removed from the deck
    void removeCardFromDeck(const CardType &Type);

    //Method:
    //this will put the given card back in it's deck
    //PARAM: the address of an card
    void returnCardToDeck(Card *ReturnCard);

    //Method:
    //Checks if the other tiles (of the same color) has an lesser amount of houses
    //Returns true if an house is allowed to be placed on the Street
    bool sameAmountHouses(const int &TileNumber);

    //Method:
    //Returns true if the player owns the full color set that contains the tileNumber.
    bool ownsFullColorset(const int TileNumber, const Figure Player);

    //Method:
    //Returns true if the color set of the tile has no buildings on them.
    bool colorSetHasNoBuilding(const int &TileNumber);

    //Method:
    //Returns the owned streets/stations/companies of the player and their index.
    QList<QPair<Street *, int>> getPlayerStreets(const Figure Player);
    QList<QPair<Company *, int>> getPlayerCompanies(const Figure Player);
    QList<QPair<Station *, int>> getPlayerStations(const Figure Player);

    //Method: Looks for all belongings of a player
    //PRE: Someone wants to Save the game
    //PARAM: an Player figure
    //POST: All Belongings will be stored in a Save File.
    std::tuple<QList<Street *>, QList<Station*>,QList<Company*>> searchBelongings(const Figure Player);

    //Method:
    //Returns the tile where the player is on.
    int getPlayerPos(const Figure &Player);

    //Method:
    //PARAM: Figure and an interger
    //Places the figure of the player on the position (newPosition)
    void moveToken(const Figure &Player, const int &NewPosition);

    //Method:
    //PARAM: Figure of an player
    //Returns the inter colorset that is owned by that player.
    std::vector<Street::Color> ownedColorSets(const Figure &Player);

private:
    //methods:
    //Method:
    //Inisializes the Chance cards
    void InitChance();

    //Method:
    //Inisializes the Community Chest cards
    void InitCommunityChest();

    //Method:
    //Inisializes the Tiles
    void initializeTiles(QFile *TileInfo);

    //Method:
    //Returns the player his index (from Coordinates)
    int getPlayerNumber(const Figure &Player);

    //Method:
    //PARAM: figure of an player
    //Returns the amount of stations owend by the player
    int getAmountStationOwned(const Figure &Player);

    //Method:
    //PARAM: figure of an player
    //Returns the amount of companies owned by the player
    int getAmountCompaniesOwned(const Figure &Player);

    //members:
    int m_AmountPlayers{2};
    const int M_BOARDSIZE{40};
    const int M_CARDSETSIZE{16};

    std::array<std::unique_ptr<Tile>, 40> m_Board;
    std::vector<Card*> m_ChanceCards;
    std::vector<Card*> m_CChestCards;

    std::array<QPair<Figure, int>, 6> Coordinates {{ {Figure::CAR, 0}, {Figure::HAT, 0},        //NEEDS TO BE CHANCED TO AN VECTOR!
                                                   {Figure::WHEELBARROW, 0}, {Figure::BOOT, 0},
                                                   {Figure::SHIP, 0}, {Figure::CANNON, 0} }};
};
#endif // BOARD_H
