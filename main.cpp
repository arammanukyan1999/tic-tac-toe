#include "tickdialog.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QRadioButton>
#include <QObject>
#include "board.h"
#include "game.h"
#include "playerselectdialog.h"
#include <functional>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    Game *g = new Game;
    
    std::function<void (void)>  ng = [&]() {
        delete g;
        g = new Game();
        g->start();
        QObject::connect(g, &Game::newGame, ng);
    };
    QObject::connect(g, &Game::newGame, ng);
    g->start();
    return a.exec();
}

