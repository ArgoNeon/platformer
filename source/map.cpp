#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "../include/map.hpp"
#include "../include/functions.hpp"

std::vector<char>::size_type Map::getTileFromCoord(sf::Vector2f coord) {
	long int width = tiles_.x + 1;
	return std::vector<char>::size_type {static_cast<std::vector<char>::size_type>((static_cast<long int> (coord.y)) / TILE_HEIGHT * width + ((static_cast<long int> (coord.x)) / TILE_WIDTH))};
}

void Map::setPixels(sf::Vector2f pixels) {
	pixels_ = pixels;
}

void Map::setTiles(sf::Vector2f tiles) {
	tiles_ = tiles;
}

void Map::setHeroCoord(sf::Vector2f hero_coord) {
	hero_coord_ = hero_coord;
}

sf::Vector2f Map::getHeroCoord() const {
	return hero_coord_;
}

sf::Vector2f Map::getPixels() const {
	return pixels_;
}

sf::Vector2f Map::getTiles() const {
	return tiles_;
}

void Map::readMapOfTiles() {
	char tile;
	int width = tiles_.x + 1;
	std::ifstream in;

	in.open("data/maps/" + name_ + "/tiles.dat");
	while(in.is_open() && in.get(tile)) {
		mapOfTiles_.push_back(tile);

		if (tile == 'h') {
			std::vector<char>::size_type k = mapOfTiles_.size();
			int y = TILE_HEIGHT * (k / width);
                        int x = TILE_WIDTH * (k % width);
                        setHeroCoord({static_cast<float> (x), static_cast<float> (y)});
		}
	}

	in.close();
}

void Map::writeMapOfTiles() {
	std::ofstream out;
	out.open("data/maps/" + name_ + "/testTiles.dat");
	std::for_each(mapOfTiles_.begin(), mapOfTiles_.end(),
   	[&out](const char tile) mutable {out << tile;});
	out.close();
}

void Map::readSize() {
        std::ifstream in;
        in.open("data/maps/" + name_ + "/size.dat");

        in >> pixels_.y;
        in >> pixels_.x;
        in.close();

	tiles_.y = pixels_.y / TILE_HEIGHT;
        tiles_.x = pixels_.x / TILE_WIDTH;
}

void Map::writeSize() const{
        std::ofstream out;
        out.open("data/maps/" + name_ + "/testSize.dat");
        out << pixels_.y << " " << pixels_.x << std::endl;
        out.close();
}

void Map::loadMap() {
	loadImageFromFile("images/maps/" + name_ + "/background.jpg", image_back);
	loadImageFromFile("images/maps/" + name_ + "/tiles.png", image_tile);

	texture_back.loadFromImage(image_back);
        texture_tile.loadFromImage(image_tile);
	
	sprite_back.setTexture(texture_back);
        sprite_tile.setTexture(texture_tile);
	
	sprite_back.setTextureRect(sf::IntRect(0, 0, pixels_.x, pixels_.y));
}

void Map::initMap(std::string name) {
	name_ = name;
	
	readSize();
	writeSize();
	readMapOfTiles();
	writeMapOfTiles();
	loadMap();
}

void Map::drawTiles(sf::RenderWindow &window) {
	int i = 0, j = 0;
	int width = tiles_.x + 1;
	sprite_tile.setTextureRect(sf::IntRect(0, 0, TILE_HEIGHT, TILE_WIDTH));
		
	for(std::vector<char>::size_type k = 0; k != mapOfTiles_.size(); k++) { 
		switch(mapOfTiles_[k]) {
		case '0':
			break;
		case 'g':
			i = k / width;
			j = k % width;
			sprite_tile.setPosition(j * TILE_WIDTH, i * TILE_HEIGHT);
                	window.draw(sprite_tile);
			break;
		case '\n':
                        break;
		case 'h':
			break;
		default:
			break;
		}
	}
}

