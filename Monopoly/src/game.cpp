#include "game.h"

Game::Game(const int NPlayers) : m_GameRules{NPlayers}, m_Save{new SaveGame{NPlayers}}
{

    for (int i = 0; i < NPlayers ; ++i)
        m_Players.push_back(Player{i});

    Player* CurrentPlayer = &m_Players[m_CurrentPlayer];
    m_GameRules.setCurrentPlayer(CurrentPlayer);
}


void Game::save()
{
    Bank * BankPtr = m_GameRules.getBank();
    m_Save->addBankInfo(BankPtr);

    for (int index = 0; index <  m_Players.size(); ++index){

        std::tuple<QList<Street *>, QList<Station*>,QList<Company*>> PlayerBelongings = m_GameRules.searchBelongings(m_Players[index].getFigure());
        QList<Street *> PlayerStreets = std::get<0>(PlayerBelongings);
        QList<Station *> PlayerStations = std::get<1>(PlayerBelongings);
        QList<Company *> PlayerCompanies = std::get<2>(PlayerBelongings);

        int CurrentPosition = BankPtr->getPlayerPos(m_Players[index].getFigure());
        m_Save->addPlayer(m_Players[index], CurrentPosition, index, PlayerStreets, PlayerStations, PlayerCompanies);

    }

    m_Save->initTurn_PlayerAmount(m_CurrentPlayer, (int) m_Players.size());
    m_Save->Combine();
    m_Save->Write("MonoSave.json");

}

QPair<int, int> Game::exit()
{
    int WinnerIndex = 0;
    int HighestBalance = 0;

    for (int i = 0; i < m_Players.size(); ++i){
        int PlayerBalance = m_Players[i].getBalance();

        if (PlayerBalance > HighestBalance){
            WinnerIndex = (i + 1);
            HighestBalance = PlayerBalance;
        }
    }

    QPair<int, int> WinnerInfo = {WinnerIndex, HighestBalance};
    return WinnerInfo;
}



void Game::endTurn()
{
    Player* CurrentPlayer = &m_Players[m_CurrentPlayer];
    const int RESET = 0;

    //We reset the amount of double throws
    m_AmountDubbelThrows = RESET;
    endTurnJailProtocol(CurrentPlayer);

    //If the player went bankrupt, we need to auction his belongins
    if (CurrentPlayer->getBalance() < 0){
        CurrentPlayer->setPlayerBankrupt();
        m_GameRules.playerWentBankrupt(CurrentPlayer);
    }

    //We check if there is an winner
    bool endGame = isEndGame();
    if (!endGame){
        selectNextPlayer();
    }
    else{
        m_GameRules.decideWinner(m_Players);
    }
}



void Game::selectNextPlayer()
{
    const int AmountPlayers = (int) m_Players.size();
    const int RESET = 0;

    //If The currentplayer is the last player in the array
    //we then will need to point the index back to player one.
    if (m_CurrentPlayer >= AmountPlayers - 1){
        m_CurrentPlayer = RESET;
    }
    //Else we just point to the next player in the array.
    else
        ++m_CurrentPlayer;

    while (m_Players[m_CurrentPlayer].isPlayerBankrupt()){
        ++m_CurrentPlayer;

        if (m_CurrentPlayer >= AmountPlayers)
            m_CurrentPlayer = RESET;
    };

    //We setup the buttons that the next player is allowed to use
    //in accordance with the game rules.
    Player* NextPlayer = &m_Players[m_CurrentPlayer];
    m_GameRules.setCurrentPlayer(NextPlayer);
    m_GameRules.playerOptions();
}

QPair<int,int> Game::throwDice(const bool &MoveToken)
{

    QPair<int, int> Dices = m_Dice.throwDice();

    if (MoveToken)
        moveToken(Dices);

    return Dices;
}

void Game::buyProperty(const bool &buy)
{
    //We check which rules apply (if buy == false, we will start the auction)
    //We also check if the player threw an double on the dice, and aply the corresponding game rules.
    bool NoAuction = m_GameRules.buyPropertyRule(buy);

    if (NoAuction)
        m_GameRules.checkForDoubleThrows(m_AmountDubbelThrows);
}

void Game::buyOrSellHouseHotel(const int &TileNumber, const bool &House, const bool buy)
{
    if (buy)
        m_GameRules.buyHouseHotelRule(TileNumber, House);
    else
        m_GameRules.sellHouseHotelRule(TileNumber, House);
}

Board * Game::getBoard()
{
    return m_GameRules.getBoard();
}

