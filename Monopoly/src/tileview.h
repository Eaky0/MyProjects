//Author: Kumas Atakan
#ifndef TILEVIEW_H
#define TILEVIEW_H

#include <QGraphicsItem>
#include <Qbrush>
#include <tokenview.h>

class TileView : public QGraphicsRectItem
{
public:
    TileView(int Width, int Height, int TileNumber);
    void setToken(TokenView * token);
private:

};

#endif // TILEVIEW_H
