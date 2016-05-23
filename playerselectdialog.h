#ifndef PLAYERSELECTDIALOG_H
#define PLAYERSELECTDIALOG_H
#include "tickdialog.h"
#include <QPushButton>
#include <QObject>

class PlayerSelectDialog : public TickDialog
{
    Q_OBJECT
    QPushButton *onePlayer;
    QPushButton *twoPlayer;
private slots:
    void playersSelected();
public:
    PlayerSelectDialog(QWidget *parent=0);
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void selectPlayers(int);
};

#endif // PLAYERSELECTDIALOG_H
