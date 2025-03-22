//Author: Kumas Atakan
#ifndef ACTION_H
#define ACTION_H

#include "tile.h"

class Action : public Tile
{
public:
    enum class ActionType{ START, CHANCE, COMMUNITYCHEST, PARKING, GOTOPRISON, INCOMETAX, SUPERTAX };

    //Constructor:
    Action(QJsonValue ActionInfo);

    //Method:
    //Returns the actiontype (START, CHANCE, COMMUNITYCHEST, PARKING, GOTOPRISON, INCOMETAX, SUPERTAX)
    ActionType getActionType();

    //Method:
    //If the action is a START, INCOMETAX or SUPERTAX, it can possibly get a value.
    int getPrice() override;

    int getMortgageValue(bool What) override; //Empty function Used for making class Tile polymorphic and effective for dynamic casting;
    void mortgage(bool IsBeingMortgaged) override; //Empty function Used for making class Tile polymorphic and effective for dynamic casting;
    bool isMortgaged() override; //Empty function Used for making class Tile polymorphic and effective for dynamic casting;

private:
    ActionType findActionType(QString Type);
    ActionType m_Action{ActionType::CHANCE};
    int m_Payment = 0;
};

#endif // ACTION_H
