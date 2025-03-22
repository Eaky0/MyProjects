//Author : Kumas Atakan
#ifndef TOKENVIEW_H
#define TOKENVIEW_H

#include <QGraphicsPixmapItem>
#include <QString>
class TokenView : public QGraphicsPixmapItem
{
public:
    TokenView(int PlayerNumber, QString Tokentype);
    int getPlayer();


private:
    int m_PlayerNumber;
};

#endif // TOKENVIEW_H
