//Author: Alessio
#ifndef TOKEN_H
#define TOKEN_H
#include "figure.h"

class Token
{
public:
    Token(Figure playerFigure);
    Figure getFigure();
private:
    Figure m_Figure;
};

#endif // TOKEN_H
