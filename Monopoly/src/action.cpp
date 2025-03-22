#include "action.h"

Action::Action(QJsonValue ActionInfo) : Tile{false}
{
    //Initializes all members according to a JSON file which contains information about the the tiles.
    QString type = ActionInfo["actiontype"].toString();
    m_Action = findActionType(type);

    //If the action is START, INCOME TAX, or SUPERTAX it contains a certain value to pay or recieve.
    if (m_Action == ActionType::START || m_Action == ActionType::INCOMETAX || m_Action == ActionType::SUPERTAX){
        m_Payment = ActionInfo["payment"].toInt();
    }
}

int Action::getPrice()
{
    return m_Payment;
}

//Needed for Polymorphism and virtual methods (Action tiles can't be mortgaged obviously):
int Action::getMortgageValue(bool What)
{
    return 0;
}

void Action::mortgage(bool IsBeingMortgaged) {}

bool Action::isMortgaged()
{
    return false;
}

Action::ActionType Action::getActionType()
{
    return m_Action;
}

Action::ActionType Action::findActionType(QString Type)
{
    //Returns the type of action, according to what is written on the JSON file containing information about all tiles, for this action tile.
    if (Type == "Chance") return ActionType::CHANCE;
    else if (Type == "Start") return ActionType::START;
    else if (Type == "Community Chest") return ActionType::COMMUNITYCHEST;
    else if (Type == "Parking") return ActionType::PARKING;
    else if(Type == "Income Tax") return ActionType::INCOMETAX;
    else if (Type == "Super Tax") return ActionType::SUPERTAX;
    else return ActionType::GOTOPRISON;

}

