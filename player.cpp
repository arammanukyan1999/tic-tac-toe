#include "player.h"

Player::Player(QString name, XOStates token):name(name),token(token)
{
    if (token == XOStates::Empty) {
        throw "Player token can't be empty";
    }
}

