
#ifndef PRISON_H
#define PRISON_H

#include "tile.h"


class Prison  : public Tile
{
public:
    Prison();
    void addToken(Token* p1, bool prisoner);
    void removeToken(Token* p1, bool prisoner);
private:
    QList<Token*> m_Prisoners;
};

#endif // PRISON_H