GameRules *Game::getGameRules()
{
    return &m_GameRules;
}

Bank *Game::getBank()
{
    return m_GameRules.getBank();
}

void Game::payRent()
{
    Figure CurrentPlayer = m_Players[m_CurrentPlayer].getFigure();
    const int PositionPlayer = m_GameRules.getPlayerPosition(CurrentPlayer);
    const bool IsUtility =  m_GameRules.isCompanyTile(PositionPlayer);
    Figure PropertyOwner = m_GameRules.getPropertyOwner(PositionPlayer);
    Player* Owner = getPlayer(PropertyOwner);

    bool PaymentSucceeded = true;

    //We check if the address of the owner isn't an nullpointer.
    if (Owner != nullptr){
        if (IsUtility){
            QPair<int,int> DiceRoll = m_Dice.getNumbers();
            int TotalRollAmount = DiceRoll.first + DiceRoll.second;
            PaymentSucceeded = m_GameRules.payRent(Owner, TotalRollAmount);
        }
        else
            PaymentSucceeded = m_GameRules.payRent(Owner);
    }

    //We also check if the player threw an double on the dice, and aply the corresponding game rules.
    //Only if the payment succeeded.
    if (PaymentSucceeded)
        m_GameRules.checkForDoubleThrows(m_AmountDubbelThrows);
}

void Game::pay()    //Tax or bail
{
    bool PaymentSucceeded = m_GameRules.pay();
    if (PaymentSucceeded)
        m_GameRules.checkForDoubleThrows(m_AmountDubbelThrows);     //See previous documentation
}

bool Game::payDebt()
{
   bool PaySucceeded = m_GameRules.payDebt();

   //We check if the pay succeeded, if it did, the player is allowed to move again
   //incase he threw an double.
   if (PaySucceeded){
        m_GameRules.checkForDoubleThrows(m_AmountDubbelThrows);
    }
   return PaySucceeded;
}

void Game::setCurrentBidder()
{
    const int AmountPlayers = (int) m_Players.size();

    //First we check if the Bidder index isn't out of bounds
    if (m_BidderIndex >= AmountPlayers)
        m_BidderIndex = 0;

    //Next we select the first next player that didn't pass
    while ( m_Players[m_BidderIndex].didPlayerPass() || m_Players[m_BidderIndex].isPlayerBankrupt() ){
        ++m_BidderIndex;

        if (m_BidderIndex >= AmountPlayers)
            m_BidderIndex = 0;
    };
}

void Game::bidAuction(const int Amount)
{
    const int AmountPlayers = (int) m_Players.size();
    Player* CurrentBidder = &m_Players[m_BidderIndex];
    const bool INCREASE_BID = true;

    //If player did not place an amount, than they pass
    if (Amount == 0){
        m_Players[m_BidderIndex].setPlayerPassed(true);
    }

    //We first check if this is the last bid.
    //We pass the bid amount, player and if this is the last bid to GameRules (eventually to Bank)
    bool LastBid = decideLastBid(AmountPlayers, INCREASE_BID);
    m_GameRules.passBid(CurrentBidder, Amount,  LastBid);

    //If this is the last bid we reset the players passs tatus and reset the m_BidderIndex
    //else we select the next bidder
    lastBidProtocol(LastBid);
}

void Game::bidPass()
{
    const int AmountPlayers = (int) m_Players.size();
    const bool INCREASE_BID = false;
    const int PASS = 0;

    Player* CurrentBidder = &m_Players[m_BidderIndex];
    m_Players[m_BidderIndex].setPlayerPassed(true);

    //We decide if this is the last bid, and pass this info over to GameRules
    const bool LastBid = decideLastBid(AmountPlayers, INCREASE_BID);
    m_GameRules.passBid(CurrentBidder, PASS,  LastBid);

    //We check if it is the last bid or we just need to
    //select the next bidder;
    lastBidProtocol(LastBid);
}

int Game::getCurrentBidder()
{
    return m_BidderIndex;
}

int Game::getCurrentPlayer()
{
    return m_CurrentPlayer;
}

Player *Game::getPlayer(const int &Index)
{
    return &m_Players[Index];
}

int Game::getPlayerIndex(const Figure Player)
{
    int Index = 0;
    int AmountPlayers = (int) m_Players.size();
    for (int i = 0; i < AmountPlayers; ++i){
        Figure Search = m_Players[i].getFigure();
        if (Search == Player)
            Index = i;
    }

    return Index;
}

