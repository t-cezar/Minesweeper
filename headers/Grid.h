#ifndef GRID_H
#define GRID_H

#include <vector>
#include <random>
#include "Cell.h"

class Grid {
private:
    int gridSize;
    int nrMines;
    std::vector<std::vector<Cell>> grid;

    void generateMines(std::mt19937& seed);

public:
    Grid(int size, int mines);

    [[nodiscard]]const Cell& getCell(const int& row, const int& col) const;
    void flagCell(int row, int col);
    void revealCell(int row, int col);
    void generateGame();

    friend std::ostream& operator<<(std::ostream& os, const Grid& grid);
};

#endif //GRID_H
