//Author Kumas Atakan
#ifndef COMPANY_H
#define COMPANY_H


#include "tile.h"

class Company : public Tile
{
public:
    Company(QJsonValue CompanyInfo);

    //Method:
    //Returns the company name of the tile.
    QString getCompanyName();

    //Method:
    //Returns the cost price of the company
    int getPrice() override;

    //Method:
    //Returns the rent of the company
    int getRent(const int &AmountOwned, const int &DiceRollAmount);

    //Method:
    //Returns true if the company is mortgaged
    bool isMortgaged() override;

    //Method:
    //Sets the mortgage state of the company
    void mortgage(bool IsBeingMortgaged) override;

    //Method:
    //PARAM: an boolean that should be true if you takeout an mortgage else false
    //Returns the mortgage value
    int getMortgageValue(bool What) override;

private:
    QString m_CompanyName;
    std::array<int,3> m_Prices;
    bool m_Mortgaged{false};
};

#endif // COMPANY_H
