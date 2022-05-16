#include <SFML/Graphics.hpp>
#include <string>

#include "../include/functions.hpp"

void loadImageFromFile(std::string name, sf::Image &image) {
	if(!image.loadFromFile(name))
                throw std::invalid_argument (name  + " doesn't open\n");
}
