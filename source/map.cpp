#include <SFML/Graphics.hpp>

#include "../include/map.hpp"

Map::Map(std::string background, std::string tile, int w, int h, int num_tile) {
	image.loadFromFile("images/maps/" + background);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, w * TILE_HEIGHT, h * TILE_WEIGHT));
}
