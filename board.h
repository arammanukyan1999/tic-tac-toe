#ifndef BOARD_H
#define BOARD_H
#include "libtic.h"
#include <QWidget>
#include <QPushButton>
#include <QVector>
#include "cell.h"

using Tic::XOStates;

class Board : public QWidget
{
    Q_OBJECT
private:
    QVector<QVector<Cell *>> cells;
public:
    explicit Board(int n=3,int m=3, QWidget *parent=0);
    bool isCellEmpty(QPair<int,int>);
    Cell *getCell(QPair<int,int>);
    QVector<QVector<Cell *>>* getCellboard();
    int height;
    int width;


signals:
    void cellClicked(QPair<int,int>);

public slots:
    void onCellClick();
    void setCellState(QPair<int,int>,XOStates);
};



#endif // BOARD_H
