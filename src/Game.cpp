#include "../headers/Game.h"
#include <thread>
Game::Game(int rows, int cols, int mines)
    : rows(rows),
      cols(cols),
      nrMines(mines),
      grid(rows, cols, mines),
      gameTexture(textureMap),
      shouldExit(false) {}

void Game::initAddTextures() {
    gameTexture.addTexture("cornerTopLeft", "assets/corner_up_left.png");
    gameTexture.addTexture("cornerTopRight", "assets/corner_up_right.png");
    gameTexture.addTexture("cornerBottomLeft", "assets/corner_bottom_left.png");
    gameTexture.addTexture("cornerBottomRight", "assets/corner_bottom_right.png");
    gameTexture.addTexture("t1", "assets/t_left.png");
    gameTexture.addTexture("t2", "assets/t_right.png");

    GameTexture::populateCells(cells, "assets/textures.png");
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
    window.display();
}
// //am incercat mai jos sa testez daca afiseaza doua texturi, una
// //din map si una din cell, dar nu apare nimic. Nu imi dau seama daca
// //problema este ca am ales sa scriu in render(), sau ceva
// //este incorect in clasa Game sau GameTexture
// //nu sunt sigur nici daca este corecta structura
// //cu update() si render()

// void Game::render() {
//     //window.clear(sf::Color(80, 80, 80));
//
//
//     sf::Sprite sprite;
//     sprite.setTexture((*textureMap)["t1"]);
//
//     sprite.setTextureRect(cells[0]);
//
//     sprite.setPosition(100.f, 100.f);
//
//     window.draw(sprite);
//
//
//     window.display();
// }





// //faptul ca nu afisa nimic m-a facut sa comentez tot codul care afisa
// //in consola testele din main. Ca sa ma ocup strict de window.
// //Am observat ca nu aparea deloc window atunci cand
// //comentam tot acel cod mai putin instantierea obiectului Game
// //si apelarea functiei run().

// //Window aparea doar atunci cand aveam /* pus la inceputul liniei 29 (sau oriunde dupa)
// //Am incercat sa folosesc si sleep poate are
// //nevoie de mai mult timp, dar nu a functionat, sau poate nu am pus
// //destul
