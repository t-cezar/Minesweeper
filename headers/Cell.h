#ifndef CELL_H
#define CELL_H
#include <ostream>

class Cell {
    bool mine, revealed, flagged, redMine, marked;
public:
    Cell();
    Cell(const Cell& other);
    ~Cell();

    void setMine();
    void setRedMine();
    void revealCellToggle();
    void flagCellToggle();
    void setMarked(); // celula marcata de un powerup

    [[nodiscard]] bool isMine() const;
    [[nodiscard]] bool isRedMine() const;
    [[nodiscard]] bool isRevealed() const;
    [[nodiscard]] bool isFlagged() const;
    [[nodiscard]] bool isMarked() const;

    Cell& operator = (const Cell& other);
    friend std::ostream& operator << (std::ostream& stream, const Cell& cell);
};

#endif
