#include <QApplication>
#include "gomoku.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Gomoku game;
    game.show();
    return a.exec();
}
