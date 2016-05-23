#ifndef PLAYERSNAMEDIALOG_H
#define PLAYERSNAMEDIALOG_H
#include <QLineEdit>
#include <QObject>
#include <QSpinBox>
#include <QPushButton>
#include <QRadioButton>
#include "tickdialog.h"
#include <QEvent>
#include "libtic.h"

class PlayersNameDialog : public TickDialog
{
    Q_OBJECT
    QLineEdit *name1;
    QLineEdit *name2;
    QSpinBox *height;
    QSpinBox *width;
    QSpinBox *winSize;
    QPushButton *ok;
    QPushButton *cancel;
    QRadioButton *compX;
    QRadioButton *compO;
    int playersCount;
private slots:
    void clickOk();
public:
    bool eventFilter(QObject *obj, QEvent *event);
    PlayersNameDialog(int,QWidget* parent=0);
signals:
    void okClick(Tic::GameData*);
    void cancelClick();
};

#endif // PLAYERSNAMEDIALOG_H
