//Author: Kumas Atakan
#ifndef SAVEGAME_H
#define SAVEGAME_H
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <Player.h>
#include <Bank.h>


class SaveGame
{
public:

    //Method:
    //PARAM: the amount of player, that will play the game.
    SaveGame(int PlayerAmount = 2);

    //Method:
    //Combines the status of the bank with the status of all players.
    void Combine();

    //Method:
    //PRE: Player has to give their SAVE file, a name.
    //Writes a JSON-save object which holds all data of the current game, into a JSON-Save file.
    void Write(QString FileName);

    //Method:
    //PARAM: The player themselves, the player's position, the player's number, all of the player's properties.
    //Adds all data about 1 plaeyer to a certain JSON-Save object.
    void addPlayer(Player PlayerInfo, int PlayerPos, int PlayerNum, QList<Street*> PlayerStreets, QList<Station *> PlayerStations, QList<Company *> PlayerCompanies);

    //Method:
    //PARAM: The bank
    //Adds all data about the current state of the bank (for example, how many buildings does the bank have left) to a certain JSON-Save object.
    void addBankInfo(Bank * BankInfo);

    //Method:
    //PARAM: The current player whose turn it is, the amount of players.
    //Adds all data about which player's turn it is and the amount of players playing to a certain JSON-Save object.
    void initTurn_PlayerAmount(int PlayersTurn, int PlayerAmount);

private:

    //Members:

    QJsonObject m_Data; //Consists of the data of the complete game.
    QJsonObject m_AllPlayersData; //Consists only of data of all the players and their status.
    QJsonObject m_BankData; //Consists only of data of the bank and its status.
    QList<QJsonObject> m_PlayerData; //A list consisting of all data of players, which eventually gets added to the m_AllPlayersData member.

};

#endif // SAVEGAME_H
