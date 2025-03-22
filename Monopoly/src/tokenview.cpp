#include "tokenview.h"

TokenView::TokenView(int PlayerNumber, QString Tokentype) : m_PlayerNumber {PlayerNumber}
{
    QString image(":/board.bile.images/");
    image += Tokentype;
    image += "Token2.png";
    QPixmap bgPixmap(image);

    setPixmap(bgPixmap);
}

int TokenView::getPlayer()
{
    return m_PlayerNumber;
}
