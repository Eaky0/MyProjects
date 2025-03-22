//Author: Iercitano Alessio, Kumas Atakan
//--------------------------------
//Methods made by Alessio:
//endTurn, throwDice, getGameRules, getBank, buyProperty, pay, buyOrSellHotel, payRent, payDebt, useJailCard,
//setCurrentBid, bidAucion, getCurrentBidder,getPlayer, checkAmountPasses, resetPassedStatus, bidPass,
//exit, getCurrentPlayer, getPlayerIndex, moveToken, endTurnJailProtocol, selectNextPlayer, checkAmountPassed,
//isEndGame, resetPassedStatus, decideLastBid, LastBidProtocol
//---------------------------------
//Methods made by Atakan:
//useJailCard, playCard, getBoard, save, load
//---------------------------------
#ifndef GAME_H
#define GAME_H

#include "dice.h"
#include "gamerules.h"
#include "savegame.h"

class Game
{
public:
    Game(const int NPlayers = 2);

    //method: endTurn
    //Next player will be set as the current player
    void endTurn();

    //PARAM: an Boolean
    //Move Token bool dictactes if the player his token should be moved.
    //Returns the dicerolls
    QPair<int,int> throwDice(const bool &MoveToken);

    //method:
    //Returns the pointer from the board member that resides in Bank.
    Board * getBoard();

    //method:
    //Returns an pointer from the GameRules member.
    GameRules * getGameRules();

    //method:
    //Returns an pointer from the Bank member that resides in GameRules.
    Bank* getBank();

    //method: buyProperty
    //Current player will buy the property his token is on
    void buyProperty(const bool &Buy);

    //Method:
    //buys or sells an house or hotel
    void buyOrSellHouseHotel(const int &TileNumber, const bool &House, const bool buy);

    //method:
    //The corresponding player will take out(or keep)/pay for an mortgage
    void mortgage(const int &TileNumber, const bool &What, const bool &Inherted);

    //method:
    //Player will pay the rent to the player that owns the tile that his token is on
    void payRent();

    //Method:
    //Player will pay the bail price, (Player status will be cleared)
    //Or the player pays tax. (depens on which tile he is on)
    void pay();

    //Method:
    //Player pays the amount he still needs to pay to the other player/bank
    //Returns true if the player succeeded in paying off his debt
    bool payDebt();

    //method: useJailCard
    //PRE: Player has to be in Jail and has to have a Jail Card obtained from CHANCE or COMMUNITY CHEST tiles.
    void useJailCard();

    //Method:PlayCard()
    //PRE: A Player's token has to either step on a COMMUNITY CHEST or CHANCE tile.
    //Players pulls a random chance or community chest card and will perform what the card says.
    void playCard();

    //method:
    //This will set the Bidder index on the first person that is allowed to bid in the player list.
    //Or it will select the next person that is allowed to bid.
    void setCurrentBidder();

    //method:
    //Player can increase the Highest bid by giving an amount to increas it with, incase their
    //bid amount equals 0 it will count as passing, and won't be able to participate in the bid of the current auction item.
    void bidAuction(const int Amount);

    //Method:
    //Player will pass on the current auction item.
    void bidPass();

    //Save & Load:
    void save();
    void load();

    //Method:
    //Returns the winner index and his the player his balance
    QPair<int, int> exit();

    //method:
    //Returns the bidder index.
    int getCurrentBidder();

    //method:
    //Retuns the current Player index.
    int getCurrentPlayer();

    //method:
    //PARAM: An integer that is an index of an player!.
    //Returns an pointer of an player corresponding wit the index.
    Player* getPlayer(const int &Index);

    //Method:
    //PARAM: An Player Figure
    //Returns the index that belongs to that player
    int getPlayerIndex(const Figure Player);
private:

    //method:
    //Moves the player the total sum of the dice rolls.
    void moveToken(QPair<int,int> &DiceRoll);

    //Method:
    //Sets the amount of rounds an player is in jail
    //or resets the amount of rounds.
    void endTurnJailProtocol(Player* Player);

    //Method:
    //PARAM: An player figure
    //Returns the corresponding player address that contains the figure
    Player* getPlayer(const Figure &Player);

    //method:
    //returns the next player to make their turn. (if bankrupt, ignored)
    void selectNextPlayer();

    //method:
    //returns the amount of players that passed.
    int checkAmountPasses();

    //Method:
    //Returns true if there is one or none player's left
    bool isEndGame();

    //method:
    //Resets all the players hun HasPassed boalean to false.
    void resetPassedStatus();

    //Method:
    //Returns true if it is the last bid
    bool decideLastBid(const int &AmountPlayers, const bool &IncreaseBid);

    //Method:
    //PARAM: bool that is true if it is the last bid
    //Check's if it is the last bid, and will excecute the corresponding code
    void lastBidProtocol(const bool &LastBid);

    //members:
    int m_AmountDubbelThrows{0};
    int m_CurrentPlayer{0};
    int m_BidderIndex{0};
    int m_AuctionRound{0};

    std::vector<Player> m_Players;
    GameRules m_GameRules;
    Dice m_Dice;
    SaveGame * m_Save;
};

#endif // GAME_H
