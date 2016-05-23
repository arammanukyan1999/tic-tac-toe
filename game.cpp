#include "game.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "computerplayer.h"
#include "humanplayer.h"
#include <QMessageBox>

Game::Game(QWidget *parent) : QWidget(parent),currentState(XOStates::X)
{

    playerSelectDialog = new PlayerSelectDialog;
    playersNameDialog = NULL;

    connect(playerSelectDialog,SIGNAL(selectPlayers(int)),this, SLOT(selectNames(int)));

}
void Game::onBoardCellClick(QPair<int,int> index) {
    if (!this->isStarted) return;
    if (gameBoard->isCellEmpty(index)){
        turn(index);
    }
}

void Game::start() {
    this->playerSelectDialog->show();
}

void Game::selectNames(int count) {
    playerSelectDialog->close();
    if (playersNameDialog != NULL)
    {
        delete playersNameDialog;
    }
    playersNameDialog = new PlayersNameDialog(count);
    playersNameDialog->show();
    connect(playersNameDialog, &PlayersNameDialog::cancelClick,[this](){this->playersNameDialog->close();});
    connect(playersNameDialog, &PlayersNameDialog::okClick, this, &Game::startGame);
}

void Game::startGame(Tic::GameData *data) {
    QHBoxLayout *mainLayout = new QHBoxLayout;
    QVBoxLayout *rightLayout = new QVBoxLayout,
                *leftLayout = new QVBoxLayout;


    gameBoard = new Board(data->width,data->height);
    this->width = data->width;
    this->height = data->height;
    this->winCount = data->winSize;
    this->playCount = 0;

    if (data->players) {
        if (data->players == 1) {
            this->XPlayer = new ComputerPlayer(data->XPalyerName, XOStates::X);
            this->OPlayer = new HumanPlayer(data->OPlayerName, XOStates::O);
        } else {
            this->XPlayer = new HumanPlayer(data->XPalyerName, XOStates::X);
            this->OPlayer = new ComputerPlayer(data->OPlayerName, XOStates::O);
        }
    } else {
        this->XPlayer = new HumanPlayer(data->XPalyerName, XOStates::X);
        this->OPlayer = new HumanPlayer(data->OPlayerName, XOStates::O);
    }

    leftLayout->addStretch();
    leftLayout->addWidget(gameBoard);
    leftLayout->addStretch();
    mainLayout->addLayout(leftLayout);

    mainLayout->addSpacing(20);

    rightLayout->addStretch();
    rightLayout->addWidget(new QLabel("Tic Tac Toe"));
    QLabel *players = new QLabel(data->XPalyerName + " vs " + data->OPlayerName);
    players->setStyleSheet("QLabel { color: red; }");
    rightLayout->addWidget(players);
    rightLayout->addStretch();

    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);

    connect(gameBoard,SIGNAL(cellClicked(QPair<int,int>)),this,SLOT(onBoardCellClick(QPair<int,int>)));
    this->currentPlayer = this->XPlayer;


    playersNameDialog->close();
    this->isStarted = true;
    this->show();
    this->setMaximumSize(this->geometry().width() + 100, this->geometry().height() + 100);
}

bool Game::checkWinner() {
    int count = 0;
    bool isWinner = false;
    XOStates player = this->currentState;
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            if (this->gameBoard->getCell(QPair<int,int>(row,column))->state == player && count < this->winCount)
                count++;
            else if(count == this->winCount){
                isWinner = true;
                break;
            }
            else{
                isWinner = false;
                count = 0;
            }
        }

        if(isWinner)
            break;

    }
    if (isWinner) {
        this->isStarted = false;
    }

    return isWinner;

}

void Game::nextTurn() {
    if (!this->currentPlayer->isHuman()) {
        return;
    }


}

void Game::turn(QPair<int, int> index) {
    playCount++;
    if (this->checkWinner()) return;
    qDebug()<<playCount;
    if (playCount == height * width) {
        this->isStarted = false;
       QMessageBox::information(0, "Draw", "Draw!");
    }
    gameBoard->setCellState(index,currentState);
    currentPlayer = currentState == XOStates::X ? OPlayer : XPlayer;
    currentState = currentState==XOStates::X ? XOStates::O:XOStates::X;
}
