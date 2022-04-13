#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

class Person {
	private:
		float x, y;
	public:
	       	float w, h, vx, vy, speed = 0;
		int dir = 0;
		std::string file;
		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		
		Person(std::string File, float X, float Y, float W, float H);
		float getCoordinateX();
		float getCoordinateY();

	       	void update(float time);
};

#endif //PERSON_CPP
