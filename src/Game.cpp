#include "../headers/Game.h"
#include "../headers/GameException.h"
#include <thread>
#include <iostream>

Game::Game(int rows, int cols)
    : rows(rows),
      cols(cols),
      grid(rows, cols, 40),
      textureMap(std::make_shared<std::map<std::string, sf::Texture>>()),
      gameTexture(textureMap),
      shouldExit(false),
      gameOver(false){}


void Game::createWindow() {
    window.create(sf::VideoMode({550, 650}), "Minesweeper Power-Ups", sf::Style::Default);
    if (!window.isOpen()) {
        throw InitCreateException("Esuare la crearea Window");
    }
    window.setFramerateLimit(60);
    gridView.reset(sf::FloatRect(34.f, 119.f, 480.f, 480.f));
    gridView.setViewport(sf::FloatRect(34.f/550.f,119.f/650.f,480.f/550.f,480.f/650.f));
}

void Game::initialRender() {
    if (!staticLayer.create(window.getSize().x, window.getSize().y)) {
        throw InitCreateException("Esuare la crearea staticLayer.");
    }
    staticLayer.clear(sf::Color(192, 192, 192));
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
        throw InitCreateException("Nu s-a putut seta textura pentru staticLayerSprite.");
    }
}

void Game::testingGen() const {
    std::cout << *this;
}

void Game::drawSprite(sf::RenderTarget& target, const sf::Texture& texture, float x, float y) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(x, y);
    target.draw(sprite);
}

void Game::drawSprite(sf::RenderTarget& target, const sf::Texture& texture,
                float x, float y, const sf::IntRect& rect, bool red) {
    sf::Sprite sprite;
    sprite.setTexture(texture);
    if (rect != sf::IntRect()) {
        sprite.setTextureRect(rect);
    }
    sprite.setPosition(x, y);
    sprite.setScale(1.875, 1.875);
    if (red) {
        sprite.setColor(sf::Color(255, 150, 150, 255));
    }
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

std::pair<int, int> Game::getCellFromMousePos(const sf::Vector2i &mousePosition) const {
    constexpr int gridXStart = 34;
    constexpr int gridYStart = 119;
    constexpr int cellSize = 30;

    int gridX = mousePosition.x - gridXStart;
    int gridY = mousePosition.y - gridYStart;
    if (gridX >= 0 && gridX < cols * cellSize &&
        gridY >= 0 && gridY < rows * cellSize) {
        int col = gridX / cellSize;
        int row = gridY / cellSize;
        return {row, col};
        }
    return {-1, -1};
}

void Game::onLeftClick(int row, int col) {
    if (!grid.getCell(row, col).isFlagged()) {
        if (grid.hasPowerup(row, col)) {
            grid.activatePowerup(row, col);
            grid.revealCell(row, col);
            grid.markedEmptyReveal();
        } else {
            if (grid.getCell(row, col).isRevealed()) {
                gameOver = grid.revealAroundCell(row, col);
            } else if (grid.getCell(row, col).isMine()) {
                grid.makeRedMine(row, col);
                gameOver = true;
            } else if (grid.minesCount(row, col) == 0) {
                grid.revealEmptyCells(row, col);
            } else {
                grid.revealCell(row, col);
            }
        }
    }
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
                if (!gameOver) {
                    mousePos = sf::Mouse::getPosition(window);
                    cellCoord = getCellFromMousePos(mousePos);
                    int row = cellCoord.first;
                    int col = cellCoord.second;
                    if (row != -1 && col != -1) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            onLeftClick(row, col);
                        }
                        if (event.mouseButton.button == sf::Mouse::Right) {
                            if (!grid.getCell(row, col).isRevealed()) {
                                grid.flagCell(row, col);
                            }
                        }
                    }
                }
                break;
            }
            default:
                break;
        }
    }
    if (shouldExit) window.close();
    if (gameOver) grid.revealAllMines();
}



void Game::render() {
    window.clear(sf::Color(192, 192, 192));
    window.draw(staticLayerSprite);
    window.setView(gridView);

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            bool red = false;
            const auto &cell = grid.getCell(i, j);
            sf::IntRect cellTexture;

            if (cell.isRevealed()) {
                if (grid.hasPowerup(i, j)) {
                    cellTexture = cells[13]; // cell cu simbol (?)
                } else if (cell.isMine()) {
                    if (cell.isRedMine()) {
                        cellTexture = cells[12]; // Red mine;
                        std::cout<<"a ajuns pana la cells 12";
                    } else {
                        cellTexture = cells[11]; // Mine
                    }
                } else {
                    int minesAroundCell = grid.minesCount(i, j);
                    if (minesAroundCell != 0) {
                        cellTexture = cells[minesAroundCell - 1];
                    } else {
                        cellTexture = cells[9]; // Empty cell
                    }
                }
            } else if (cell.isFlagged()) {
                if ( (!cell.isMine() && gameOver) || (!cell.isMine() && cell.isMarked()) ) {
                    red = true; // Red flag
                }
                cellTexture = cells[10]; // Flagged
            } else {
                cellTexture = cells[8]; // Unrevealed
            }

            drawSprite(window, (*textureMap)["textures"],
                       34.f + static_cast<float>(j) * 30.f,
                       119.f + static_cast<float>(i) * 30.f, cellTexture, red);
        }
    }

    window.setView(window.getDefaultView());
    window.display();
}

void Game::run() {
    try {
        createWindow();
        initialRender();
        testingGen();
        while (window.isOpen()) {
            update();
            render();
            using namespace std::chrono_literals;
            std::this_thread::sleep_for(300ms);
        }
    } catch (const InitCreateException &e) {
        std::cerr << "Initial Create Error (Window/staticLayer): " << e.what() << std::endl;
    } catch (const TextureException &e) {
        std::cerr << "Texture Error: " << e.what() << std::endl;
    } catch (const InvalidCoordinateException &e) {
        std::cerr << "Coordinate Error: " << e.what() << std::endl;
    } catch (const InvalidGridException& e) {
        std::cerr << "Grid Initialization Error: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown error." << std::endl;
    }
}

std::ostream& operator<<(std::ostream& stream, const Game& game) {
    stream << "\nGrid:\n" << game.grid;
    return stream;
}
