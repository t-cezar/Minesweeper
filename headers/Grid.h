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
    const int dx[8] = {-1, -1, -1, 0, 1, 1, 1, 0};
    const int dy[8] = {-1, 0, 1, 1, 1, 0, -1, -1};

    void generateMines();
    void withinGrid(int row, int col, void (Cell::*fCell)());
    static int randomNr(int low, int high);
    [[nodiscard]]int aroundCell(int row, int col, bool (Cell::*fCell)() const) const;

public:
    Grid(int rows, int cols, int mines);

    [[nodiscard]]int minesCount(int row, int col) const;
    [[nodiscard]]int flagsCount(int row, int col) const;
    [[nodiscard]]const Cell& getCell(const int& row, const int& col) const;
    void flagCell(int row, int col);
    void revealCell(int row, int col);
    void makeRedMine(int row, int col);
    void revealEmptyCells(int row, int col);
    int revealAroundCell(int row, int col);
    void revealAllMines();

    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

#endif
