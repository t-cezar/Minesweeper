#ifndef POWERUPFACTORY_H
#define POWERUPFACTORY_H

#include "Powerup.h"
#include <memory>

class PowerupFactory {
public:
    static std::shared_ptr<Powerup> createPowerup(int type, int row, int col);
};

#endif
