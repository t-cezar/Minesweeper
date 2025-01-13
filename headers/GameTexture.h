#ifndef GAMETEXTURE_H
#define GAMETEXTURE_H

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <memory>

class GameTexture {
    std::shared_ptr<std::map<std::string, sf::Texture>> textureMap;

public:
    explicit GameTexture(std::shared_ptr<std::map<std::string, sf::Texture>> textureMap);
    void addTexture(const std::string &name, const std::string &path) const;
    static void addCellsTextures(sf::IntRect (&cells)[14]);
    void initAddTextures(sf::IntRect (&cells)[14]) const;
};

#endif
