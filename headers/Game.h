#ifndef GAME_H
#define GAME_H

#include "Grid.h"
#include "GameTexture.h"
#include <SFML/Graphics.hpp>
#include <memory>

class Game {
    int rows;
    int cols;
    Grid grid;

    std::shared_ptr<std::map<std::string, sf::Texture>> textureMap = std::make_shared<std::map<std::string, sf::Texture>>();
    GameTexture gameTexture;

    sf::RenderWindow window;
    sf::View gridView;
    sf::RenderTexture staticLayer;
    sf::Sprite staticLayerSprite;
    sf::IntRect cells[14];
    bool shouldExit;
    bool gameOver;

    sf::Vector2i mousePos;
    std::pair<int, int> cellCoord;

    void createWindow();
    void initialRender();
    void testingGen() const;
    static void drawSprite(sf::RenderTarget& target,
                        const sf::Texture& texture, float x, float y);
    static void drawSprite(sf::RenderTarget& target, const sf::Texture& texture,
                        float x, float y, const sf::IntRect& rect, bool red);
    static void drawVert(sf::RenderTarget& target, const sf::Texture& texture,
                        int cnt, float x, float y);
    static void drawHor(sf::RenderTarget& target, const sf::Texture& texture,
                        int cnt, float x, float y);
    std::pair<int, int> getCellFromMousePos(const sf::Vector2i &mousePos) const;
    void onLeftClick(int row, int col);
public:
    Game(int rows, int cols);

    void update();
    void render();
    void run();
    friend std::ostream& operator<<(std::ostream& stream, const Game& game);
};

#endif
