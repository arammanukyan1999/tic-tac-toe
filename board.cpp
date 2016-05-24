#include "board.h"
#include <QLayout>
#include <QDebug>
#include <QVector>
#include <QFile>
#include "libtic.h"
#include "cell.h"
#include <QPair>

using namespace Tic;

Board::Board(int n,int m, QWidget *parent) : QWidget(parent)
{

    for(int i=0;i<m;i++){
        cells.push_back(QVector<Cell*>());
    }
    QGridLayout *boardLayout = new QGridLayout();
    boardLayout->setSpacing(0);
    boardLayout->setMargin(0);

    this->setLayout(boardLayout);
    QFile file(":/styles/boardstyle.qss");
    file.open(QFile::ReadOnly);
    QString boardStyles = QLatin1String(file.readAll());
    this->setStyleSheet(boardStyles);
    this->setStyle(new Style_tweaks);
    for(int i=0; i<m; ++i)
        for(int j=0; j<n; ++j)
        {
            cells[i].push_back(new Cell);
            cells[i][j]->setMinimumSize(50,50);
            cells[i][j]->state = XOStates::Empty;
            cells[i][j]->index.first = i;
            cells[i][j]->index.second = j;
            boardLayout->addWidget(cells[i][j],i,j);

            connect(cells[i][j],SIGNAL(clicked(bool)),this,SLOT(onCellClick()));
        }
    this->height = n;
    this->width = m;        

}
void Board::onCellClick(){
    Cell *cell = (Cell*)(sender());
    emit cellClicked(cell->index);
}

void Board::setCellState(QPair<int,int> index,XOStates state) {
    switch (state) {
    case X:
        getCell(index)->setText("X");
        getCell(index)->setStyleSheet("QPushButton { color: red; }");
        getCell(index)->state=XOStates::X;
        break;
    case O:
        getCell(index)->setText("O");
        getCell(index)->setStyleSheet("QPushButton { color: blue; }");
        getCell(index)->state=XOStates::O;
        break;
    }
}

Cell *Board::getCell(QPair<int,int> index) {
    return this->cells[index.first][index.second];
}

bool Board::isCellEmpty(QPair<int,int> index) {
    return getCell(index)->state==XOStates::Empty;
}

QVector<QVector<Cell *>>* Board::getCellboard() {
    return &this->cells;
}


