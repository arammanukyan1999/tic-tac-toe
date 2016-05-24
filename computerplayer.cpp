#include "computerplayer.h"
#include <QApplication>
#include <QThread>

ComputerPlayer::ComputerPlayer(QString name, XOStates token):Player(name, token)
{

}

bool ComputerPlayer::isHuman() {
    return false;
}

QPair<int, int> ComputerPlayer::computeTurn(Board *board) {
    QApplication::processEvents();
    if (board->isCellEmpty(QPair<int, int>(board->height/2, board->width/2))) return QPair<int, int>(board->height/2, board->width/2);
    QThread::msleep(500); 
    for (int i = 0; i < board->height; i++) 
        for (int j = 0; j < board->width; j++)
            if (board->isCellEmpty(QPair<int, int>(i, j))) return QPair<int, int>(i, j);
}