#ifndef PLAYER_H
#define PLAYER_H
#include <QObject>
#include "libtic.h"

using Tic::XOStates;

class Player : public QObject
{
    Q_OBJECT
public:
    QString name;
    XOStates token;

public:
    explicit Player(QString="Computer",XOStates=XOStates::X);
    virtual bool isHuman() = 0;

signals:

public slots:
};


#endif // PLAYER_H
