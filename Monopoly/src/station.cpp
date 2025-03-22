#include "station.h"

Station::Station(QJsonValue StationInfo) : Tile{true}
{
    //Initializes all members according to a JSON file which contains information about the the tiles.
    m_StationName = StationInfo["stationname"].toString();

    QJsonValue PriceInfo = StationInfo["prices"];

    m_RentPrices[0] = PriceInfo["price"].toInt();
    m_RentPrices[1] = PriceInfo["rent"].toInt();
    m_RentPrices[2] = PriceInfo["rent with 2 owned"].toInt();
    m_RentPrices[3] = PriceInfo["rent with 3 owned"].toInt();
    m_RentPrices[4] = PriceInfo["rent with all owned"].toInt();
    m_RentPrices[5] = PriceInfo["mortgageTakeOut"].toInt();
    m_RentPrices[6] = PriceInfo["mortgagePayoff"].toInt();
}


QString Station::getStationName(){
    return m_StationName;
}

int Station::getRentOrPrice(const int NStationsOwned)
{
    const int RentPriceIndex = NStationsOwned;
    return m_RentPrices[RentPriceIndex];

}



bool Station::isMortgaged()
{
    return m_Mortgaged;
}

int Station::getMortgageValue(bool What){
    if (What){
        return m_RentPrices[5];
    }
    else
        return m_RentPrices[6];
}



void Station::mortgage(bool IsBeingMortgaged)
{
    if (IsBeingMortgaged){
        m_Mortgaged = true;
    }
    else
        m_Mortgaged = false;
}



