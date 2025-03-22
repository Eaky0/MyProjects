//Author: Ieracitano Alessio, Kumas Atakan
//---------------------
//Methods made by Atakan:
//checkTax, getPlayerStreets, payOrTakeMortgage, checkMortgageState, searchBelongings,
//getPlayerStreets, getPlayerCompanies, getPlayerStations, checkTax, checkCard, getCardType
//getCard, getCardAction, getProperty
//---------------------
//Methods made by Alessio:
//getCosts, isCompanyTile, getAmountStreetBuildings,
//getAuctionItem, hasAutionItem, buyHouseHotel, sellHouseHotel, ownsFullColorSet, ownsAnFullColorSet,
//passedStartMoney, buyProperty, payRent, pay, auctionProperty, setAuctionItem, hasHighestBidder, hasDebt, colorSetHasTheSameAmountHouses,
//getInhertedProperties, propertyBuyable, propertyHasOwner, ownsAnFullColor, removeCard, returnCardToDeck, getPlayerPos, getDebtToPlayer,
//moneyPayAndOwe, giveUpMortgageProperties, removeFromInhertedList
//--Signals:
//highestBid, inhertedMortgages, debtToPay
//---------------------
#ifndef BANK_H
#define BANK_H

#include "board.h"
#include "player.h"

class Bank : public QObject
{
    Q_OBJECT
signals:
    void highestBid(int amount, Player* HighestBidder);
    void inheritedMortgages();
    void debtToPay(int Amount, Figure DebtTo);
public:
    //constructor:
    Bank(int AmountPlayers = 2);

    //Method:
    //Returns the Amount the current player need to pay
    int getCosts(const Figure &CurrentPlayer);

    //Method:
    //Returns the amount of buildings the Bank has left to sell
    QPair<int, int> getAmountBankBuildings();

    //Method:
    //PARAM: the tile index
    //Return true if the tile is an company tile
    bool isCompanyTile(const int &PosToken);

    //Method:
    //PRE: TileNumber points to an Street
    //Returns the amount of buildings the street has as an QPair.
    QPair<int, int> getAmountStreetBuildings(const int &TileNumber);

    //Method:
    //Return the first item in the auction list
    int getAuctionItem();

    //Method:
    //Returns true if there are items in the auction list
    bool hasAuctionItem();

    //Method:
    //an hotel or house get's placed on the TileNumber, the player pays the corresponding price
    void buyHouseHotel(const int &TileNumber, Player* Player, const bool &House);

    //Mehtod:
    //Sells an hotel or house for half the price it was bought (to the bank)
    void sellHouseHotel(const int &TileNumber, Player* Player, const bool &House);

    //Method:
    //Take out/pays or keeps an Mortgage depending on the situation
    //Player will pay/recieve the corresponding price depending ont the situation.
    void payOrTakeMortgage(int TileNumber, Player *CurrentPlayer, const bool &TakeOut, const bool &Inherted);

    //Method:
    //Returns true if the tile is mortgaged.
    bool checkMortgageState(int TileNumber);

    //Method:
    //Returns true if the player owns an entire collorset
    bool ownsFullColorSet(const int &TileNumber, const Figure &Player);

    //Method:
    //Returns true if the color set which the player owns doesn't have buildings on them.
    bool colorSetHasNoBuilding(const int &TileNumber);

    //Method:
    //PRE: Player should have passed or on Start
    //Increases the player Balance by 200
    void passedStartMoney(Player* Player);

    //Method:
    //Current player pays the corresponding price of the Tile
    void buyProperty(Player* CurrentPlayer);

    //Method:
    //Player pays the owner of the property the corresponding rent
    void payRent(Player* CurrentPlayer, Player* PlayerOwningProperty);

    //Method:
    //PRE: Tile is an company tile
    //Player pays the owner of the porperty the corresponding rent
    void payRent(Player* CurrentPlayer, Player* PlayerOwningProperty, const int DiceRollAmount);

    //Method:
    //Player pays the corresponding price (bail/tax)
    void pay(Player * currentPlayer);

    //Method:
    //Keeps track who is the higehst bidder, and if it is the last bid the highestbidder pays
    //the corresponding Highest bid, and will be set as the owner of the auctioned tile.
    void auctionProperty(Player* CurrentBidder, const int &BidAmount, const bool &LastBid);

    //Method:
    //Sets the all the properties of the player as the auction item
    //PRE: player went bankrupt
    //PARAM: an player address
    void setAuctionItem(Player* WentBankrupt);

    //Method:
    //Sets the given tile as the auction item
    //PRE: player can't or doen't want to buy the tile
    //PARAM: an Tile index
    void setAuctionItem(const int &TileToAuction);

    //Method:
    //Returns true if there is an highestBidder
    bool hasHighestBidder();

    //Method:
    //Returns true if the player has debt;
    bool hasDebt();

    //Method:
    //Moves the figure to the Corresoponding tile number
    void moveToken(const Figure CurrentPlayer, const int TileNumber);

