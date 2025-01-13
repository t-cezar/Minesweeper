#ifndef REVEAL_WRONG_FLAGS_H
#define REVEAL_WRONG_FLAGS_H

#include "Powerup.h"
#include <memory>

class RevealWrongFlags : public Powerup {
public:
    RevealWrongFlags(int row, int col);
    RevealWrongFlags(const RevealWrongFlags& other);

    void activate(std::vector<std::vector<Cell>>& gridCells) const override;
    void print(std::ostream& os) const override;

    [[nodiscard]] std::shared_ptr<Powerup> clone() const override;

    RevealWrongFlags& operator=(const RevealWrongFlags& other);
};

#endif