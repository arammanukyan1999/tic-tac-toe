#include "humanplayer.h"

HumanPlayer::HumanPlayer(QString name, XOStates token):Player(name, token)
{

}

bool HumanPlayer::isHuman() {
    return true;
}
