#ifndef GRID_H
#define GRID_H

#include <vector>
#include <random>
#include "Cell.h"

class Grid {
    int rows;
    int cols;
    int nrMines;
    std::vector<std::vector<Cell>> grid;

    void generateMines();
    void withinGrid(int row, int col, void (Cell::*fCell)());
    static int randomNr(int low, int high);

public:
    Grid(int rows, int cols, int mines);

    [[nodiscard]]int getNrMinesAroundCell(int row, int col) const;
    [[nodiscard]]const Cell& getCell(const int& row, const int& col) const;
    void flagCell(int row, int col);
    void revealCell(int row, int col);
    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

#endif
