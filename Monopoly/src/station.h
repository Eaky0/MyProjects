//Author: Kumas Atakan
#ifndef STATION_H
#define STATION_H

#include "tile.h"


class Station : public Tile
{
public:
    Station(QJsonValue StationInfo);

    //Method:
    //Returns the name of the station as an QString
    QString getStationName();

    //Method:
    //Returns the price or rent (depening on the input)
    int getRentOrPrice(const int NStationsOwned);


    //Method:
    //Return true if the station is mortgaged
    bool isMortgaged() override;

    //Method:
    //Sets the mortgage state of the station
    void mortgage(bool IsBeingMortgaged) override;

    //Method:
    //Returns the mortgage value
    int getMortgageValue(bool What) override;

private:
    QString m_StationName;
    std::array<int, 7> m_RentPrices;
    bool m_Mortgaged{false};


};

#endif // STATION_H
