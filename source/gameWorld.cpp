#include "../include/gameWorld.hpp"
#include "../include/gameTile.hpp"

GameWorld::GameWorld(int Weight, int Height){
	weight = Weight;
        height = Height;
}
void setBackground(std::string background) {
	imageBackground.loadFromFile("images/maps/" + background);
        textureBackground.loadFromImage(imageBackground);
        spriteBackground.setTexture(textureBackground);
        spriteBackground.setTextureRect(sf::IntRect(0, 0, weight * GAMETILE_W, height * GAMETILE_H));
}

void setTiles(std::string tiles){
	imageTileSet.loadFromFile("images/maps/" + tiles);
        textureTileSet.loadFromImage(imageTileSet);
        spriteTileSet.setTexture(textureTileSet);
        spriteTileSet.setTextureRect(sf::IntRect(0, 0, w * TILE_HEIGHT, h * TILE_WEIGHT));
}

void GameWorld::setPlayerPos() {
	
}
