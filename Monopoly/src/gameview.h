//Auhtors: Kumas Atakan, Ieracitano Alessio
//--------------------------
//Methods made by Atakan:
//BoardBiew, GameView
//
//--------------------------
//Methods made by Alessio:
//buildMenu, throwDice, MenuScene
//
//--------------------------
#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsProxyWidget>
#include <QGraphicsSimpleTextItem>
#include <QPushButton>
#include <QApplication>
#include <QMessageBox>
#include <QTableWidget>

#include "game.h"
#include "playerview.h"
#include "boardview.h"
#include "diceview.h"
#include "cardview.h"
#include "menuscene.h"
#include "prisonview.h"
#include "auctionview.h"
#include "bankview.h"
#include "propertyview.h"

class GameView : public QMainWindow
{
    Q_OBJECT

public:
    GameView(QWidget *parent = nullptr);

    //Method:
    //Displays the menu of the game.
    void buildMenu();

public slots:

    ///MENU CONNECTS



    //Method:
    //If during a game, the player decides the save the current status of the game, this method will perform.
    void saveGame();

    //Method:
    //If during a game, a player decides to end it early, this method will perform.
    void endGame();

    //Method:
    //If pressed on 'Load Game', the explorer's window will open for the user to select a JSON Save File.
    void loadGame();

    //Method:
    //Once returned from the info menu, the menu with the standard options will be reset.
    void returnToMenuFromInfo();

    //Method:
    //If clicked on 'Info', this method will perform and display the info menu.
    void gameInfo();

    //Method:
    //If clicked on 'New game', this method will perform and display the player selection menu.
    void PlayerSelectionMenu();

    //Method:
    //If the amount of Players is selected and the player presses on 'Start Game', everything about a new game will be initialised.
    void newGame();

    ///END TURN METHODS

    //Method:
    //Displays the end turn button.
    void showEndTurn();

    //Method:
    //If the player decides to end their turn, the turn will be given to the next player. There will also be checked if the player who ended their turn is indebted, that means they'll get bankrupt.
    void endTurn();

    ///PAYING RENT AND TAX METHODS:

    //Method:
    //PARAM: a boolean that informs whether the property is a utility or not.
    //Shows the rent value of a property, if this a utility, a different kind of rent value is calculated and shown.
    void showPayRent(const bool &IsCompany);
    void showPayTax();

    //Method:
    //This method is for if the player performs to pay the rent of a street or station.
    void payRent();



    //Method:
    //This method is for if the player performs to pay the rent of a utility/company.
    void payUtility();

    //Method:
    //This method is for if the player performs to pay income or super tax costs to the bank.
    void payTax();

    ///PRISON METHODS
    //Method:
    //PARAM: a boolean that checks whether the player in jail is still allowed to attempt to throw a double with the dices, a boolean that checks whether the player has jail card
    //Shows all possible options for the player to escape from jail depending on the parameters.
    void showPrisonOptions(bool throwDiceAllowed, bool JailCardObtained);


    //Method:
    //If the player chooses for the prison option pay Bail, this will be performed.
    void payBail();

    //Method:
    //PRE: player has to have a jail card.
    //If the player chooses for the prison option to use their jail card, this will be performed.
    void useJailCard();

    //Method:
    //If the player has chosen any prison option, those options will be hidden.
    void hideBail_JailCard();



    ///CARDS METHODS:

    //Method:
    //PARAM: The type of the card, The chore/action written on the card
    //Displays the card that player has pulled.
    void showPullCard(CardType &Type, Card &Action);


    //Method:
    //PRE: Player has to be on a chance or community chest tile.
    //If the player peforms the card, this method will be triggered.
    void playCard();


    ///MOVEMENT METHODS:

    //Method:
    //Displays the dice numbers and makes the player who has thrown the dice, move.
    void throwDice();
    void showThrowDiceButton();



    ///END GAME METHODS:

    //Method:
    //PRE: Someone ended the game early
    //PARAM: The player who has won (with the most balance).
    //Displays the winner with an information message box after ending the game, afterwards the program is closed.
    void showCaseWinner(int &Player);

    ///"DEBT TO PLAYER OR BANK" METHODS

    //Method:
    //If a player inherits mortgaged properties from another player, they will get a window, which allows them to either immediately pay off the mortgage of the properties or keep them.
    void inheritedMortgages();

    //Method:
    //PARAM: The amount you try to pay to a player or the bank. The token/figure of a player you're indebted to, if you're indebted to a player at that moment.
    //If a player has to pay off their debt, a option will be trigged and available which states 'Pay Debt'.
    void payOffDebt(const int &Amount, const Figure &DebtTo);

    //Method:
    //If a player wants to pay off their debt, this method will be perform. However, this could only succeed if they have the money for it.
    //If they fail, The debted player could go bankrupt.
    void PayDebt();


    ///PROPERTY OPTIONS METHOD:

    //Methods:
    //Updates the property options table if a players would like to check out a different kind of property (Streets, Stations, Companies) they own.
    void UpdateTable();
    void StreetOptions();
    void StationOptions();
    void CompanyOptions();


    //Method:
    //Displays the property options menu.
    void showBuyBuilding();

    //Method:
    //PARAM: a boolean expression, which is true, if the player tends to purchase the property, false, otherwise.
    void buyProperty(bool buy);

    //Method:
    //If the player tends to place a house for their property, this will be performed.
    void buyHouse();

    //Method:
    //If the player tends to place a hotel for their property, this will be performed.
    void buyHotel();

    //Method:
    //If the player tends to sell a house of their property, this will be performed.
    void sellHouse();

    //Method:
    //If the player tends to sell a hotel of their property, this will be performed.
    void sellHotel();

    //Method:
    //If the players tend to take out a mortgage for a property, this will be performed.
    void takeOutMortgage();

