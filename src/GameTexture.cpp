#include "../headers/GameTexture.h"

GameTexture::GameTexture(std::shared_ptr<std::map<std::string, sf::Texture>> textureMap)
    : ResourceManager<sf::Texture>(std::move(textureMap)) {}

void GameTexture::addCellsTextures(sf::IntRect (&cells)[14]) {
    cells[0] = sf::IntRect(1, 73, 16, 16);
    for (int i = 1; i <= 7; i++) {
        cells[i] = cells[i - 1];
        cells[i].left += 17;
        //in textures.png intre texturi este un spatiu de 1px, o celula fiind de 16x16px deci
        //adaug 17 ca sa trec la urmatoare textura de celula
    }
    cells[8] = sf::IntRect(1, 56, 16, 16);   // Unrevealed
    cells[9] = sf::IntRect(18, 56, 16, 16);  // Revealed
    cells[10] = sf::IntRect(35, 56, 16, 16); // Flagged
    cells[11] = sf::IntRect(86, 56, 16, 16); // Mina
    cells[12] = sf::IntRect(103, 56, 16, 16); // Mina rosie
    cells[13] = sf::IntRect(52, 56, 16, 16); // Powerup
}

void GameTexture::initAddTextures(sf::IntRect (&cells)[14]) const {
    add("corner_up_left", "assets/corner_up_left.png");
    add("corner_up_right", "assets/corner_up_right.png");
    add("corner_bottom_left", "assets/corner_bottom_left.png");
    add("corner_bottom_right", "assets/corner_bottom_right.png");
    add("t_left", "assets/t_left.png");
    add("t_right", "assets/t_right.png");
    add("textures", "assets/textures.png");
    add("border_hor", "assets/border_hor.png");
    add("border_vert", "assets/border_vert.png");
    addCellsTextures(cells);
}