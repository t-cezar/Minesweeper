#ifndef MINE_REVEAL_RANDOM_H
#define MINE_REVEAL_RANDOM_H

#include "Powerup.h"
#include <memory>

class MineRevealRandom : public Powerup {
public:
    MineRevealRandom(int row, int col);
    MineRevealRandom(const MineRevealRandom& other);

    void activate(std::vector<std::vector<Cell>>& gridCells) const override;
    void print(std::ostream& os) const override;

    [[nodiscard]] std::shared_ptr<Powerup> clone() const override;

    MineRevealRandom& operator=(const MineRevealRandom& other);
};

#endif