//Author: Ieracitano Alessio, Kumas Atakan
//---------------------
//Methods made by Atakan:
//Tile, Tile(bool), addToken, removeToken, isMortgaged, mortgage, getMortgageValue
//---------------------
//Methods made by Alessio:
//setOwner, removeOwner, getPrice, getOwner, setOwner, hasOwner, isBuyable
//---------------------
#ifndef TILE_H
#define TILE_H

#include "figure.h"
#include <QDebug>
#include <array>

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>
#include <QIODevice>
#include <QStringLiteral>

class Tile
{
public:

    //Constructors:
    Tile();
    Tile(bool canBeBought);

    //Method:
    //Adds an addres of an figure to the QList m_Tokens
    void addToken(Figure* Token);

    //Method:
    //Removes the addres of an figrue in the QList m_Tokens
    void removeToken(const Figure* Token);

    //Method:
    //Sets the owner of the tile
    void setOwner(const Figure Owner);

    //Method:
    //resets the owner to None, and makes the tile buyable.
    void removeOwner();

    //Method
    //Returns the price of the tile
    virtual int getPrice();

    //Method:
    //Returns an Figure of the owner (Figure::NONE if no owner)
    Figure getOwner();

    //Method:
    //Returns yes if the tile is buyable else false
    bool isBuyable();

    //Method:
    //Returns an boolean true if it has an owner else false
    bool hasOwner();

    //Method:
    //Returns the mortgage value depending on whether its a mortgage take out or -pay off on some property.
    virtual int getMortgageValue(bool What);

    //Method:
    //Returns a boolean expression to determine whether a property is mortgaged or not.
    virtual bool isMortgaged();

    //Method:
    //Sets the mortgage state.
    virtual void mortgage(bool IsBeingMortgaged);

private:

    //Members
    bool m_CanBeBought{false};
    int m_Price{0};
    Figure m_Owner{Figure::NONE};    //set figure back to NONE!
    QList<Figure*> m_Tokens;
};

#endif // TILE_H
