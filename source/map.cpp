#include <SFML/Graphics.hpp>

#include "../include/map.hpp"

void Map::setPixels(sf::Vector2i pixels) {
	pheight_ = pixels.x;
	pwidth_ = pixels.y;
}

void Map::setTiles(sf::Vector2i tiles) {
	theight_ = tiles.x;
	twidth_ = tiles.y;
}

sf::Vector2i Map::getPixels() const {
	return sf::Vector2i{pheight_, pwidth_};
}

sf::Vector2i Map::getTiles() const {
	return sf::Vector2i{theight_, twidth_};
}

void Map::readMapOfTiles(std::string name) {
	char tile;
	std::ifstream in;
	in.open("data/" + name);
	while(in.is_open() && in.get(tile))
		mapOfTiles.push_back(tile);
	in.close();
}

void Map::writeMapOfTiles(std::string name) {
	std::ofstream out;
	out.open("data/" + name);
	std::for_each(mapOfTiles.begin(), mapOfTiles.end(),
   	[&out](const char tile) mutable {out << tile;});
	out.close();
}


Map::Map(std::string background, std::string tile, int height, int width) {
	pheight_ = height;
	pwidth_ = width;
	theight_ = height / TILE_HEIGHT;
	twidth_ = width / TILE_WIDTH;

	if(!image_back.loadFromFile("images/maps/" + background)) {
		throw std::invalid_argument ("images/maps/" + background + "doesn't open");
	}

        if(!image_tile.loadFromFile("images/maps/" + tile)) {
                throw std::invalid_argument ("images/maps/" + tile + "doesn't open");
        }

        texture_back.loadFromImage(image_back);
	texture_tile.loadFromImage(image_tile);

        sprite_back.setTexture(texture_back);
	sprite_tile.setTexture(texture_tile);

        sprite_back.setTextureRect(sf::IntRect(0, 0, pwidth_, pheight_));
}

void Map::drawTiles(sf::RenderWindow &window) {
	int i = 0, j = 0;
	int width = twidth_ + 1;
	sprite_tile.setTextureRect(sf::IntRect(0, 0, TILE_HEIGHT, TILE_WIDTH));	
	
	for(std::vector<int>::size_type k = 0; k != mapOfTiles.size(); k++) { 
		switch(mapOfTiles[k]) {
		case '0':
			break;
		case '\n':
			break;
		case 'g':
			i = k / width;
			j = k % width;
			sprite_tile.setPosition(j * TILE_WIDTH, i * TILE_HEIGHT);
                	window.draw(sprite_tile);
			break;
		default:
			break;
		}
	}
}

