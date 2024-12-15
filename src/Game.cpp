#include "../headers/Game.h"
#include <thread>
#include <iostream>
Game::Game(int rows, int cols, int mines)
    : rows(rows),
      cols(cols),
      nrMines(mines),
      grid(rows, cols, mines),
      textureMap(std::make_shared<std::map<std::string, sf::Texture>>()),
      gameTexture(textureMap),
      shouldExit(false),
      gameOver(false){}

void Game::createWindow() {
    window.create(sf::VideoMode({550, 650}), "Minesweeper Power-Ups", sf::Style::Default);
    window.setFramerateLimit(60);
    gridView.reset(sf::FloatRect(34.f, 119.f, 480.f, 480.f));
    gridView.setViewport(sf::FloatRect(
        34.f / 550.f,
        119.f / 650.f,
        480.f / 550.f,
        480.f / 650.f));
}

void Game::initialRender() {
    if (!staticLayer.create(window.getSize().x, window.getSize().y)) {
        throw std::runtime_error("Error staticLayer.create");
    }
    staticLayer.clear(sf::Color(80, 80, 80));
    gameTexture.initAddTextures(cells);

    float startX = 10.0f;
    float startY = 10.0f;
    //stanga
    drawSprite(staticLayer, (*textureMap)["corner_up_left"], startX, startY);
    drawSprite(staticLayer, (*textureMap)["t_left"], startX, 98.0f);
    drawSprite(staticLayer, (*textureMap)["corner_bottom_left"], startX, 598.f);
    drawVert(staticLayer, (*textureMap)["border_vert"], 17, startX, 30.0f);
    drawVert(staticLayer, (*textureMap)["border_vert"], 120, startX, 118.f);
    //dreapta
    drawSprite(staticLayer, (*textureMap)["corner_up_right"], 514.f, startY);
    drawSprite(staticLayer, (*textureMap)["t_right"], 514.f, 98.f);
    drawSprite(staticLayer, (*textureMap)["corner_bottom_right"], 514.f, 598.f);
    drawVert(staticLayer, (*textureMap)["border_vert"], 17, 514.f, 30.0f);
    drawVert(staticLayer, (*textureMap)["border_vert"], 120, 514.f, 118.f);

    drawHor(staticLayer, (*textureMap)["border_hor"], 121, startX + 24.0f, startY);
    drawHor(staticLayer, (*textureMap)["border_hor"], 120, startX + 24.0f, 98.f);
    drawHor(staticLayer, (*textureMap)["border_hor"], 120, startX + 24.0f, 598.f);

    staticLayer.display();
    //"pastrez" toate texturile ca in loc sa le rerendez pe toate cele de sus,
    //rendez doar una (care teoretic le cuprinde pe toate cele de sus) in render():
    staticLayerSprite.setTexture(staticLayer.getTexture());
    if (!staticLayerSprite.getTexture()) {
        throw std::runtime_error("Error staticLayerSprite.getTexture");
    }
}


void Game::testingGen() const {
    // std::cout << "Minele din grid (x = mina, o = empty):\n";
    // for (int i = 0; i < rows; i++) {
    //     for (int j = 0; j < cols; j++) {
    //         std::cout << grid.getCell(i, j) << " ";//testez op. << pt. Cell
    //     }
    //     std::cout << '\n';
    // }
    // std::cout << "\n";

    //testez reveal and flag
    //grid.revealCell(2, 2);
    //grid.flagCell(3, 3);
    std::cout << '\n';
    std::cout << grid; //testez op. << pt. grid
}

void Game::drawSprite(sf::RenderTarget& target, const sf::Texture& texture, float x, float y) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    target.draw(sprite);
}

void Game::drawSprite(sf::RenderTarget& target, const sf::Texture& texture,
                float x, float y, const sf::IntRect& rect) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    if (rect != sf::IntRect()){
        sprite.setTextureRect(rect);
    }
    sprite.setPosition(x, y);
    sprite.setScale(1.875, 1.875);
    //pt. cell: scale factor de 30/16=1.875, de la 16x16 la 30x30 px
    target.draw(sprite);
}

void Game::drawVert(sf::RenderTarget& target, const sf::Texture& texture,
                    int cnt, float x, float y) {
    for (int i = 0; i < cnt; i++) {
        drawSprite(target, texture, x, y + static_cast<float>(i) * 4.0f);
    } //offset pentru y = 4.0f;
}

void Game::drawHor(sf::RenderTarget& target, const sf::Texture& texture,
                   int cnt, float x, float y) {
    for (int i = 0; i < cnt; i++) {
        drawSprite(target, texture, x + static_cast<float>(i) * 4.0f, y);
    } //offset pentru x = 4.0f;
}

std::pair<int, int> Game::getCellFromMousePos(const sf::Vector2i &mousePos) const {
    constexpr int gridXStart = 34;
    constexpr int gridYStart = 119;
    constexpr int cellSize = 30;

    int gridX = mousePos.x - gridXStart;
    int gridY = mousePos.y - gridYStart;
    if (gridX >= 0 && gridX < cols * cellSize &&
        gridY >= 0 && gridY < rows * cellSize) {
        int col = gridX / cellSize;
        int row = gridY / cellSize;

        return {row, col};
        }
    return {-1, -1};
}

void Game::update() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    shouldExit = true;
                }
                break;
            case sf::Event::MouseButtonPressed: {
                mousePos = sf::Mouse::getPosition(window);
                cellCoord = getCellFromMousePos(mousePos);
                int row = cellCoord.first;
                int col = cellCoord.second;
                if (row != -1 && col != -1) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        if (grid.getCell(row, col).isMine()) {
                            gameOver = true;
                        } else {
                            grid.revealCell(row, col);
                        }
                    } else if (event.mouseButton.button == sf::Mouse::Right) {
                        grid.flagCell(row, col);
                    }
                }
                testingGen();
                break;
            }
            default:
                break;
        }
    }
    if (shouldExit || gameOver) {
        window.close();
    }
}

void Game::render() {
    window.clear(sf::Color(80, 80, 80));
    window.draw(staticLayerSprite);
    window.setView(gridView);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            const auto &cell = grid.getCell(i, j);
            sf::IntRect cellTexture;
            if (cell.isRevealed()) {
                if (cell.isMine()) {
                    cellTexture = cells[11]; //Mines
                } else {
                    int nrMines = grid.getNrMinesAroundCell(i, j);
                    if (nrMines > 0) {
                        cellTexture = cells[nrMines - 1];
                    } else {
                        cellTexture = cells[9]; //Revealed cell
                    }
                }
            } else if (cell.isFlagged()) {
                cellTexture = cells[10]; //Flagged cell
            } else {
                cellTexture = cells[8]; //Unrevealed cell
            }

            drawSprite(window, (*textureMap)["textures"],
                       34.f + static_cast<float>(j) * 30.f,
                       119.f + static_cast<float>(i) * 30.f, cellTexture);
        }
    }
    window.setView(window.getDefaultView());
    window.display();
}

void Game::run() {
    createWindow();
    initialRender();
    while (window.isOpen()) {
        update();
        render();
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(300ms);
    }
}

