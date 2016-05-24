#include "humanplayer.h"

HumanPlayer::HumanPlayer(QString name, XOStates token):Player(name, token)
{

}

bool HumanPlayer::isHuman() {
    return true;
}

QPair<int, int> HumanPlayer::computeTurn(Board *board) {
    return QPair<int, int>(1,1);
}