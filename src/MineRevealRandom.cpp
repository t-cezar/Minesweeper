#include "../headers/MineRevealRandom.h"
#include <ostream>

MineRevealRandom::MineRevealRandom(int row, int col) : Powerup(row, col) {}

MineRevealRandom::MineRevealRandom(const MineRevealRandom& other) : Powerup(other) {}

void MineRevealRandom::activate(std::vector<std::vector<Cell>>& gridCells) const {
    int checkedCells = 0;
    int sizeGrid = static_cast<int>(gridCells.size() * gridCells[0].size());

    while (checkedCells < sizeGrid) {
        int randomRow = generateRandom(0, static_cast<int>(gridCells.size()) - 1);
        int randomCol = generateRandom(0, static_cast<int>(gridCells[0].size()) - 1);

        Cell& cell = gridCells[randomRow][randomCol];
        if (!cell.isRevealed() && cell.isMine() && !cell.isFlagged()) {
            cell.flagCellToggle();
            return;
        }
        checkedCells++;
    }
}

void MineRevealRandom::print(std::ostream& os) const {
    os << "MineRevealRandom Powerup la (row: " << row << ", col: " << col << ")";
}

std::shared_ptr<Powerup> MineRevealRandom::clone() const {
    return std::make_shared<MineRevealRandom>(*this);
}

MineRevealRandom& MineRevealRandom::operator=(const MineRevealRandom& other) {
    if (this != &other) {
        Powerup::operator=(other);
    }
    return *this;
}