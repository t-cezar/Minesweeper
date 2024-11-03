#ifndef CELL_H
#define CELL_H

#include <ostream>

class Cell {
    bool mine, revealed, flagged;
public:
    Cell();
    ~Cell();

    void setMine();
    void revealCell();
    void flagCell();

    [[nodiscard]] bool isMine() const;
    [[nodiscard]] bool isRevealed() const;
    [[nodiscard]] bool isFlagged() const;

    Cell& operator = (const Cell& other) = default;
    friend std::ostream& operator << (std::ostream& stream, const Cell& cell);
};

#endif //CELL_H