void Game::moveToken(QPair<int, int> &DiceRoll)
{
    int FirstNumber = DiceRoll.first;
    int SecondNumber = DiceRoll.second;
    int TotalAmountOfJumps = FirstNumber + SecondNumber;

    if (FirstNumber == SecondNumber)
        ++m_AmountDubbelThrows;

    else if (FirstNumber != SecondNumber)
        m_AmountDubbelThrows = 0;

    //We pass on the thrown dice numbers to the board (to move the tokens)
    //At last we return the numbers on the dice, so we can update the GUI.
    m_GameRules.moveToken(TotalAmountOfJumps, m_AmountDubbelThrows);
}

void Game::endTurnJailProtocol(Player *Player)
{
    const bool playerInJail = Player->getPlayerStatus();
    const int RESET = 0;

    //Next if the player is in jail we will need to update the amount of rounds
    //he is in jail
    if (playerInJail){
        int RoundsInJail = Player->getRoundsInJail();
        Player->setRoundsInJail(RoundsInJail + 1);
    }
    //Else we reset his amount of rounds he was in jail
    else
        Player->setRoundsInJail(RESET);
}

Player* Game::getPlayer(const Figure &PlayerToFind)
{
    Player* GetPlayer = nullptr;
    const int AMOUNTPLAYERS = (int) m_Players.size();

    //we Find the player that is the owner of the property and pass
    //on an pointer to the owner.
    for (int i = 0; i < AMOUNTPLAYERS; ++ i){
        if (m_Players[i].getFigure() == PlayerToFind){
            GetPlayer = &m_Players[i];
            break;
        }
    }

    return GetPlayer;
}

int Game::checkAmountPasses()
{
    const int AmountPlayers = (int) m_Players.size();

    int Amount = 0;
    for (int i = 0; i < AmountPlayers; ++i){    //We count the amount of players that have passed or that are bankrupt
        if (m_Players[i].didPlayerPass() || m_Players[i].isPlayerBankrupt())
            ++Amount;
    }
    return Amount;  //We return the counted amount
}

bool Game::isEndGame()
{
    const int AmountPlayers = (int) m_Players.size();

    int AmountBankrupt = 0;     //We count the amount of players that went bankrupt
    for (int i = 0; i < AmountPlayers; ++i){
        if (m_Players[i].isPlayerBankrupt())
            ++AmountBankrupt;
    }

    //If the amount of players is equal or bigger than the amount of player minus one
    //then we return true, because the game should end.
    const bool endGame = ((AmountPlayers - 1) <= AmountBankrupt);
    return endGame;
}

void Game::resetPassedStatus()
{
    //We reset all players their passed status
    const int AmountPlayers = (int) m_Players.size();
    for (int i = 0; i < AmountPlayers; ++i){
        m_Players[i].setPlayerPassed(false);
    }
}

bool Game::decideLastBid(const int &AmountPlayers,  const bool &IncreaseBid)
{
    bool LastBid;

    //Edge case
    if (AmountPlayers == 2){
        LastBid = true;
    }
    else{   //We decide depening on the situation on which way we should calculate the "LastBid"
        const int AmountPlayersPassed = checkAmountPasses();
        const bool HasAnHighestBidder = (m_GameRules.hasHighestBidder() || IncreaseBid);

        if (HasAnHighestBidder){
            LastBid = (AmountPlayersPassed >= AmountPlayers - 1);
        }
        else
            LastBid = (AmountPlayersPassed >= AmountPlayers);
    }

    //We return the result (true if this is the last bid else false)
    return LastBid;
}

void Game::lastBidProtocol(const bool &LastBid)
{
    if (LastBid){
        const int RESET = 0;
        resetPassedStatus();

        m_BidderIndex = RESET;
        m_AuctionRound = RESET;
        m_GameRules.checkForDoubleThrows(m_AmountDubbelThrows);     //See previous documentation
    }

    //If this is not the last bidder we let the index point to the next player.
    //We check if the next player didn't already pass and that the bidder index isn't out of bounds
    else{
        ++m_BidderIndex;
        setCurrentBidder();
        ++m_AuctionRound;
    }
}


void Game::playCard()
{
    m_GameRules.cardPerformingRule(&m_Players, m_AmountDubbelThrows);
}

void Game::useJailCard()
{
    m_GameRules.jailCardRule();
}

void Game::mortgage(const int &TileNumber, const bool &What, const bool &Inherted)
{
    m_GameRules.mortgage(TileNumber, What, Inherted);
}

