#include "playerselectdialog.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>
#include <QEvent>

PlayerSelectDialog::PlayerSelectDialog(QWidget *parent):TickDialog(parent)
{
    onePlayer = new QPushButton("1 Player");
    twoPlayer = new QPushButton("2 Player");

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(onePlayer);
    layout->addWidget(twoPlayer);

    this->setLayout(layout);

    onePlayer->installEventFilter(this);
    twoPlayer->installEventFilter(this);

    connect(onePlayer,SIGNAL(clicked(bool)),SLOT(playersSelected()));
    connect(twoPlayer,SIGNAL(clicked(bool)),SLOT(playersSelected()));

    this->setFixedSize(300,200);
}

bool PlayerSelectDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == (QObject*)onePlayer || obj == (QObject*)twoPlayer) {
        if (event->type() == QEvent::Enter)
        {
            this->setCursor(Qt::PointingHandCursor);
        }else if (event->type() == QEvent::Leave)
           {
            this->setCursor(Qt::ArrowCursor);
        }
        return false;
    }else {
        return QWidget::eventFilter(obj, event);
    }
}

void PlayerSelectDialog::playersSelected() {
    if (sender() == (QObject *)onePlayer)
    {
        emit this->selectPlayers(1);
    }
    else
    {
        emit this->selectPlayers(2);
    }
}

