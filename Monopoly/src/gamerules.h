//Author: Ieracitano Alessio, Kumas Atakan
//--------------------------------
//Methods made by Alessio:
//PlayerOptions, checkForDoubleThrows, pay, payRent, buyPropertyRule, isCompanyTile, decideWinner,
//jailCardRule, moveToken, passBid, setCurrentPlayer, getBank, tileCheck, passedStartRule, goToJail, PrisonRules
//playerWentBankrupt, playerOption, checkForDoubleThrows, getInhertedProperties.
//-------------------------------
//Methods made by Atakan:
//searchBelongings, cardPerformingRule, playChangeCard, playCChestCard, getBoard, getPalyerStreets,
//getPlayerStations, getPlayerCompanies, mortgage, chanceAdvancement, chancePayment, playChanceCard, playCChestCard,
//cChestAdvancemnt, cChestPayment, mortgageStreetRules, mortgageAction
//-------------------------------
#ifndef GAMERULES_H
#define GAMERULES_H

#include "bank.h"

class GameRules : public QObject
{
    Q_OBJECT
signals:
    void showBuyProperty(const int &Price);
    void updatePlayerBalance();
    void UpdateBuildingTable();

    void showAuctionWindow();
    void startAuction(const int &AuctionTile);
    void endAuction();
    void showPropertyOptions();
    void ErrorReason(QString Window, QString Reason);

    void showDice();
    void showEndTurn();

    void showCaseWinner(int &Player);
    void showRent(const bool &Company);
    void showTax();

    void showPullCard(CardType &Type, Card &Action);
    void hideBail_JailCard();
    void JailOptions(bool AllowedToThrowDice, bool JailCardObtained);
public:
    GameRules(int AmountPlayers = 2);

    //Method:
    //Returns true if the given tile index is an company
    bool isCompanyTile(const int &PosToken);

    //method:
    //PRE: one or none players are left
    //Decides the Winner of the game
    void decideWinner(std::vector<Player> Players);

    //Method:
    //We auction the player his belongings.
    void playerWentBankrupt(Player *Player);

    //Method:
    //GameRules will check which buttons should be displayed for an player
    //at the start of his turn/round.
    void playerOptions();

    //Method:
    //Will check if player is allowed to move again, incease he has thrown an doublethrow,
    //Else he will get to see the end turn button.
    void checkForDoubleThrows(const int &AmountDoubleThrows);

    //Method: Looks for all belongings of a player
    //PRE: Someone wants to Save the game
    //POST: All Belongings will be stored in a Save File.
    std::tuple<QList<Street *>, QList<Station*>,QList<Company*>> searchBelongings(const Figure Player);

    //Method: Looks for all streets of a Player
    //PRE: A Player has to decide to purchase buildings
    //Post: Player might add a building to one of its streets.
    QList<QPair<Street *, int>> getPlayerStreets();
    QList<QPair<Company *, int>> getPlayerCompanies();
    QList<QPair<Station *, int>> getPlayerStations();
    QList<QPair<Tile*, int>> getInhertedProperties();

    //Method:
    //Returns the player position on the board
    int getPlayerPosition(const Figure &Player);

    //Method:
    //if buy is true, the player will be set as the owner of the property
    //and the price will get deducted of the player his balance
    //else an auction will start.
    bool buyPropertyRule(const bool &buy);

    //Method:
    //Player get's checked if he is allowed to place an house on the Tile (street)
    //If it is allowed the player balance will decrease and an house will be placed on the tile.
    //PRE: Player owns an color set
    void buyHouseHotelRule(const int &TileNumber, const bool &House);

    //Method:
    //This method will check if the player is allowed to sell, in case he is
    //the player will recieve the corresponding price, and an house or hotel will be sold
    void sellHouseHotelRule(const int &TileNumber, const bool &sellHouse);

    //Method:
    //A street owned by a Player will be Mortgaged.
    //PRE: Players owns an color set and decides to take out a mortgage.
    void mortgage(const int &TileNumber, const bool &What, const bool &Inherted);

    //Method:
    //The current player pays the owner the corressponding rent
    //It returns true if the payment succeeded.
    bool payRent(Player *Owner);
    bool payRent(Player *Owner, const int DiceRollAmount);  //Incase the tile is an Company

