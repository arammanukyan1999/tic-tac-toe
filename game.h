#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
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
    QHBoxLayout *mainLayout;
    QVBoxLayout *boardLayout;
    int playCount;
    PlayerSelectDialog* playerSelectDialog;
    PlayersNameDialog*  playersNameDialog;
    int width;
    int height;
    int winCount;
    bool isStarted;
    QString currentStateName();
    void updateName();
    QLabel *cpName;
    Tic::GameData *data;

public:
    explicit Game(QWidget *parent = 0);
    void start();
    void startGame(Tic::GameData*);

signals:
    void newGame();

public slots:
    void onBoardCellClick(QPair<int,int>);
    void selectNames(int);
    bool checkWinner(QPair<int, int>);
    void nextTurn();
    void turn(QPair<int,int>);
};

#endif // GAME_H
