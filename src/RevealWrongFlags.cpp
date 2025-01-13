#include "../headers/RevealWrongFlags.h"
#include <ostream>

RevealWrongFlags::RevealWrongFlags(int row, int col) : Powerup(row, col) {
    this->row = row;
    this->col = col;
}


RevealWrongFlags::RevealWrongFlags(const RevealWrongFlags& other) : Powerup(other) {}

void RevealWrongFlags::activate(std::vector<std::vector<Cell>>& gridCells) const {
    for (auto& gridRow : gridCells) {
        for (auto& cell : gridRow) {
            if (cell.isFlagged() && !cell.isMine()) {
                cell.setMarked();
            }
        }
    }
}

void RevealWrongFlags::print(std::ostream& os) const {
    os << "RevealWrongFlags Powerup la (row: " << this->row << ", col: " << this->col << ")";
}

std::shared_ptr<Powerup> RevealWrongFlags::clone() const {
    return std::make_shared<RevealWrongFlags>(*this);
}

RevealWrongFlags& RevealWrongFlags::operator=(const RevealWrongFlags& other) {
    if (this != &other) {
        Powerup::operator=(other);
    }
    return *this;
}