#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(QString, XOStates);
    bool isHuman();
};

#endif // HUMANPLAYER_H
