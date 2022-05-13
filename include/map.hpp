#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

const int TILE_HEIGHT = 16;
const int TILE_WIDTH = 16;

class Map{
	private:
                int pheight_, pwidth_;	//in pixels
                int theight_, twidth_;	//in tiles

	public:
		std::string background;
		std::string tile;

		sf::Image image_back;
		sf::Image image_tile;

                sf::Texture texture_back;
		sf::Texture texture_tile;

                sf::Sprite sprite_back;
		sf::Sprite sprite_tile;

		std::vector<char> mapOfTiles;

		Map(std::string, std::string, int height, int width);	
		
		void readMapOfTiles(std::string);
		void writeMapOfTiles(std::string);
		void setPixels(sf::Vector2i);
		void setTiles(sf::Vector2i);
		sf::Vector2i getPixels() const;
		sf::Vector2i getTiles() const;

		void drawTiles(sf::RenderWindow &);	
};

#endif//MAP_HPP
