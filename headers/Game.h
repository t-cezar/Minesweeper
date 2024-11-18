#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "GameTexture.h"
#include <SFML/Graphics.hpp>
#include <memory>


class Game {
    int rows;
    int cols;
    int nrMines;
    Grid grid;

    std::shared_ptr<std::map<std::string, sf::Texture>> textureMap = std::make_shared<std::map<std::string, sf::Texture>>();
    GameTexture gameTexture;

    sf::RenderWindow window;
    sf::IntRect cells[12];
    bool shouldExit;
    void initAddTextures();

public:
    Game(int rows, int cols, int mines);
    void createWindow();
    void run();
    void update();
    void render();

};

#endif //GAME_H