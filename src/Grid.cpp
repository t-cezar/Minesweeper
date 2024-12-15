#include "../headers/Grid.h"

Grid::Grid(int rows, int cols, int mines)
    : rows(rows),
      cols(cols),
      nrMines(mines),
      grid(rows, std::vector<Cell>(cols)) { generateMines(); }

void Grid::generateMines() {
    int mineCount = 0;
    while (mineCount < nrMines) {
        int randomPos = randomNr(0, rows * cols - 1);
        int row = randomPos / cols;
        int col = randomPos % cols;

        if (!grid[row][col].isMine()) {
            grid[row][col].setMine();
            mineCount++;
        }
    }
}

const Cell& Grid::getCell(const int& row, const int& col) const{
    return grid[row][col];
}

void Grid::withinGrid(int row, int col, void (Cell::*fCell)()) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        (grid[row][col].*fCell)();
    }
}

void Grid::flagCell(int row, int col) {
    withinGrid(row, col, &Cell::flagCellToggle);
}

void Grid::revealCell(int row, int col) {
    withinGrid(row, col, &Cell::revealCellToggle);
}

int Grid::randomNr(int low, int high) {
    static std::random_device rd;
    static std::default_random_engine gen(rd());
    using Dist = std::uniform_int_distribution<int>;
    static Dist uid {};
    return uid(gen, Dist::param_type{low, high});
}

int Grid::getNrMinesAroundCell(int row, int col) const {
    constexpr int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0};
    constexpr int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int nrMines = 0;
    for (int i = 0; i < 8; i++) {
        int checkedRow = row + dx[i];
        int checkedCol = col + dy[i];

        if (checkedRow >= 0 && checkedRow < rows && checkedCol >= 0 && checkedCol < cols) {
            if (grid[checkedRow][checkedCol].isMine()) nrMines++;
        }
    }
    return nrMines;
}

std::ostream& operator<<(std::ostream& os, const Grid& grid) {
    for (int row = 0; row < grid.rows; row++) {
        for (int col = 0; col < grid.cols; col++) {
            os << grid.grid[row][col] << " ";
        }
        os << "\n";
    }
    return os;
}