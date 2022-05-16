#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

#include "../include/person.hpp"
#include "../include/functions.hpp"

void Vessel::interactWithMap(Map &map) {
	long int width = map.getWidth();
        const std::vector<char>::size_type coord = map.getTileFromCoord(coord_);
        const std::vector<char>::size_type coord_str = coord / width;
        const std::vector<char>::size_type coord_col = coord %  width;

        const std::vector<char>::size_type border = map.getTileFromCoord(border_);
        const std::vector<char>::size_type border_str = border / width;
        const std::vector<char>::size_type border_col = border %  width;

        for (std::vector<char>::size_type str = coord_str; str <= border_str; str++) {
                for (std::vector<char>::size_type col = coord_col; col <= border_col; col++) {
                        if (map.mapOfTiles_[str * width + col] == 'g') {
                                if ((speed_.x > 0) && ((border_col - 1) < col)) {
                                        speed_.x = 0;
                                }
                        }
                                //if(speed_.x < 0)
                        }
        }
}

void Vessel::update(float time, Map &map) {
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

        interactWithMap(map);

        coord_ += speed_ * time;
        border_ += speed_ * time;
        coord_frame_ += speed_ * time;

        speed_ = {0, 0};
        sprite.setPosition(coord_frame_);
}

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
	
	readSize();
	
	coord_frame_ = coord_ - shift_;
	border_ = coord_ + psize_;
	speed_ = {0, 0};
	acel_ = {0, 0};

	dir_ = dir::RIGHT;
	dir_idle_ = dir_idle::RIGHT;
	state_ = state::IDLE;	

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
	in >> psize_.x;
	in >> psize_.y;
        in.close();

	
	tsize_.x = std::ceil(psize_.x / static_cast<float>(TILE_WIDTH));
	tsize_.y = std::ceil(psize_.y / static_cast<float>(TILE_HEIGHT));
	shift_.x = (frame_border_.x - psize_.x) / 2;
	shift_.y = (frame_border_.y - psize_.y) / 2;
}

void Vessel::writeSize() const{
        std::ofstream out;
        out.open("data/maps/" + name_ + "/test.dat");
        out << frame_border_.x << " " << frame_border_.y << " " << psize_.x << " " << psize_.y << std::endl;
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
        return sf::Vector2f{psize_.x, psize_.y};
}

void Vessel::setSize(sf::Vector2f psize) {
	psize_ = psize;
}

Vessel::~Vessel() {}

void Person::initPerson(std::string name, sf::Vector2f coord) {
	initVessel(name, coord);

	soul::PERSON;

	speedOfRun_ = 0.1;
	
	sprite.setTextureRect(sf::IntRect(0, frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	
}

void Person::control(Camera &camera) {

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
                camera.setCoordView(border_);
        }

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                dir_ = dir::LEFT;
		dir_idle_ = dir_idle::LEFT;
                state_ = state::RUN;
                frame_ += FRAME_SPEED;

                if(frame_ >= run_) 
                        frame_ = std::fmod(frame_, run_);

                sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
                camera.setCoordView(border_);
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
