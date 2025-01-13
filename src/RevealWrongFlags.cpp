#include "../headers/RevealWrongFlags.h"
#include <ostream>

RevealWrongFlags::RevealWrongFlags(int row, int col) : Powerup(row, col) {}

RevealWrongFlags::RevealWrongFlags(const RevealWrongFlags& other) : Powerup(other) {}

void RevealWrongFlags::activate(std::vector<std::vector<Cell>>& gridCells) const {
    for (auto& row : gridCells) {
        for (auto& cell : row) {
            if (cell.isFlagged() && !cell.isMine()) {
                cell.setMarked();
            }
        }
    }
}

void RevealWrongFlags::print(std::ostream& os) const {
    os << "RevealWrongFlags Powerup la (row: " << row << ", col: " << col << ")";
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