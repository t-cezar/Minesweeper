#ifndef THREEMINEREVEALRANDOM_H
#define THREEMINEREVEALRANDOM_H
#include "Powerup.h"

class ThreeMineRevealRandom : public Powerup {
public:
    ThreeMineRevealRandom(int row, int col);
    ThreeMineRevealRandom(const ThreeMineRevealRandom& other);

    void activate(std::vector<std::vector<Cell>>& gridCells) const override;
    void print(std::ostream& os) const override;

    [[nodiscard]] std::shared_ptr<Powerup> clone() const override;

    ThreeMineRevealRandom& operator=(const ThreeMineRevealRandom& other);
};

#endif
