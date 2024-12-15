#ifndef CELL_H
#define CELL_H
#include <ostream>

class Cell {
    bool mine, revealed, flagged;
public:
    Cell();
    Cell(const Cell& other);
    ~Cell();

    void setMine();
    void revealCellToggle();
    void flagCellToggle();

    [[nodiscard]] bool isMine() const;
    [[nodiscard]] bool isRevealed() const;
    [[nodiscard]] bool isFlagged() const;
    Cell& operator = (const Cell& other);
    friend std::ostream& operator << (std::ostream& stream, const Cell& cell);
};

#endif
