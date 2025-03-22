//Authors: Kumas Atakan, Iercitano Alesio
//------------------------
//Methods made by Atakan:
//Street, getStreetName, getHousesAndHotels, getMortgageValue, isMortgaged, mortgage,
//getColor, checkType
//-----------------------
//Methods made by Alessio:
//getPriceOrRent, placeOrRemoveHouseHotel, getValue
//-----------------------
#ifndef STREET_H
#define STREET_H

#include "tile.h"
#include <QString>

class Street : public Tile
{
public:

    //Enum class:
    //The enum class color is used to set and get the color of a street.
    enum class Color{ BROWN, BLUE, PINK, ORANGE, RED, YELLOW, GREEN, DARKBLUE };

    //Constructor:
    Street(QJsonValue StreetInfo);

    //Method:
    //Returns the price/rent of the street:
    int getPriceOrRent(bool OwnerHasFullColorset);

    //Method:
    //Returns the cost for building an house or hotel
    int getBuildingCost();

    //Method:
    //Returns the street name as an QString
    QString getStreetName() const;

    //Method:
    //Returns the amount of houeses and hotel as an QPair<int,int>
    QPair<int, int> getHousesAndHotels() const;

    //Method:
    //Places an house (if House == true) or hotel (if ...) or,
    //removes an house (if House == true) or hotel (if ...)
    void placeOrRemoveHouseHotel(const bool &House, const bool &Place);

    //Method:
    //returns the entire value of the street
    int getValue() const;

    //Method:
    //Returns the mortgage Take out or PayOff value
    int getMortgageValue(bool What) override;

    //Method:
    //Checks whether house is mortgaged or not
    bool isMortgaged() override;

    //Method:
    //Sets the mortgage state of the street
    void mortgage(bool IsBeingMortgaged) override;

    //Method:
    //Returns the color of the street
    Color getColor() const;

private:
    //Method:
    //Returns the color enum that corresponds with the Qstring name
    Color findColor(QString ColorName);
    //Members:
    std::array<int, 10> m_RentPrices;
    int m_Houses{0};
    int m_Hotels{0};
    Color m_StreetColor{Color::BROWN};
    QString m_StreetName;
    bool m_Mortgaged{false};
};

#endif // STREET_H
