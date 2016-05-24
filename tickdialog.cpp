#include "tickdialog.h"
#include <QWidget>
#include <QPalette>
#include <QFile>
#include <QDebug>
#include "libtic.h"
#include <QStyle>
#include <QApplication>
#include <QDesktopWidget>

TickDialog::TickDialog(QWidget *parent) : QWidget(parent)
{
    pal = new QPalette();
    pal->setColor(QPalette::Background,Qt::white);
    this->setAutoFillBackground(true);
    this->setPalette(*pal);
    QFile file(":/styles/tickdialogstyle.qss");
    bool isOpened = file.open(QFile::ReadOnly);
    QString dStyle = QLatin1String(file.readAll());
    this->setStyleSheet(dStyle);
    this->setStyle(new Tic::Style_tweaks);

    this->setWindowFlags(Qt::Window | Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint);
    this->setGeometry(QStyle::alignedRect(
        Qt::LeftToRight,
        Qt::AlignCenter,
        this->size(),
        QApplication::desktop()->availableGeometry()));
}
