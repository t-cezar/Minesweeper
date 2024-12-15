#include "../headers/GameTexture.h"
#include <stdexcept>//todo: sa-l inlocuiesc cu functii, i.e. loadError()

GameTexture::GameTexture(std::shared_ptr<std::map<std::string, sf::Texture>> textureMap)
    : textureMap(std::move(textureMap)) {}

void GameTexture::addTexture(const std::string &name, const std::string &path) const {
    sf::Texture texture;
    if (texture.loadFromFile(path)) {
        (*textureMap)[name] = texture;
    } else {
        throw std::runtime_error("Error addTexture()");
    }
}

void GameTexture::addCellsTextures(sf::IntRect (&cells)[12]) {
    cells[0] = sf::IntRect(1, 73, 16, 16);
    for (int i = 1; i <= 7; i++) {
        cells[i] = cells[i - 1];
        cells[i].left += 17;
        //in textures.png intre texturi este un spatiu de 1px, o celula fiind de 16x16px deci
        //adaug 17 ca sa trec la urmatoare textura de celula
    }
    cells[8] = sf::IntRect(1, 56, 16, 16);   // celula Unrevealed
    cells[9] = sf::IntRect(18, 56, 16, 16);  // celula Revealed
    cells[10] = sf::IntRect(35, 56, 16, 16); // celula Flagged
    cells[11] = sf::IntRect(52, 56, 16, 16); // Mina
}
void GameTexture::initAddTextures(sf::IntRect (&cells)[12]) const{
    addTexture("corner_up_left", "assets/corner_up_left.png");
    addTexture("corner_up_right", "assets/corner_up_right.png");
    addTexture("corner_bottom_left", "assets/corner_bottom_left.png");
    addTexture("corner_bottom_right", "assets/corner_bottom_right.png");
    addTexture("t_left", "assets/t_left.png");
    addTexture("t_right", "assets/t_right.png");
    addTexture("textures", "assets/textures.png");
    addTexture("border_hor","assets/border_hor.png");
    addTexture("border_vert","assets/border_vert.png");
    addCellsTextures(cells);
}
