#ifndef POWERUPFACTORY_H
#define POWERUPFACTORY_H
#include "Powerup.h"
#include <memory>
#include <unordered_map>
#include <functional>

class PowerupFactory {
public:
    static std::shared_ptr<Powerup> createPowerup(int type, int row, int col);

    static const std::unordered_map<int, std::function<std::shared_ptr<Powerup>(int, int)>> factoryMap;
};

#endif
