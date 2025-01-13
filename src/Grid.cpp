#include "../headers/Grid.h"
#include "../headers/MineRevealRandom.h"
#include "../headers/RevealAreaRandom.h"
#include "../headers/RevealWrongFlags.h"
#include <queue>
#include <set>
#include <ranges>
#include <algorithm>

#include <iostream>

Grid::Grid(int rows, int cols, int mines)
    : rows(rows),
      cols(cols),
      nrMines(mines),
      grid(rows, std::vector<Cell>(cols)),
      firstPowerupCloned(false) {
    generateMines();
    generatePowerups();
}

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

void Grid::makeRedMine(int row, int col) {
    withinGrid(row, col, &Cell::setRedMine);
}

int Grid::aroundCell(int row, int col, bool (Cell::*fCell)() const) const {
    int count = 0;
    for (int i = 0; i < 8; i++) {
        int checkedRow = row + dx[i];
        int checkedCol = col + dy[i];

        if (checkedRow >= 0 && checkedRow < rows && checkedCol >= 0 && checkedCol < cols) {
            if ((grid[checkedRow][checkedCol].*fCell)()) count++;
        }
    }
    return count;
}

int Grid::minesCount(int row, int col) const {
    return aroundCell(row, col, &Cell::isMine);
}

int Grid::flagsCount(int row, int col) const {
    return aroundCell(row, col, &Cell::isFlagged);
}

void Grid::revealEmptyCells(int row, int col) {//consider empty acea celula care nu are deloc mine in jurul ei
    if (row < 0 || row >= rows || col < 0 || col >= cols || grid[row][col].isMine()) {
        return;
    }
    std::queue<std::pair<int, int> > queue;
    std::set<std::pair<int, int> > visited; //ma asigur ca nu verific o celula de mai multe ori
    queue.emplace(row, col);

    while (!queue.empty()) {
        std::pair<int, int> current = queue.front();
        queue.pop();
        int currentRow = current.first;
        int currentCol = current.second;
        if (visited.contains(current)) continue;
        visited.insert(current);
        if (!grid[currentRow][currentCol].isRevealed()) {
            grid[currentRow][currentCol].revealCellToggle();
        }
        if (minesCount(currentRow, currentCol) != 0) {
            continue;
        }
        for (int i = 0; i < 8; i++) {
            int newRow = currentRow + dx[i];
            int newCol = currentCol + dy[i];

            if (newRow >= 0 && newRow < rows && newCol >= 0 && newCol < cols &&
                !visited.contains({newRow, newCol}) && !grid[newRow][newCol].isMine()) {
                queue.emplace(newRow, newCol);
            }
        }
    }
}

int Grid::revealAroundCell(int row, int col) {
    int flaggedCells = flagsCount(row, col);
    int mineCells = minesCount(row, col);

    if (flaggedCells == mineCells) {
        int correctFlags = 0;
        for (int i = 0; i < 8; i++) {
            int checkedRow = row + dx[i];
            int checkedCol = col + dy[i];

            if (checkedRow >= 0 && checkedRow < rows && checkedCol >= 0 && checkedCol < cols) {
                if (grid[checkedRow][checkedCol].isFlagged() && grid[checkedRow][checkedCol].isMine()) {
                    correctFlags++;
                } else {
                    makeRedMine(checkedRow, checkedCol);
                }
                if (!grid[checkedRow][checkedCol].isRevealed() && !grid[checkedRow][checkedCol].isFlagged()) {
                    revealCell(checkedRow, checkedCol);
                    if (minesCount(checkedRow, checkedCol) == 0)
                        revealEmptyCells(checkedRow, checkedCol);
                }
            }
        }
        if (correctFlags != mineCells) {std::cout<< "\n"<<correctFlags<< " "<< mineCells;
            return true;

        }
    }

    return false;
}

void Grid::revealAllMines() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (!grid[row][col].isRevealed() && grid[row][col].isMine() && !grid[row][col].isFlagged()) {
                grid[row][col].revealCellToggle();
            }
        }
    }
}

void Grid::markedEmptyReveal() {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (!grid[row][col].isMine() && grid[row][col].isMarked()
                && minesCount(row, col) == 0 && grid[row][col].isRevealed()) {
                revealEmptyCells(row, col);
                }
        }
    }
}

int Grid::randomNr(int low, int high) {
    static std::random_device rd;
    static std::default_random_engine gen(rd());
    using Dist = std::uniform_int_distribution<int>;
    static Dist uid {};
    return uid(gen, Dist::param_type{low, high});
}

void Grid::generatePowerups() {
    powerups.clear();
    for (int i = 0; i < 3; ++i) {
        int row, col;

        do {
            row = randomNr(0, rows - 1);
            col = randomNr(0, cols - 1);
        } while (grid[row][col].isRevealed() || grid[row][col].isMine() || hasPowerup(row, col));

        int type = randomNr(0, 2);
        std::shared_ptr<Powerup> powerup;
        if (type == 0) {
            powerup = std::make_shared<MineRevealRandom>(row, col);
        } else if (type == 1) {
            powerup = std::make_shared<RevealAreaRandom>(row, col);
        } else {
            powerup = std::make_shared<RevealWrongFlags>(row, col);
        }
        powerups.push_back(std::move(powerup));
    }

    if (dynamic_cast<RevealAreaRandom*>(powerups[1].get()) &&
        dynamic_cast<MineRevealRandom*>(powerups[2].get())) {
        std::swap(powerups[1], powerups[2]);
        }
}

bool Grid::hasPowerup(int row, int col) const {
    return std::ranges::any_of(powerups, [row, col](const auto& powerup) {
        return powerup->getRow() == row && powerup->getCol() == col;
    });
}

void Grid::activatePowerup(int row, int col) {
    for (auto it = powerups.begin(); it != powerups.end(); ++it) {
        if ((*it)->getRow() == row && (*it)->getCol() == col) {
            (*it)->activate(grid);
            if (!firstPowerupCloned) {
                auto clonedPowerup = (*it)->clone();

                int newRow, newCol;
                do {
                    newRow = randomNr(0, rows - 1);
                    newCol = randomNr(0, cols - 1);
                } while (grid[newRow][newCol].isRevealed() || grid[newRow][newCol].isMine() || hasPowerup(newRow, newCol));

                clonedPowerup->setCoordinates(newRow, newCol);
                powerups.push_back(clonedPowerup);
                firstPowerupCloned = true;
            }
            powerups.erase(it);
            return;
        }
    }
}


std::ostream& operator<<(std::ostream& os, const Grid& grid) {
    for (const auto& row : grid.grid) {
        for (const auto& cell : row) {
            os << cell << " ";
        }
        os << "\n";
    }

    os << "\nPower-ups:\n";
    for (const auto& powerup : grid.powerups) {
        powerup->print(os);
        os << "\n";
    }
    return os;
}
