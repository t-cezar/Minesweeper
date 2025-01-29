#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <map>
#include "ResourceManager.h"

class GameTexture : public ResourceManager<sf::Texture> {
public:
    explicit GameTexture(std::shared_ptr<std::map<std::string, sf::Texture>> textureMap);
    static void addCellsTextures(sf::IntRect (&cells)[14]);
    void initAddTextures(sf::IntRect (&cells)[14]) const;
};

#endif // GAMETEXTURE_H