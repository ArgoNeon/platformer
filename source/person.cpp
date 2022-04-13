#include <SFML/Graphics.hpp>  

#include "../include/person.hpp"

Person::Person(std::string File, float X, float Y, float W, float H) {
	file = File;
	x = X;
	y = Y;
	w = W;
	h = H;
	image.loadFromFile("images/" + file);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0, 0, w, h));
}

float Person::getCoordinateX(){
	return x;
}

float Person::getCoordinateY(){
        return y;
}

void Person::update(float time) {
	switch(dir) {
		case 0:
			vx = speed;
			vy = 0;
			break;
		case 1:
			vx = -speed;
			vy = 0;
			break;
		case 2:
			vx = 0;
			vy = speed;
			break;
		case 3:
			vx = 0;
			vy = -speed;
			break;
	}

		x += vx * time;
		y += vy * time;
		speed = 0;
		sprite.setPosition(x, y);
}

