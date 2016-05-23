#ifndef CELL_H
#define CELL_H
#include <QPair>
#include <QPushButton>
#include "libtic.h"

class Cell : public QPushButton
{

public:
    Cell(QWidget *parent=0);
    Tic::XOStates state;
    QPair<int,int> index;
};

#endif // CELL_H
