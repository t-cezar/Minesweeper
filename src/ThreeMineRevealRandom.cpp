#include "../headers/ThreeMineRevealRandom.h"
#include <ostream>

ThreeMineRevealRandom::ThreeMineRevealRandom(int row, int col) : Powerup(row, col) {
    this->row = row;
    this->col = col;
}

ThreeMineRevealRandom::ThreeMineRevealRandom(const ThreeMineRevealRandom& other) : Powerup(other) {}

void ThreeMineRevealRandom::activate(std::vector<std::vector<Cell>>& gridCells) const {
    int maxFlags = 3;
    int nr = 0;

    // numar cate bombe pot fi flagged
    int minesAvailable = 0;
    for (const auto& gridRow : gridCells) {
        for (const auto& cell : gridRow) {
            if (!cell.isRevealed() && cell.isMine() && !cell.isFlagged()) {
                minesAvailable++;
            }
        }
    }

    maxFlags = std::min(maxFlags, minesAvailable);
    while (nr < maxFlags) {
        int randomRow = generateRandom(0, static_cast<int>(gridCells.size()) - 1);
        int randomCol = generateRandom(0, static_cast<int>(gridCells[0].size()) - 1);

        Cell& cell = gridCells[randomRow][randomCol];
        if (!cell.isRevealed() && cell.isMine() && !cell.isFlagged()) {
            cell.flagCellToggle();
            nr++;
        }
    }
}

void ThreeMineRevealRandom::print(std::ostream& os) const {
    os << "ThreeMineRevealRandom Powerup la (row: " << this->row << ", col: " << this->col << ")";
}

std::shared_ptr<Powerup> ThreeMineRevealRandom::clone() const {
    return std::make_shared<ThreeMineRevealRandom>(*this);
}

ThreeMineRevealRandom& ThreeMineRevealRandom::operator=(const ThreeMineRevealRandom& other) {
    if (this != &other) {
        Powerup::operator=(other);
    }
    return *this;
}
