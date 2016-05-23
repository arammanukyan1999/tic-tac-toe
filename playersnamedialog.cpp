#include "playersnamedialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "libtic.h"
#include <QDebug>

using Tic::Style_tweaks;

PlayersNameDialog::PlayersNameDialog(int playersCount, QWidget *parent):TickDialog(parent)
{
    name1 = new QLineEdit;
    name2 = new QLineEdit;

    height = new QSpinBox;
    width = new QSpinBox;
    winSize = new QSpinBox;

    ok = new QPushButton("Ok");
    cancel = new QPushButton("Cancel");
    connect(ok, SIGNAL(clicked(bool)), this, SLOT(clickOk()));
    connect(cancel, SIGNAL(clicked(bool)), this, SIGNAL(cancelClick()));

    ok->installEventFilter(this);
    cancel->installEventFilter(this);

    QString blueColor = "QPushButton {color: red; }";
    ok->setStyleSheet(blueColor);
    cancel->setStyleSheet(blueColor);

    QLabel *l1 = new QLabel("X player");
    QLabel *l2 = new QLabel("O player");

    QLabel *wl = new QLabel("Width: ");
    QLabel *hl = new QLabel("Height: ");
    QLabel *ws = new QLabel("Win length: ");

    QVBoxLayout *mainLayout = new QVBoxLayout;
    QVBoxLayout *nameLayout = new QVBoxLayout;
    QHBoxLayout *sizeLayout = new QHBoxLayout;
    QHBoxLayout *p1Layout = new QHBoxLayout;
    QHBoxLayout *p2Layout = new QHBoxLayout;
    QVBoxLayout *buttonArea = new QVBoxLayout;
    QHBoxLayout *buttonBox = new QHBoxLayout;

    this->playersCount = playersCount;

    if (playersCount == 1) {
        compX = new QRadioButton("Computer");
        compX->setStyle(new Style_tweaks());
        compO = new QRadioButton("Computer");
        compO->setStyle(new Style_tweaks());
        connect(compX, &QRadioButton::pressed,[this]() {
            this->name1->setText("Computer");
            this->name1->setDisabled(true);
            this->name2->setText("");
            this->name2->setEnabled(true);
        });
        connect(compO, &QRadioButton::pressed,[this]() {
            this->name2->setText("Computer");
            this->name2->setDisabled(true);
            this->name1->setText("");
            this->name1->setEnabled(true);
        });
    }

    p1Layout->addWidget(l1);
    p1Layout->addWidget(name1);
    if (playersCount == 1) {
        p1Layout->addWidget(compX);
    }

    p2Layout->addWidget(l2);
    p2Layout->addWidget(name2);
    if (playersCount == 1) {
        p2Layout->addWidget(compO);
        compX->click();

    }

    nameLayout->addLayout(p1Layout);
    nameLayout->addLayout(p2Layout);

    height->setRange(3, 15);
    width->setRange(3,15);
    winSize->setRange(3,5);

    sizeLayout->addWidget(hl);
    sizeLayout->addWidget(height);
    sizeLayout->addSpacing(15);
    sizeLayout->addWidget(wl);
    sizeLayout->addWidget(width);
    sizeLayout->addWidget(ws);
    sizeLayout->addWidget(winSize);

    buttonBox->addWidget(ok);
    buttonBox->addWidget(cancel);

    buttonArea->addLayout(buttonBox);

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(sizeLayout);
    mainLayout->addLayout(buttonArea);

    this->setFixedSize(400,400);
    this->setLayout(mainLayout);
}

bool PlayersNameDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == (QObject*)ok || obj == (QObject*)cancel) {
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
void PlayersNameDialog::clickOk() {
    using namespace Tic;

    if (name1->text().trimmed() == "" || name2->text().trimmed() == "") {
        return;
    }

    GameData *data= new GameData;

    data->height = height->value();
    data->width = width->value();
    data->winSize = winSize->value();
    data->XPalyerName = name1->text();
    data->OPlayerName = name2->text();

    if (this->playersCount == 1) {
        data->players = compX->isChecked() ? 1 : 2;
    } else {
        data ->players = 0;
    }
    emit okClick(data);
}
