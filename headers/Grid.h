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

public:
    Grid(int rows, int cols, int mines);

    [[nodiscard]]const Cell& getCell(const int& row, const int& col) const;
    void generateMines();
    void withinGrid(int row, int col, void (Cell::*fCell)());
    void flagCell(int row, int col);
    void revealCell(int row, int col);
    static int randomNr(int low, int high);
    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

#endif //GRID_H
