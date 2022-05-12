#include <SFML/Graphics.hpp>

#include "../include/gameObj.hpp"

GameObj::GameObj(float X, float Y, float W, float H) {
	position = {X, Y};
	size = {W, H};
}

void GameObj::setCoordinate(float X, float Y) {
	position = {X, Y};
}

void GameObj::setSize(float W, float H) {
	size = {W, H};
}

sf::Vector2f GameObj::getCoordinate() {
	return position;
}

sf::Vector2f GameObj::getSize() {
	return size;
}
