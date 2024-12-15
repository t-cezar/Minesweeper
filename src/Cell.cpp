#include "../headers/Cell.h"

Cell::Cell()
    : mine(false),
      revealed(false),
      flagged(false),
      redMine(false) {}

Cell::Cell(const Cell &other)
    : mine(other.mine),
      revealed(other.revealed),
      flagged(other.flagged),
      redMine(other.redMine) {}

Cell::~Cell() = default;

void Cell::setMine() {
    mine = true;
}

void Cell::setRedMine() {
    redMine = true;
}

void Cell::revealCellToggle() {
    revealed = !revealed;
}

void Cell::flagCellToggle() {
    flagged = !flagged;
}

bool Cell::isMine() const {
    return mine;
}

bool Cell::isRedMine() const {
    return redMine;
}

bool Cell::isRevealed() const {
    return revealed;
}

bool Cell::isFlagged() const {
    return flagged;
}

Cell &Cell::operator=(const Cell &other) {
    if (this != &other) {
        mine = other.mine;
        revealed = other.revealed;
        flagged = other.flagged;
    }
    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Cell &cell) {
    if (cell.isFlagged()) {
        stream << "F";
    } else if (cell.isRevealed()) {
        stream << "R";
    } else if (cell.isMine()) {
        stream << "x";
    } else {
        stream << "o";
    }
    return stream;
}
