#include "../include/gameTile.hpp"

GameTile::GameTile(std::string tiles, float x, float y, bool passable, bool exit) {
	image.loadFromFile("images/" + tiles);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(7 * GAMETILE_W, 0, GAMETILE_W, GAMETILE_H));
	pos = sf::Vector2f(x, y);
	sprite.setPosition(pos);
	isPassable = passable;
	isExit = exit;
}

bool GameTile::setSprite(std::string file) {
	bool loadImage;
	loadImage = image.loadFromFile("images/" + file);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, GAMETILE_W, GAMETILE_H));
	return loadImage;
}

