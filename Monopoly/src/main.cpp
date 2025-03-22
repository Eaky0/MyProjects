#include "gameview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameView w;
    w.showFullScreen();
    return a.exec();
}
