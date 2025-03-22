#include "savegame.h"


SaveGame::SaveGame(int PlayerAmount) : m_PlayerData(PlayerAmount){}

void SaveGame::addPlayer(Player PlayerInfo, int PlayerPos, int PlayerNum, QList<Street*> PlayerStreets, QList<Station *> PlayerStations, QList<Company *> PlayerCompanies){
    m_PlayerData[PlayerNum].insert("balance", PlayerInfo.getBalance());
    m_PlayerData[PlayerNum].insert("in jail?", PlayerInfo.getPlayerStatus());
    m_PlayerData[PlayerNum].insert("rounds in jail", PlayerInfo.getRoundsInJail());
    m_PlayerData[PlayerNum].insert("figure", static_cast<int>(PlayerInfo.getFigure()));
    m_PlayerData[PlayerNum].insert("Current Position", PlayerPos);

    QJsonArray PlayerCardInfo;

    QList<Card *> PlayerCards = PlayerInfo.getCards();

    //Data representation of Player Cards:
    //Cards = [] : has no cards.
    //Cards = [0 of 1] : has either a 'get out of jail for free' chance or cchest cards.
    //Cards = [0, 1] : has both 'get out of jail free' cards.

    for (auto i : PlayerCards){
        if (i->TypeOfCard() == CardType::CHANCE){
            PlayerCardInfo.append((int)CardType::CHANCE);
        }
        else if (i->TypeOfCard() == CardType::COMMUNITYCHEST){
            PlayerCardInfo.append((int)CardType::COMMUNITYCHEST);
        }
    }


    m_PlayerData[PlayerNum].insert("Cards", PlayerCardInfo);


    QJsonObject BelongingData;

    int BeloningsCounter = 0;

    for (int index = 0; index < PlayerStreets.size(); ++index){
        QJsonObject Street;

        Street.insert("type", "Street");
        Street.insert("name", PlayerStreets[index]->getStreetName());
        Street.insert("hotels", PlayerStreets[index]->getHousesAndHotels().first);
        Street.insert("houses", PlayerStreets[index]->getHousesAndHotels().second);
        Street.insert("Mortgaged?", PlayerStreets[index]->isMortgaged());
        BelongingData.insert("Property" + QString::number(BeloningsCounter), Street);
        ++BeloningsCounter;
    }

    for (int index = 0; index < PlayerStations.size(); ++index){
        QJsonObject Station;
        Station.insert("type", "Station");
        Station.insert("name", PlayerStations[index]->getStationName());
        Station.insert("Mortgaged?", PlayerStations[index]->isMortgaged());
        BelongingData.insert("Property" + QString::number(BeloningsCounter), Station);
        ++BeloningsCounter;
    }

    for (int index = 0; index < PlayerCompanies.size(); ++index){
        QJsonObject Company;
        Company.insert("type", "Company");
        Company.insert("name", PlayerCompanies[index]->getCompanyName());
        Company.insert("Mortgaged?", PlayerCompanies[index]->isMortgaged());
        BelongingData.insert("Property" + QString::number(BeloningsCounter), Company);
        ++BeloningsCounter;
    }


    m_PlayerData[PlayerNum].insert("Belongings", BelongingData);
    m_AllPlayersData.insert("Player " + QString::number(PlayerNum), m_PlayerData[PlayerNum]);

}


void SaveGame::initTurn_PlayerAmount(int PlayersTurn, int PlayerAmount){
    m_Data.insert("Amount of Players", PlayerAmount);
    m_Data.insert("Current Player", PlayersTurn);
}

void SaveGame::addBankInfo(Bank * BankInfo){

    //Inserts the amount of Buildings into the data of the bank.
    QPair<int, int> BuildingsLeft = BankInfo->getAmountBankBuildings();
    m_BankData.insert("Houses Left", BuildingsLeft.first);
    m_BankData.insert("Hotels Left", BuildingsLeft.second);

}

void SaveGame::Write(QString FileName){

    //Creates a Json Document for the Data
    QJsonDocument SaveDocument(m_Data);

    //Makes a new file depending on the given filename
    QFile newSave(FileName);

    //Writes all data into the file and saves it.
    newSave.open(QFile::WriteOnly);
    newSave.write(SaveDocument.toJson());
}

void SaveGame::Combine(){
    m_Data.insert("Bank Status", m_BankData);
    m_Data.insert("Players Status", m_AllPlayersData);

    qDebug() << m_Data;
}


//JSON SAVE FILE EXAMPLE WITH 6 PLAYERS (AND STANDARD TEMPLATE)

/*{
    "Amount of Players": 6,
    "Bank Status": {
        "Hotels Left": 12,
        "Houses Left": 12
    },
    "Current Player": 4,
    "Players Status": {
        "Player 0": {
            "Belongings": {
                "Property0": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Trafalgar\nSquare",
                    "type": "Street"
                },
                "Property1": {
                    "Mortgaged?": false,
                    "name": "Kings\nCross\nStation",
                    "type": "Station"
                },
                "Property2": {
                    "Mortgaged?": false,
                    "name": "Marylebone\nStation",
                    "type": "Station"
                }
            },
            "balance": 1030,
            "bankrupt?": false,
            "cards": [
            ],
            "current position": 20,
            "in jail?": false,
            "rounds in jail": 0
        },
        "Player 1": {
            "Belongings": {
                "Property0": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Marlborough\nStreet",
                    "type": "Street"
                },
                "Property1": {
                    "Mortgaged?": false,
                    "name": "Electric\nCompany",
                    "type": "Company"
                }
            },
            "balance": 1197,
            "bankrupt?": false,
            "cards": [
            ],
            "current position": 22,
            "in jail?": false,
            "rounds in jail": 0
        },
        "Player 2": {
            "Belongings": {
                "Property0": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "The Angel,\nIslington",
                    "type": "Street"
                },
                "Property1": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Pall Mall",
                    "type": "Street"
                },
                "Property2": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Vine\nStreet",
                    "type": "Street"
                },
                "Property3": {
                    "Mortgaged?": false,
                    "name": "Fenchurch St\nStation",
                    "type": "Station"
                }
            },
            "balance": 1085,
            "bankrupt?": false,
            "cards": [
            ],
            "current position": 15,
            "in jail?": false,
            "rounds in jail": 0
        },
        "Player 3": {
            "Belongings": {
                "Property0": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Pentonville\nRoad",
                    "type": "Street"
                },
                "Property1": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Fleet\nStreet",
                    "type": "Street"
                },
                "Property2": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Leicester\nSquare",
                    "type": "Street"
                },
                "Property3": {
                    "Mortgaged?": false,
                    "name": "Liverpool\nStreet\nStation",
                    "type": "Station"
                }
            },
            "balance": 500,
            "bankrupt?": false,
            "cards": [
                1
            ],
            "current position": 2,
            "in jail?": false,
            "rounds in jail": 0
        },
        "Player 4": {
            "Belongings": {
                "Property0": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Northumber-\nland\nAvenue",
                    "type": "Street"
                },
                "Property1": {
                    "Mortgaged?": false,
                    "hotels": 0,
                    "houses": 0,
                    "name": "Mayfair",
                    "type": "Street"
                }
            },
            "balance": 801,
            "bankrupt?": false,
            "cards": [
            ],
            "current position": 12,
            "in jail?": false,
            "rounds in jail": 0
        },
        "Player 5": {
            "Belongings": {
            },
            "balance": 1411,
            "bankrupt?": false,
            "cards": [
            ],
            "current position": 25,
            "in jail?": false,
            "rounds in jail": 0
        }
    }
}
*/