    //Method:
    //If the players tend to take out a mortgage for a property, this will be performed.
    void payOffMortgage();

    //Method:
    //If the players tend to keep a mortgage for a property, that they inherited from an indebted player, this will be performed.
    void keepMortgage();


    //Method:
    //This method is for if the player decides to leave the property options menu.
    void Cancel();

    ///BUY PROPERTY METHODS:
    //Method:
    //PARAM: The price of the property
    //Shows a menu for the player to purchase the property or not with a given price which is displayed on the GUI.
    void showBuyMenu(const int &Price);

    //Method:
    //If the player presses on yes when asked to buy a property or not, the property will be bought.
    void yes();

    //Method:
    //If the player presses on no when asked to buy a property or not, the property will be ignored and an auction event will start.
    void no();

    ///AUCTION METHODS:

    //plus Methods:
    //A player can click on a +... button during an auction to add to their bid.
    void plusOne();
    void plusFive();
    void plusTen();
    void plusTwenty();
    void plusFifty();
    void plusHundred();
    void plusFiveHunderd();

    //Method:
    //The player has confirmed their bid. Their bid will become the highest bid in the auction and the turn of bidding will be given to the next player.
    void ConfirmBid();

    //Method:
    //This method is performed for if the player decides to not join the auction.
    void pass();

    //Method:
    //PARAM: A tile on which the property is located on the board, in order to display it.
    //When a player doesn't want to buy a property, this method will eventually be trigged and start an auction event.
    void startAuction(const int &AuctionTile);

    //Method:
    //PARAM: the highest bid amount, the player with the highest bid.
    //Both parameters will be displayed on the auction menu.
    void HighestBid(const int amount, Player* HighestBidder);

    //Method:
    //If an auction event ends, this method will be triggered.
    void endAuction();

    ///STANDARD METHODS

    //Method:
    //PARAM: Window title of the message box, Reason for error
    //If a non-valid action occurs, this method could be used to display the problem.
    void ErrorReason(const QString Window, const QString Reason);

    //Method:
    //After any change in balance of any player, this method will trigger.
    void updateBalances();





private:
    ///CONNECTS: These are for initialising all the connects with the majority of slots above.
    void MenuConnects() const;
    void GameConnects() const;
    void auctionConnects() const;
    void gameRulesConnects() const;
    void bankConnects() const;
    void propertyConnects() const;

    ///PRIVATE METHODS:

    ///BUTTONS AND CREATION METHODS: these initialise all buttons and view data necessary for the game.
    //Method:
    //PARAM: The amount of players for a game.
    //Initialises the player data on the GUI, consisting of their Playername and balance.
    void makePlayerInfoCards(const int &AmountPlayers);

    //Method:
    //PARAM: The results of the 2 thrown dices.
    //After a dice is thrown, sets the new dice numbers on the dice.
    void setDiceRolls(QPair<int, int> &DiceRolls);


    void makeButtons();  //Creates the game buttons.
    void beginStatusButtons(); //Creates the menu buttons.
    void setScale(); //Sets the size for the buttons.
    void setPosition(); //Sets the positions of the buttons.
    void makeDice(); //Created the two white dices on the board.


    ///PROPERTY OPTION PRIVATE METHODS:


    //Method:
    //When taken at a mortgage, this method will eventually process the taking out of paying off the mortgage of a selected property
    //On the property options menu.
    void mortgageAction(const bool &TakeOut);


    //Method:
    //When a player decides to buy or sell a building for a street, this method will eventually be triggered and process all of it.
    void buySellBuilding(const bool &House, const bool &Buy);

    //Methods:
    //PRE: the kind of property to take out or pay off a mortgage for, must be evaluated
    //Calls one of the functions and performs a mortgage operation according to the evaluation in the PRE-section.
    void streetMorgage(int *TileNumber, const int &SelectedRow, const bool &TakeOut);
    void stationMorgage(int *TileNumber, const int &SelectedRow, const bool &TakeOut);
    void companyMorgage(int *TileNumber, const int &SelectedRow, const bool &TakeOut);

    //Method:
    //This method is performed whenever the player inherits mortgaged properties from a indebted player.
    void instantMortgageChoice(int *TileNumber, const int &SelectedRow);


    ///MEMBERS
    Game* m_Game;

    //Game setting members
    QPushButton *m_EndGameButton;
    QPushButton *m_SaveGameButton;
    QGraphicsProxyWidget *m_SaveGameButtonProxy;
    QGraphicsProxyWidget *m_EndGameButtonProxy;

    //Playerturn setting members.
    QGraphicsTextItem *m_TurnInfoText;
    QPushButton* m_EndTurnButton;
    QGraphicsProxyWidget *m_EndTurnButtonProxy;

    //DiceView members
    QList<DiceView*> m_Dices;
    QGraphicsProxyWidget *m_DiceButtonProxy;
    QPushButton* m_DiceButton;

    //PlayerView members
    std::vector<PlayerView*> m_Players;

    //CardView members
    QPushButton *m_PullCardButton;
    CardView m_Card;
    QGraphicsProxyWidget *m_PullCardButtonProxy;

    //PrisonView
    PrisonView* m_PrisonButtons;

    //AuctionView
    AuctionView* m_Auction;

    //BankView
    BankView* m_Bank;

    //PropertyView Members
    PropertyView* m_BuildingOptions;
    QList<QPair<Street *, int>> m_PlayerStreets;
    QList<QPair<Station *, int>> m_PlayerStations;
    QList<QPair<Company *, int>> m_PlayerCompanies;


    //Scenes and Views:
    BoardView * m_Scene;
    MenuScene* m_MenuScene;
    QGraphicsView * m_View;
};
#endif // GAMEVIEW_H
