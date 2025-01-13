#ifndef POWERUP_H
#define POWERUP_H

#include <vector>
#include <memory>
#include "Cell.h"

class Powerup {
protected:
    int row, col;

public:
    Powerup(int row, int col);
    virtual ~Powerup() = default;

    Powerup(const Powerup& other) = default;
    Powerup& operator=(const Powerup& other);

    static int generateRandom(int low, int high);
    virtual void activate(std::vector<std::vector<Cell>>& gridCells) const = 0;
    virtual void print(std::ostream& os) const = 0;
    [[nodiscard]] virtual std::shared_ptr<Powerup> clone() const = 0;

    void setCoordinates(int newRow, int newCol);
    [[nodiscard]] int getRow() const;
    [[nodiscard]] int getCol() const;

    friend void swap(Powerup& lhs, Powerup& rhs) noexcept;
};

#endif