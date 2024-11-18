#include "../headers/Game.h"
#include <thread>
Game::Game(int rows, int cols, int mines)
    : rows(rows),
      cols(cols),
      nrMines(mines),
      grid(rows, cols, mines),
      textureMap(std::make_shared<std::map<std::string, sf::Texture>>()),
      gameTexture(textureMap),
      shouldExit(false) {}

void Game::initAddTextures() {
    gameTexture.addTexture("cornerTopLeft", "assets/corner_up_left.png");
    gameTexture.addTexture("cornerTopRight", "assets/corner_up_right.png");
    gameTexture.addTexture("cornerBottomLeft", "assets/corner_bottom_left.png");
    gameTexture.addTexture("cornerBottomRight", "assets/corner_bottom_right.png");
    gameTexture.addTexture("t1", "assets/t_left.png");
    gameTexture.addTexture("t2", "assets/t_right.png");
    gameTexture.addTexture("sprite sheet", "assets/textures.png");
    //todo: iau pe rand stringurile dintr-un fisier text si fac un for pt addTextures
    GameTexture::addCellsTextures(cells);
}
void Game::createWindow() {
    window.create(sf::VideoMode({800, 1000}), "Minesweeper Power-Ups", sf::Style::Default);
    window.setFramerateLimit(60);
}

void Game::run() {
    createWindow();

    while (window.isOpen()) {
        update();
        render();

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);
    }
}

void Game::update() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;

            case sf::Event::Resized:
                break;

            case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) {
                        shouldExit = true;
                    }
                break;

            default:
                break;
        }
    }

    if (shouldExit) {
        window.close();
    }
}

void Game::render() {
    window.clear(sf::Color(80, 80, 80));

    initAddTextures();
    //testing sa vad daca afiseaza corect in window
    sf::Sprite sprite1;
    sprite1.setTexture((*textureMap)["cornerTopLeft"]);
    sprite1.setPosition(10.f, 10.f);
    window.draw(sprite1);

    sf::Sprite sprite2;
    sprite2.setTexture((*textureMap)["sprite sheet"]);
    sprite2.setTextureRect(cells[4]);
    sprite2.setPosition(40.f, 40.f);
    window.draw(sprite2);

    window.display();
}