    //Method:
    //The current player pays the bail or tax price (depending on which tile he is on)
    //It returns true if the payment succeeded.
    bool pay();

    //Method:
    //the player pays the rest of the debt he is owed, if he can't pay
    //he will go bankrupt, and his propterties will get auctioned.
    //Returns true if the pay succeeded, false if the player goes bankrupt
    bool  payDebt();

    //Method:
    //PRE: Player has an "Get Out Of Jail Card"
    //Player status of being in jail will be reset, and the card is returned to the deck.
    void jailCardRule();

    //Method:
    //Player plays the card that he has drawn.
    void cardPerformingRule(std::vector<Player> * AllPlayers, const int &DoubleThrows);

    //Method:
    //The function will check if the player has to be sent to the Prison
    //The player will move the token the corresponding amount of spaces
    void moveToken(const int &TotalAmountJumps, const int &AmountDoubleThrows);

    //Method:
    //Bid of the player will be passed to the bank. If it is the last bid, it will end the auction in the view
    void passBid(Player *CurrentBidder, const int &Amount, const bool &LastBid);

    //Method:
    //Returns true if there is an highestBidder
    bool hasHighestBidder();

    //Method:
    //Returns the owner of the Tile where the current is on.
    Figure getPropertyOwner(const int &TileNumber);

    //Method:
    //Returns if the Tile the current player is on has an owner.
    bool propertyHasOwner(const Figure &PlayerFigure);

    //Method: setCurrentPlayer
    //Sets the m_CurrentPlayer to point to the currentPlayer
    void setCurrentPlayer(Player* CurrentPlayer);

    //Functions for the views
    Board *getBoard();
    Bank *getBank();
private:
    //Method:
    //PARAM IN-OUT: boolean of ToAuction, boolean about the maximum building, bool placementrule
    //PARAM IN: The tilenumber on which the rule should be applied, and buy hous boolean (that is true if an house
    //          is being bought, incase of an hotel false)
    //We Check which rules aply (depending on the situation) and fill in the bool values corresponding to it
    void applyHouseHotelRules(const int &TileNumber, bool *ToAuction, bool *MaxBuildings, bool *PlacementRule, const bool &BuyHouse);

    //Method:
    //PRE: player stands on an Chance Tile
    //Does the corresponding activtity as the drawn card
    void playChanceCard(std::vector<Player> * AllPlayers, int DoubleThrows);
    void chanceAdvancement(int DoubleThrows, Advancement * AdvanceTo, int position);
    void chancePayment (std::vector<Player> * AllPlayers, int DoubleThrows, int CardNumber, Payment * payment);

    //Method:
    //PRE: player stands on an CommunictyChest Tile
    //Does the corresponding activtity as the drawn card
    void playCChestCard(std::vector<Player> * AllPlayers, int DoubleThrows);
    void cChestAdvancement(int DoubleThrows, Advancement * AdvanceTo, int position);
    void cChestPayment (std::vector<Player> * AllPlayers, int DoubleThrows, int CardNumber, Payment * payment);

    //Method:
    //This will check what options (buttons) should be presented to the player
    void tileCheck(const int &posToken, const Figure &PlayerFigure);

    //Method:
    //Will set the player jails status to true, and relocates the player figure to Prison.
    void goToJail();

    //Method:
    //PRE: The tile number is an street
    //PARAM: the tile number on which an mortgage should be placed
    //Returns true if an mortgage is allowed to be placed.
    bool mortgageStreetRules(const int TileNumber);

    //Method:
    //PARAM: Tile number, an boolean that is true if it is an takeout, and an boolean if it is about
    //       inherted mortgage properties.
    //This method will do the corresponding action, sell or take/keep an mortgage depening on the param.
    void mortgageAction(const int TileNumber, const bool &What, const bool &Inherted);

    //Method:
    //Prison rules will be checked for the player, if the player has thrown an double he is realised of jail.
    //If he has thrown an thriple double throw, player will be sent to jail.
    void prisonRules(const bool &IsDoubleThrow, bool &InJail, const bool &IsTripleDoubleThrow);

    //Method:
    //Returns true if the amount of debt an player has by another person is zero.
    bool paymentSucceeded();

    Player* m_CurrentPlayer{nullptr};
    Bank m_Bank;
};

#endif // GAMERULES_H
