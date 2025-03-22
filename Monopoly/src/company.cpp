#include "company.h"

Company::Company(QJsonValue CompanyInfo) : Tile{true}
{
    m_CompanyName = CompanyInfo["companyname"].toString();
    m_Prices[0] = CompanyInfo["prices"]["price"].toInt();
    m_Prices[1] = CompanyInfo["prices"]["mortgageTakeOut"].toInt();
    m_Prices[2] = CompanyInfo["prices"]["mortgagePayoff"].toInt();

}

QString Company::getCompanyName()
{
    return m_CompanyName;
}

bool Company::isMortgaged(){
    return m_Mortgaged;
}

int Company::getMortgageValue(bool What)
{
    if (What){
        return m_Prices[1];
    }
    else
        return m_Prices[2];

}



void Company::mortgage(bool IsBeingMortgaged)
{
    if (IsBeingMortgaged){
        m_Mortgaged = true;
    }
    else
        m_Mortgaged = false;
}



int Company::getPrice()
{
    return m_Prices[0];
}

int Company::getRent(const int &AmountOwned, const int &DiceRollAmount)
{
    const int ONE_OWNED_MULTIPLIER = 4;
    const int TWO_OWNED_MULTIPLIER = 10;

    if(AmountOwned == 1){
        return (ONE_OWNED_MULTIPLIER * DiceRollAmount);
    }
    else{
        return (TWO_OWNED_MULTIPLIER * DiceRollAmount);
    }
}
