#include "mainwindow.h"
#include "tickdialog.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include "board.h"
#include "game.h"
#include "playerselectdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game *g = new Game;

    g->start();
    return a.exec();
}

