#include "../headers/Powerup.h"
#include <random>
#include <utility>

Powerup::Powerup(int row, int col) : row(row), col(col) {}

Powerup& Powerup::operator=(const Powerup& other) {
    if (this != &other) {
        row = other.row;
        col = other.col;
    }
    return *this;
}

int Powerup::generateRandom(int low, int high) {
    static std::random_device rd;
    static std::default_random_engine gen(rd());
    std::uniform_int_distribution<int> dist(low, high);
    return dist(gen);
}

void Powerup::setCoordinates(int newRow, int newCol) {
    row = newRow;
    col = newCol;
}

int Powerup::getRow() const {
    return row;
}

int Powerup::getCol() const {
    return col;
}

void swap(Powerup& lhs, Powerup& rhs) noexcept{
    using std::swap;
    swap(lhs.row, rhs.row);
    swap(lhs.col, rhs.col);
}