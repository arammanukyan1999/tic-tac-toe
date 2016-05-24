#ifndef COMPUTERPLAYER_H
#define COMPUTERPLAYER_H
#include "player.h"


class ComputerPlayer : public Player
{
public:
    ComputerPlayer(QString="Computer", XOStates=XOStates::X);
    bool isHuman();
    QPair<int, int> computeTurn(Board*);
};

#endif // COMPUTERPLAYER_H
