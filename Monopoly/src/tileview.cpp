#include "tileview.h"

TileView::TileView(int Width, int Height, int TileNumber) {


    setBrush(QColor(205, 255, 220));
    setRect(0, 0, Width, Height);
}


void TileView::setToken(TokenView * token){
    token->setParentItem(this);
    token->setPos(15, 20);
}


