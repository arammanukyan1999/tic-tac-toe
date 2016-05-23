#ifndef TICKDIALOG_H
#define TICKDIALOG_H

#include <QWidget>
#include <QPalette>

class TickDialog : public QWidget
{
    Q_OBJECT
private:
    QPalette *pal;
public:
    explicit TickDialog(QWidget *parent = 0);

signals:

public slots:
};

#endif // TICKDIALOG_H
