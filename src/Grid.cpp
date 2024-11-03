#include "../headers/Grid.h"
#include <random>

Grid::Grid(int size, int mines) : gridSize(size), nrMines(mines), grid(size, std::vector<Cell>(size)) {}

void Grid::generateMines(std::mt19937& seed){
    int mineCount = 0;
    std::uniform_int_distribution<int> distrib(0, gridSize * gridSize - 1);

    while (mineCount < nrMines) {
        int randomPos = distrib(seed);
        int row = randomPos / gridSize;
        int col = randomPos % gridSize;

        if (!grid[row][col].isMine()) {
            grid[row][col].setMine();
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

void Grid::flagCell(int row, int col) {
    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
        grid[row][col].flagCell();
    }
}

void Grid::revealCell(int row, int col) {
    if (row >= 0 && row < gridSize && col >= 0 && col < gridSize) {
        grid[row][col].revealCell();
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