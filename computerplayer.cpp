#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(QString name, XOStates token):Player(name, token)
{

}

bool ComputerPlayer::isHuman() {
    return false;
}
