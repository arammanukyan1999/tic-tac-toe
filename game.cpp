#include "game.h"
#include <QLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>
#include "computerplayer.h"
#include "humanplayer.h"
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>


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
                
    this->mainLayout = mainLayout;                


    gameBoard = new Board(data->width,data->height);
    this->data = data;
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
    
    this->boardLayout = leftLayout;
    this->boardLayout->setSizeConstraint(QLayout::SetFixedSize);
    
    mainLayout->addLayout(this->boardLayout);

    mainLayout->addSpacing(20);

    rightLayout->addStretch();
    rightLayout->addWidget(new QLabel("Tic Tac Toe"));
    QLabel *players = new QLabel("Players: " + data->XPalyerName + " vs " + data->OPlayerName);
    players->setStyleSheet("QLabel { color: red; }");
    
    QHBoxLayout *cpLayout = new QHBoxLayout;
    QLabel *cp = new QLabel("Playing: ");
    cpLayout->addWidget(cp);
    
    QLabel *cpName = new QLabel("");
    cpLayout->addWidget(cpName);
    this->cpName = cpName;
    
    rightLayout->addWidget(players);
    rightLayout->addLayout(cpLayout);
    rightLayout->addStretch();
    
    QPushButton *startAgain = new QPushButton("Start again");
    connect(startAgain, &QPushButton::clicked, [this](){
        delete this->gameBoard;
        this->gameBoard = new Board(this->data->width,this->data->height);
        this->boardLayout->insertWidget(this->boardLayout->count() - 1, this->gameBoard);
        this->currentPlayer = this->XPlayer;
        this->currentState = XOStates::X;
        updateName();
        this->playCount = 0;
        this->isStarted = true;
        this->nextTurn();
    });
    QPushButton *newGame = new QPushButton("New Game");
    connect(newGame, &QPushButton::clicked, [this](){
       emit this->newGame(); 
    });
    
    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->addWidget(startAgain);
    buttons->addWidget(newGame);

    rightLayout->addLayout(buttons);
    
    mainLayout->addLayout(rightLayout);

    this->setLayout(mainLayout);

    this->currentPlayer = this->XPlayer;
    updateName();


    playersNameDialog->close();
    this->isStarted = true;
    this->show();
    this->nextTurn();
    this->setMaximumSize(this->geometry().width() + 100, this->geometry().height() + 100);
    this->setGeometry(QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        this->size(),
        QApplication::desktop()->availableGeometry()));
    
}

bool Game::checkWinner(QPair<int, int> index) {
    int count = 0;
    int i;
    XOStates player = this->currentState;
    int col = index.second;
    
    // check column
    int k = 0;
    for (i = 0; i < this->height; i++) {
        if (this->gameBoard->getCell(QPair<int, int>(i, col))->state == player) k++; else k =0;
        if (k == this->winCount) return true;
    }
    
    // check row
    k = 0;
    int row = index.first;
    
    for (i = 0; i < this->height; i++) {
        if (this->gameBoard->getCell(QPair<int, int>(row, i))->state == player) k++; else k =0;
        if (k == this->winCount) return true;
    }
    
    // check diagonal
    k = 0;
    int min = qMin(row, col);
    i = row - min; int j = col - min;
    for (; i < this->height && j < this -> width; i++, j++) {
         if (this->gameBoard->getCell(QPair<int, int>(i, j))->state == player) k++; else k =0;
        if (k == this->winCount) return true;
    }
    
    
    // check anti diagonal
    k = 0;
    j = row + col > this->width - 1 ? this->width - 1 : row + col;
    i = row + col - j;
     for (; i < this->height && j >= 0; i++, j--) {
         if (this->gameBoard->getCell(QPair<int, int>(i, j))->state == player) k++; else k =0;
        if (k == this->winCount) return true;
    }
    
    return false;
}

void Game::nextTurn() {
    if (!this->currentPlayer->isHuman()) {
        disconnect(this->gameBoard,SIGNAL(cellClicked(QPair<int,int>)),this,SLOT(onBoardCellClick(QPair<int,int>)));
        this->turn(this->currentPlayer->computeTurn(this->gameBoard));
        return;
    } else {
        connect(this->gameBoard,SIGNAL(cellClicked(QPair<int,int>)),this,SLOT(onBoardCellClick(QPair<int,int>)));
    }
}

void Game::turn(QPair<int, int> index) {
    playCount++;
    gameBoard->setCellState(index,currentState);
    if (this->checkWinner(index)) {
        QMessageBox::information(0, "Win!", "The Winner is " + this->currentPlayer->name + " ( " + currentStateName() + " )!");
        this->isStarted = false;
        return;
    }
    if (playCount == height * width) {
        this->isStarted = false;
       QMessageBox::information(0, "Draw", "Draw!");
    }
    currentPlayer = currentState == XOStates::X ? OPlayer : XPlayer;
    currentState = currentState == XOStates::X ? XOStates::O : XOStates::X;
    updateName();
    this->nextTurn();
}

QString Game::currentStateName() {
    return this->currentState == XOStates::X ? "X" : "O";
}

void Game::updateName() {
    this->cpName->setText(this->currentPlayer->name + " ( "+currentStateName()+" )");
    this->cpName->setStyleSheet("QLabel { color: " + QString((this->currentState == XOStates::X ? "red" : "blue")) + "; }");
}