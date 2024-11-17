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

    //adaug texturi care nu provin din sprite sheet
    void addTexture(const std::string &name, const std::string &path) const;

    //"Populeaza" array-ul cells[12] dintr-un sprite sheet cu texturile specifice
    static void populateCells(sf::IntRect (&cells)[12], const std::string &texturePath);
};

#endif // GAMETEXTURE_H
