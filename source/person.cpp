#include <SFML/Graphics.hpp>  
#include <fstream>
#include <iostream>

#include "../include/person.hpp"
#include "../include/functions.hpp"

void Vessel::readStateTable() {
        std::ifstream in;
        in.open("data/" + name_ + "/state.dat");
       
	in >> idle_;
	in >> run_;
	in >> jump_;
	in >> fall_;

        in.close();
}

void Vessel::writeStateTable() {
        std::ofstream out;
        out.open("data/" + name_ + "/test.dat");
        out << idle_ << " " << run_ << " " << jump_ << " " << fall_ <<std::endl;
        out.close();
}

void Vessel::initVessel(std::string name, sf::Vector2f coord) {
	name_ = name;
        coord_ = coord;
	speed_ = {0, 0};
	acel_ = {0, 0};
	
	readSize();

        loadImageFromFile("images/" + name + "/image.png", image);
        image.createMaskFromColor(sf::Color(255, 255, 255));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
	
	readStateTable();
};

void Vessel::readSize() {
        std::ifstream in;
        in.open("data/" + name_ + "/size.dat");

        in >> size_.x;
        in >> size_.y;
        in.close();
}

void Vessel::writeSize() const{
        std::ofstream out;
        out.open("data/maps/" + name_ + "/test.dat");
        out << size_.x << " " << size_.y <<std::endl;
        out.close();
}


sf::Vector2f Vessel::getCoord() const {
	return sf::Vector2f{coord_.x, coord_.y};
}

void Vessel::setCoord(sf::Vector2f coord) {
	coord_ = coord;
}

sf::Vector2f Vessel::getSpeed() const {
	return sf::Vector2f{speed_.x, speed_.y};
}

void Vessel::setSpeed(sf::Vector2f speed) {
	speed_ = speed;
}

sf::Vector2f Vessel::getAcel() const {
        return sf::Vector2f{acel_.x, acel_.y};
}

void Vessel::setAcel(sf::Vector2f acel) {
	acel_ = acel;
}

sf::Vector2f Vessel::getSize() const {
        return sf::Vector2f{size_.x, size_.y};
}

void Vessel::setSize(sf::Vector2f size) {
	size_ = size;
}

void Vessel::update(float time) {}

Vessel::~Vessel() {}

void Person::initPerson(std::string name, sf::Vector2f coord) {
	initVessel(name, coord);

	soul::PERSON;

	speedOfRun_ = 0.1;
	
}

void Person::interactWithMap(Map &map) {
	std::vector<char>::size_type coord = map.getTileFromCoord(coord_);
	
}


void Person::control() {
/*
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                frame += FRAME_SPEED;
                if(frame >= run_) 
                        Frame -= run_;
                hero.sprite.setTextureRect(sf::IntRect(size_.x * (int(Frame) + 1), 0, -size_.x, size_.y));
                camera.getCoordinateView(hero.getCoordinateX() + (HERO_W / 2), hero.getCoordinateY() + (HERO_H / 2));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                Frame += FRAME_SPEED;
                if(frame >= run_)
                        frame -= run_;
                hero.sprite.setTextureRect(sf::IntRect(size_.x * int(Frame), 0, HERO_W, HERO_H));
                camera.getCoordinateView(hero.getCoordinateX() + (HERO_W / 2), hero.getCoordinateY() + (HERO_H / 2));
        }


        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                hero.sprite.setTextureRect(sf::IntRect(0, 0, HERO_W, HERO_H));
                camera.getCoordinateView(hero.getCoordinateX() + (HERO_W / 2), hero.getCoordinateY() + (HERO_H / 2));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                hero.sprite.setTextureRect(sf::IntRect(0, 0, HERO_W, HERO_H));
                camera.getCoordinateView(hero.getCoordinateX() + (HERO_W / 2), hero.getCoordinateY() + (HERO_H / 2));
        }*/
}

/*
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
*/
