#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

const int TILE_HEIGHT = 16;
const int TILE_WEIGHT = 16;

class Map{
	public:
		std::string background;
		std::string tile;
		sf::Image image;
                sf::Texture texture;
                sf::Sprite sprite;
		int h, w;
		int num_tile;
		Map(std::string, std::string tile, int w, int h, int num_tile);	
		
};

#endif//MAP_HPP