    //Method:
    //Retuns the amount of houses the bank has
    int getAmountHouses();

    //Method:
    //Checks if the other tiles (of the same color) has an lesser amount of houses
    //Returns true if an house is allowed to be placed on the Street
    bool colorSetHasSameAmountHouses(const int &TileNumber);

    //Returns all the belonging of an player
    std::tuple<QList<Street *>, QList<Station*>,QList<Company*>> searchBelongings(const Figure Player);

    //Methods:
    //Returns the streets togheter with it's index
    QList<QPair<Street *, int>> getPlayerStreets(const Figure Player);

    //Methods:
    //Returns the companies togheter with it's index
    QList<QPair<Company *, int>> getPlayerCompanies(const Figure Player);

    //Methods:
    //Returns the station togheter with it's index
    QList<QPair<Station *, int>> getPlayerStations(const Figure Player);

    //Method:
    //PRE: member m_Inherited has to be filled
    //Returns the inherited (mortgaged) properties
    QList<QPair<Tile*, int>> getInheritedProperties();

    //Method:
    //PARAM: the tileNumber
    //returns if the tile is buyable
    bool propertyBuyable(const int &posToken);

    //Method:
    //Returns if the property has an owner (where the current player is on)
    bool propertyHasOwner(const Figure CurrentPlayer);

    //Method:
    //Returns an boolean (true) if the player owns an full color set
    bool ownsAnFullColor(const Figure &Player);

    //Method:
    //Returns true if the tileNumber is an tax tile
    bool checkTax(const int postoken);

    //Method:
    //Returns true if the tile number says to draw an card
    bool checkCard(const int postoken);

    //Mehtod:
    //Returns the cardType the currentplayer need to drawn form
    CardType getCardType(Player* currentPlayer);

    //Mehtod:
    //PARAM: The card type (which deck)
    //Returns the address of the card from the corresponding card type
    Card *getCard(const CardType &CardToPull);

    //Mehtod:
    //PARAM: The card type (which deck)
    //Returns the address of the pulled card.
    Card * getCardAction(CardType CardToPull);

    //Mehtod:
    //PRE: An get out of jail card has been drawn
    //PARAM: the type of card
    //Removes an card from the corresponding deck of cards
    //POST: get out of jail card has been removed from the corresponding deck
    void removeCard(const CardType Type);

    //Mehtod:
    //PRE: needs to be "get out of jail" card
    //PARAM: address of an card
    //POST: Cards is back in the deck that was lacking an card
    void returnCardToDeck(Card* ReturnCard);

    //Method:
    //PARAM: Figure of an player
    //Returns the player posistion (Tile number on which the token is on)
    int getPlayerPos(const Figure &Player);

    //Method:
    //PARAM: integer of the tile index
    //Returns the Figure of the property owner on which the currentplayer is on
    Figure getPropertyOwner(const int &TileNumber);

    //Method:
    //Player will pay his debt, according to the rules
    //PARAM: the player that need to pay of his debt
    //Returns true if the debt has been paid off, else false
    bool payOffDebt(Player* PlayerToPay);

    //Method:
    //If the player can't pay off the debt, we will need to give away his mortgaged properties
    //And his get out of jail free cards.
    void cantPayDebt(Player * InDebt);

    //Method:
    //Returns the a Tile address
    Tile  *getProperty(const int &TileNumber);

    //Method:
    //Returns the player, who the current player owes debt to.
    //Incase the player owes the bank an null pointer will be returned
    Player *getDebtToPlayer();

    //Method:
    //Returns the address of the board
    Board *getBoard();
private:
    //Method:
    //If the payer can't pay the amount, the m_DebtTo will be filled.
    //and an emit will occur that will force the current player to pay his debt.
    //PARAM: the cost the player needs to pay, and the player his balance
    //IN-OUT PARAM: Cost the player needs to pay, will be adjusted to the amount he can pay
    void moneyPayAndOwe(int *Costs, const int Balance, Player* Owner);

    //Method:
    //If the player owes money to an Player, all (mortgage) properties will be given to that player
    //else the mortgage will be removed from the properties
    void giveUpMortgageProperties(const Figure PlayerInDebt, const Figure PlayerToPay);

    //Method:
    //PARAM: Player that owes, and an address or nullptr of the other person
    //All cards of the player will be given to the player that he owed money to.
    //Incase he owes money to the bank, the cards will be returned to the deck.
    void giveUpCards(Player *GiveUp, Player *ToGet);

    //Method:
    //Removes the Tile from the inehrted list, that corresponds with it's tile index
    void removeFromInhertedList(const int &TileNumber);

    //Members:
    Board m_Board;
    int m_Houses;
    int m_Hotels;
    //Auction:
    Player* m_HighestBidder {nullptr};
    int m_HighestAmount {10};
    QList<int>  m_AuctionItems;
    //Debt:
    QList<QPair<Tile*,int>> m_InheritedItems;
    QPair<Player*, int> m_DebtTo;
};

#endif // BANK_H
