#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"

class HumanPlayer : public Player
{
public:
    HumanPlayer(QString, XOStates);
    bool isHuman();
    QPair<int, int> computeTurn(Board*);
};

#endif // HUMANPLAYER_H
