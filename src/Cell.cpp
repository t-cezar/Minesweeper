//
// Created by cezar on 02/11/2024.
//

#include "../headers/Cell.h"

Cell::Cell():
mine(false), revealed(false), flagged(false) {}

Cell::~Cell() = default;

void Cell::setMine() {
    mine = true;
}
void Cell::revealCell() {
    revealed = true;
}
void Cell::flagCell() {
    flagged = true;
}
bool Cell::isMine() const{
    return mine;
}
bool Cell::isRevealed() const {
    return revealed;
}
bool Cell::isFlagged() const{
    return flagged;
}

std::ostream& operator<<(std::ostream& stream, const Cell& cell) {
    if (cell.isFlagged()) {
        stream << "F";
    } else if (cell.isMine()) {
        stream << "x";
    } else if (cell.isRevealed()) {
        stream << "R";
    } else {
        stream << "o";
    }
    return stream;
}
