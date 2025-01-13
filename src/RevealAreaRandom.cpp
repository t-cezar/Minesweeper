#include "../headers/RevealAreaRandom.h"
#include <ostream>

RevealAreaRandom::RevealAreaRandom(int row, int col) : Powerup(row, col) {
    this->row = row;
    this->col = col;
}

RevealAreaRandom::RevealAreaRandom(const RevealAreaRandom& other) : Powerup(other) {}

void RevealAreaRandom::activate(std::vector<std::vector<Cell>>& gridCells) const {
    while (true) {
        int randomRow = generateRandom(0, static_cast<int>(gridCells.size()) - 1);
        int randomCol = generateRandom(0, static_cast<int>(gridCells[0].size()) - 1);

        Cell& cell = gridCells[randomRow][randomCol];
        if (!cell.isRevealed() && !cell.isMine()) {
            cell.revealCellToggle();
            cell.setMarked();
            return;
        }
    }
}

void RevealAreaRandom::print(std::ostream& os) const {
    os << "RevealAreaRandom Powerup la (row: " << this->row << ", col: " << this->col << ")";
}

std::shared_ptr<Powerup> RevealAreaRandom::clone() const {
    return std::make_shared<RevealAreaRandom>(*this);
}

RevealAreaRandom& RevealAreaRandom::operator=(const RevealAreaRandom& other) {
    if (this != &other) {
        Powerup::operator=(other);
    }
    return *this;
}