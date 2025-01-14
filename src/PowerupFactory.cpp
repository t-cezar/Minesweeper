#include "../headers/PowerupFactory.h"
#include "../headers/MineRevealRandom.h"
#include "../headers/RevealAreaRandom.h"
#include "../headers/RevealWrongFlags.h"
#include <unordered_map>
#include <functional>
std::shared_ptr<Powerup> PowerupFactory::createPowerup(int type, int row, int col) {
    static const std::unordered_map<int, std::function<std::shared_ptr<Powerup>(int, int)>> factoryMap = {
        {0, [](int row, int col) { return std::make_shared<MineRevealRandom>(row, col); }},
        {1, [](int row, int col) { return std::make_shared<RevealAreaRandom>(row, col); }},
        {2, [](int row, int col) { return std::make_shared<RevealWrongFlags>(row, col); }}
    };

    auto i = factoryMap.find(type);
    if (i != factoryMap.end()) {
        return i->second(row, col);
    }
    return nullptr;
}