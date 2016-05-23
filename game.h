#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "libtic.h"
#include "board.h"
#include "player.h"
#include "playerselectdialog.h"
#include "playersnamedialog.h"

class Game : public QWidget
{
    Q_OBJECT
private:
    Board *gameBoard;
    Player *XPlayer;
    Player *OPlayer;
    XOStates currentState;
    Player *currentPlayer;
    int playCount;
    PlayerSelectDialog* playerSelectDialog;
    PlayersNameDialog*  playersNameDialog;
    int width;
    int height;
    int winCount;
    bool isStarted;

public:
    explicit Game(QWidget *parent = 0);
    void start();
    void startGame(Tic::GameData*);

signals:

public slots:
    void onBoardCellClick(QPair<int,int>);
    void selectNames(int);
    bool checkWinner();
    void nextTurn();
    void turn(QPair<int,int>);
};

#endif // GAME_H
