#ifndef REVEAL_AREA_RANDOM_H
#define REVEAL_AREA_RANDOM_H

#include "Powerup.h"
#include <memory>

class RevealAreaRandom : public Powerup {
public:
    RevealAreaRandom(int row, int col);

    void activate(std::vector<std::vector<Cell>>& gridCells) const override;
    void print(std::ostream& os) const override;

    [[nodiscard]] std::shared_ptr<Powerup> clone() const override;

    RevealAreaRandom& operator=(const RevealAreaRandom& other);
};

#endif