#include <SFML/Graphics.hpp>
#include <cmath>
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

	dir_ = dir::RIGHT;
	dir_idle_ = dir_idle::RIGHT;
	state_ = state::IDLE;	
	
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

        in >> frame_border_.x;
        in >> frame_border_.y;
	in >> size_.x;
	in >> size_.y;
        in.close();

	shift_.x = (frame_border_.x - size_.x) / 2;
	shift_.y = (frame_border_.y - size_.y) / 2;
}

void Vessel::writeSize() const{
        std::ofstream out;
        out.open("data/maps/" + name_ + "/test.dat");
        out << frame_border_.x << " " << frame_border_.y << " " << size_.x << " " << size_.y << std::endl;
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

void Vessel::update(float time) {
	switch(state_) {
	case state::RUN:
    		switch(dir_) {
                case dir::RIGHT:
                        speed_.x = speedOfRun_;
                        speed_.y = 0;
                        break;
                case dir::LEFT:
                        speed_.x = -speedOfRun_;
                        speed_.y = 0;
                        break;
                case dir::UP:
                        speed_.x = 0;
                        speed_.y = -speedOfRun_;
                        break;
                case dir::DOWN:
                        speed_.x = 0;
                        speed_.y = speedOfRun_;
                        break;
       		}
		break;
	default:
		break;
	}

                coord_.x += speed_.x * time;
                coord_.y += speed_.y * time;
                speed_ = {0, 0};
                sprite.setPosition(coord_);
}

Vessel::~Vessel() {}

void Person::initPerson(std::string name, sf::Vector2f coord) {
	initVessel(name, coord);

	soul::PERSON;

	speedOfRun_ = 0.1;
	
	sprite.setTextureRect(sf::IntRect(0, frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	
}

void Person::interactWithMap(Map &map) {
	std::vector<char>::size_type coord = map.getTileFromCoord(coord_);
	
}


void Person::control() {

	if(!((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
		state_ = state::IDLE;
		frame_ += FRAME_SPEED;
		
		if(frame_ >= idle_)
                        frame_ = std::fmod(frame_, idle_);

		if (dir_idle_ == dir_idle::RIGHT)
			sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
		else
			sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
	}

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		dir_ = dir::RIGHT;
		dir_idle_ = dir_idle::RIGHT;
		state_ = state::RUN;
                frame_ += FRAME_SPEED;

                if(frame_ >= run_)
                        frame_ = std::fmod(frame_, run_);

                sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
                //camera.getCoordinateView(hero.getCoordinateX() + (HERO_W / 2), hero.getCoordinateY() + (HERO_H / 2));
        }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                dir_ = dir::LEFT;
		dir_idle_ = dir_idle::LEFT;
                state_ = state::RUN;
                frame_ += FRAME_SPEED;

                if(frame_ >= run_) 
                        frame_ = std::fmod(frame_, run_);

                sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
                //camera.getCoordView() + (HERO_W / 2), hero.getCoordinateY() + (HERO_H / 2));
        }
/*

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		dir_ = dir::UP;
		state_ = state::RUN;
		frame_ += FRAME_SPEED;
                hero.sprite.setTextureRect(sf::IntRect(0, 0, HERO_W, HERO_H));
                camera.getCoordinateView(hero.getCoordinateX() + (HERO_W / 2), hero.getCoordinateY() + (HERO_H / 2));
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		dir_ = dir::DOWN;
		state_ = state::RUN;
		frame_ += FRAME_SPEED;
                hero.sprite.setTextureRect(sf::IntRect(0, 0, HERO_W, HERO_H));
                camera.getCoordinateView(hero.getCoordinateX() + (HERO_W / 2), hero.getCoordinateY() + (HERO_H / 2));
        }*/
}
