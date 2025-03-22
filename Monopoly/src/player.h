//Author: Ieracitano Alessio
#ifndef PLAYER_H
#define PLAYER_H

#include "figure.h"
#include "card.h"
#include <transactiontype.h>

class Player
{
public:
    //Constructors:
    //PARAM: The player's number in order to identify them more easily.
    Player(const int i);

    //Method:
    //Returns the balance of the player.
    int getBalance();

    //Method:
    //Returns the status of the player. That is, if the player is in jail or not.
    bool getPlayerStatus();

    //Method:
    //PRE: Player has to be in an auction
    //Returns whether the player (during an auction event) has passed and doesn't want to buy a certain property.
    bool didPlayerPass();

    //Method:
    //PARAM: The amount of money, the type of transaction (does the player have to receive or pay this given amount?).
    //Does a money transaction according to the transaction type.
    void moneyTransaction(int Amount, TransactionType ToPay);

    //Method:
    //Returns the token/figure of the player.
    Figure getFigure();

    //Method:
    //PARAM: The state of the player. If true, the player is in jail, false, otherwise.
    //If the player is placed in Jail, their status will be changed.
    void playerInJail(bool Status);

    //Method:
    //Returns the amount of rounds which determines how long the player has been in jail.
    int getRoundsInJail();

    //Method:
    //Returns the cards owned by the player.
    QList<Card *> getCards();

    //Method:
    //If a round is passed during a player's jailtime, than the amount of rounds which determines how long the player has been in jail, will change.
    void setRoundsInJail(int Amount);

    //Method:
    //PRE: Player has to be in an auction.
    //If the player decides to pass (during an auction event), their status of having passed will change.
    void setPlayerPassed(bool Status);

    //Method:
    //PRE: Player ends their turn with debts and no money
    //The player is in a state of bankruptcy, and this will be set.
    void setPlayerBankrupt();

    //Method:
    //Checks whether a player is bankrupt or not.
    bool isPlayerBankrupt();

    //Method:
    //PARAM: a chance or Community chest card (is ought to be a 'get out of jail free' card)
    //If the player pulled a card they can keep for a while, the card will be added to their card collection.
    void addCard(Card* GetOutCard);

    //Method:
    //PRE: The player has used one of its cards.
    //If the player uses a card, they've kept, the card will be removed from their card collection and placed back in the deck.
    Card* removeCard();

    //Method:
    //Checks whether the player has a jail card or not in their card collection. true, if so, false, otherwise.
    bool hasJailCard();
private:
    //Method:
    //PARAM: The player's number in order to identify them more easily.
    //Determines the token/figure a player will use for the game, depending on its playernumber.
    Figure findFigure(const int i);

    //members:
    Figure m_Figure;
    QList<Card*> m_Cards;         //get out of jail cards;
    int m_Balance{1500};
    int m_RoundsInJail{0};

    bool m_InJail{false};
    bool m_Passed{false};
    bool m_IsBankrupt{false};
};

#endif // PLAYER_H
