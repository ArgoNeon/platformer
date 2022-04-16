#include <SFML/Graphics.hpp>

#include "../include/map.hpp"

Map::Map(std::string background, std::string tile, int h, int w, int num_tile) {
	image.loadFromFile("images/maps/" + background);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, h * TILE_HEIGHT, w * TILE_WEIGHT));
}
