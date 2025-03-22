#include "tile.h"

Tile::Tile() {}

Tile::Tile(bool canBeBought)
{
    m_CanBeBought = canBeBought; //Changes the state of a tile on whether it can be bought or not (Actions tiles aren't buyable for example)
}

void Tile::addToken(Figure *Token)
{
    m_Tokens.append(Token);  //If a player with a certain token has stepped on a tile, the player will be added as "a member of the tile".
}

int Tile::getPrice()
{
    return m_Price;
}

int Tile::getMortgageValue(bool What)
{
    return 0;
}

void Tile::mortgage(bool IsBeingMortgaged) {}


void Tile::removeToken(const Figure* Token)
{
    //If a player with a certain token moves from one tile to another, the player will be removed from the original tile.
    int amountTokensOnTile = m_Tokens.size();
    if (amountTokensOnTile < 0){
        qDebug() << "Tile does not contain any Tokens";
        return;
    }
    else
        m_Tokens.removeOne(Token);
}


void Tile::setOwner(const Figure Owner)
{
    //Street, Station and Company tiles could possibly get owners.
    m_Owner = Owner;
    m_CanBeBought = false;
}

void Tile::removeOwner()
{

    //If an owner is in debt for example, he won't be the owner of the street, station or utility anymore.
    m_Owner = Figure::NONE;
    m_CanBeBought = true;
}

Figure Tile::getOwner(){
    return m_Owner;
}

bool Tile::isBuyable()
{
    return m_CanBeBought;
}

bool Tile::hasOwner()
{
    return m_Owner != Figure::NONE;
}

bool Tile::isMortgaged()
{
    return false;
}
