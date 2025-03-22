//Author: Alessio
#include "token.h"

Token::Token(Figure playerFigure): m_Figure{playerFigure} {}

Figure Token::getFigure()
{
    return m_Figure;
}


