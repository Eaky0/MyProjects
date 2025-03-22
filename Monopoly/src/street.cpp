#include "street.h"

Street::Street(QJsonValue StreetInfo) : Tile{true}
{

    //Initializes all members according to a JSON file which contains information about the the tiles.
    m_StreetName = StreetInfo["streetname"].toString();
    QString StreetColorString = StreetInfo["color"].toString();
    m_StreetColor = findColor(StreetColorString);

    QJsonValue PriceInfo = StreetInfo["prices"];

    m_RentPrices[0] = PriceInfo["price"].toInt();
    m_RentPrices[1] = PriceInfo["rent"].toInt();
    m_RentPrices[2] = PriceInfo["rent with 1 house"].toInt();
    m_RentPrices[3] = PriceInfo["rent with 2 houses"].toInt();
    m_RentPrices[4] = PriceInfo["rent with 3 houses"].toInt();
    m_RentPrices[5] = PriceInfo["rent with 4 houses"].toInt();
    m_RentPrices[6] = PriceInfo["rent with hotel"].toInt();
    m_RentPrices[7] = PriceInfo["building cost"].toInt();
    m_RentPrices[8] = PriceInfo["mortgageTakeOut"].toInt();
    m_RentPrices[9] = PriceInfo["mortgagePayoff"].toInt();
}

bool Street::isMortgaged()
{
    return m_Mortgaged;
}


void Street::mortgage(bool IsBeingMortgaged)
{
    if (IsBeingMortgaged){
        m_Mortgaged = true;
    }
    else
        m_Mortgaged = false;
}


int Street::getMortgageValue(bool What)
{
    if (What){
        return m_RentPrices[8];
    }
    else
        return m_RentPrices[9];
}

QString Street::getStreetName() const
{
    return m_StreetName;
}


QPair<int, int> Street::getHousesAndHotels() const
{
    return {m_Houses, m_Hotels};
}

void Street::placeOrRemoveHouseHotel(const bool &House, const bool &Place)
{
    const int AMOUNT = 1;
    const int EMPTY = 0;

    //Buy a building
    if (Place){
        //Purchase a house
        if (House)
            m_Houses += AMOUNT;
        //Purchase a hotel
        else{
            m_Houses = EMPTY;
            m_Hotels = AMOUNT;
        }
    }
    //Sell a building
    else
        //Sell a house
        if (House)
            m_Houses -= AMOUNT;

        //Sell a hotel
        else
            m_Hotels -= AMOUNT;

}

int Street::getValue() const
{

    //Returns the complete value of a street, this also depends on the amount of buildings placed on it.
    const int INDEX_BULDINGCOST = 7;
    const int PRICEBUILDING = m_RentPrices[INDEX_BULDINGCOST];

    const int HOTELVALUEINHOUSES = (m_Hotels * 5);
    const int PRICE = (m_Houses + HOTELVALUEINHOUSES) * PRICEBUILDING;

    const int PRICEPROPERTY = m_RentPrices[0];

    int TotalAmount = (PRICE + PRICEPROPERTY);
    return TotalAmount;
}

Street::Color Street::getColor() const
{
    return m_StreetColor;
}


int Street::getPriceOrRent(bool OwnerHasFullColorset)
{
    //Calculates what rent or streetprice value the player has to receive depending on the state of the street.
    if (hasOwner() && OwnerHasFullColorset){
        //Street has a hotel:
        if (m_Hotels == 1){
            const int HOTELRENT = 7;
            return m_RentPrices[HOTELRENT];
        }
        //Street has an amount of houses
        else{
            int RentIndex = (m_Houses + 2);
            return m_RentPrices[RentIndex];
        }
    }
    //Starting rent price of the street
    else if (hasOwner()){
        const int RENT = 1;
        return m_RentPrices[RENT];
    }
    //The price of the street (a player is able to buy it)
    else{
        const int PRICE = 0;
        return m_RentPrices[PRICE];
    }
}

int Street::getBuildingCost()
{
    const int INDEX_BULDINGCOST = 7;
    return m_RentPrices[INDEX_BULDINGCOST];
}



Street::Color Street::findColor(QString ColorName)
{
    //Returns the color, according to what is written on the JSON file containing information about all tiles, for this street.
    if (ColorName == "Brown") return Color::BROWN;
    else if (ColorName == "Blue") return Color::BLUE;
    else if (ColorName == "Pink") return Color::PINK;
    else if (ColorName == "Orange") return Color::ORANGE;
    else if (ColorName == "Red") return Color::RED;
    else if (ColorName == "Yellow") return Color::YELLOW;
    else if (ColorName == "Green") return Color::GREEN;
    else return Color::DARKBLUE;
}






