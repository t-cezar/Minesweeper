#include "../headers/Grid.h"
#include <random>

Grid::Grid(int size, int mines) : gridSize(size), nrMines(mines), grid(size, std::vector<Cell>(size)) {}

void Grid::generateMines(std::mt19937& seed){
    int mineCount = 0;
    std::uniform_int_distribution<int> distrib(0, gridSize * gridSize - 1);

    while (mineCount < nrMines) {
        int randomPos = distrib(seed);
        int x = randomPos / gridSize;
        int y = randomPos % gridSize;

        if (!grid[x][y].isMine()) {
            grid[x][y].setMine();
            mineCount++;
        }
    }
}

void Grid::generateGame() {
    std::random_device rd;
    std::mt19937 gen(rd());
    generateMines(gen);
}

const Cell& Grid::getCell(const int& row, const int& col) const{
    return grid[row][col];
}

void Grid::revealCell(int x, int y) {
    if (x >= 0 && x < gridSize && y >= 0 && y < gridSize) {
        grid[x][y].revealCell();
    }
}

std::ostream& operator<<(std::ostream& stream, const Grid& gameGrid) {
    for (int row = 0; row < gameGrid.gridSize; row++) {
        for (int col = 0; col < gameGrid.gridSize; col++) {
            stream << gameGrid.grid[row][col] << " ";
        }
        stream << "\n";
    }
    return stream;
}