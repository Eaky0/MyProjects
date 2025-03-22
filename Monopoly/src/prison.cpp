
#include "prison.h"

Prison::Prison()
{

}

void Prison::addToken(Token *p1, bool prisoner)
{
    if (prisoner){
        m_Prisoners.append(p1);
    }
    else
        Tile::addToken(p1);
}

