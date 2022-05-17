#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

#include "../include/person.hpp"
#include "../include/functions.hpp"

void Person::control(float time, Camera &camera) {
	switch(onGround_) {
	case true:

        	if(!((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))))
			idle();

       		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			runRight(camera);

     		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
			runLeft(camera);

       		if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			//sf::Vector2f camera_coord = camera.getCoord();
        	  	dir_attack_ = dir_attack::UP;
	
                	/*if (camera_coord.y > CAMERA_H2) {
                		camera_coord.y -= CAMERA_SPEED * time;
              			camera.getView().move(0, -CAMERA_SPEED * time);
               		}

              		 camera.setCoordView(camera_coord);*/
        	}

        	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			//sf::Vector2f camera_coord = camera.getCoord();
                	dir_attack_ = dir_attack::DOWN;
                
			/*if (camera_coord.y < border_.y) {
                		camera_coord.y += CAMERA_SPEED * time;
                		camera.getView().move(0, CAMERA_SPEED * time);
                	}

                	camera.setCoordView(camera_coord);*/
       		}
		
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (onGround_) && (jump_clock_.getElapsedTime().asMilliseconds() > 150)) {
			speed_.y = -speedOfJump_;
			jump(camera);
			onGround_ = false;
		}

		break;
	case false:
		if (speed_.y > 0) {
 
			if(!((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))))
                	        fall(camera);
		
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                        	fallRight(camera);

                	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                        	fallLeft(camera);
		} else {
			if(!((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A))))
                                jump(camera);
			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
                                jumpRight(camera);

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
                                jumpLeft(camera);
		}
		break;	
	}
}

void Person::jump(Camera &camera) {
        state_ = state::JUMP;
        frame_ += frame_speed_;

        if(frame_ >= jump_)
                frame_ = std::fmod(frame_, jump_);
	
	if (dir_ == dir::RIGHT)
		sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	else
	        sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y)); 
}

void Person::fall(Camera &camera) {
        state_ = state::FALL;
        frame_ += frame_speed_;

        if(frame_ >= fall_)
                frame_ = std::fmod(frame_, fall_);

	if (dir_ == dir::RIGHT)
        	sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	else 
		sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
}

void Person::fallRight(Camera &camera) {
	dir_ = dir::RIGHT;
        dir_attack_ = dir_attack::RIGHT;
        state_ = state::FALL;
        frame_ += frame_speed_;
	speed_.x = speedOfRun_;

        if(frame_ >= fall_)
                frame_ = std::fmod(frame_, fall_);

        sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	camera.setCoordView({border_.x, camera.getCoord().y});
}

void Person::fallLeft(Camera &camera) {
        dir_ = dir::LEFT;
        dir_attack_ = dir_attack::LEFT;
        state_ = state::FALL;
        frame_ += frame_speed_;
	speed_.x = -speedOfRun_;

        if(frame_ >= fall_)
                frame_ = std::fmod(frame_, fall_);

        sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
        camera.setCoordView({border_.x, camera.getCoord().y});
}

void Person::jumpRight(Camera &camera) {
	dir_ = dir::RIGHT;
	dir_attack_ = dir_attack::RIGHT;
        state_ = state::JUMP;
        frame_ += frame_speed_;
	speed_.x = speedOfRun_;

        if(frame_ >= jump_)
                frame_ = std::fmod(frame_, jump_);

        sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	camera.setCoordView({border_.x, camera.getCoord().y});

}

void Person::jumpLeft(Camera &camera) {
	dir_ = dir::LEFT;
	dir_attack_ = dir_attack::LEFT;
        state_ = state::JUMP;
        frame_ += frame_speed_;
	speed_.x = -speedOfRun_;

        if(frame_ >= jump_)
                frame_ = std::fmod(frame_, jump_);

        sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
	camera.setCoordView({border_.x, camera.getCoord().y});
}

void Person::idle() {
	state_ = state::IDLE;
        frame_ += frame_speed_;

	if(frame_ >= idle_)
        	frame_ = std::fmod(frame_, idle_);

	if (dir_ == dir::RIGHT)
       		sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
  	else
        	sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
}

void Person::runRight(Camera &camera) {
	dir_ = dir::RIGHT;
        dir_attack_ = dir_attack::RIGHT;
        state_ = state::RUN;
        frame_ += frame_speed_;

     	if(frame_ >= run_)
        	frame_ = std::fmod(frame_, run_);

        sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
 	camera.setCoordView(border_);
}

void Person::runLeft(Camera &camera) {
	dir_ = dir::LEFT;
	dir_attack_ = dir_attack::LEFT;
        state_ = state::RUN;
        frame_ += frame_speed_;

        if(frame_ >= run_)
        	frame_ = std::fmod(frame_, run_);

   	sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
       	camera.setCoordView(border_);

}

void Vessel::interactWithMap(Map &map) {
	bool ground = onGround_;
        coord_ld_ = map.getTileFromCoord(coord_);
        coord_ld_str_ = coord_ld_ / mapWidth_;
        coord_ld_col_ = coord_ld_ %  mapWidth_;

        border_ld_ = map.getTileFromCoord(border_);
        border_ld_str_ = border_ld_ / mapWidth_;
        border_ld_col_ = border_ld_ %  mapWidth_;

        for (std::vector<char>::size_type str = coord_ld_str_; str <= border_ld_str_; str++)
                for (std::vector<char>::size_type col = coord_ld_col_; col <= border_ld_col_; col++)
                        if (map.mapOfTiles_[str * mapWidth_ + col] == 'g') {
				//printf("%f %ld\n", coord_.y, str * TILE_HEIGHT);
                                if ((speed_.y > 0) && (border_ld_str_ == str) && (coord_.x + 0.5 < (col + 1) * TILE_WIDTH ) && (border_.y - 0.5 < str * TILE_HEIGHT) && (border_.x - 0.5 > col * TILE_WIDTH)) {
                                        if (!ground)
						jump_clock_.restart();

					speed_.y = 0;
                                        onGround_ = true;
                                }

                                if ((speed_.y < 0) && (coord_ld_str_ == str) && (coord_.x + 0.5 < (col + 1) * TILE_WIDTH ) && (coord_.y + 0.5 < (str + 1) * TILE_HEIGHT) && (border_.x - 0.5 > col * TILE_WIDTH))

                                        speed_.y = 0;

				if (onGround_ && (str < border_ld_str_)) {
					if ((speed_.x > 0) && (border_ld_col_ == col))
                                       		speed_.x = -0.0001;

                                	if ((speed_.x < 0) && (coord_ld_col_ == col))
                                        	speed_.x = 0.0001;

				} else if (!onGround_) {
					if ((speed_.x > 0) && (border_ld_col_ == col))
                                 	       speed_.x = -0.0001;

                              		if ((speed_.x < 0) && (coord_ld_col_ == col))
                                        	speed_.x = 0.0001;
				}
				}
}

void Vessel::update(float time, Map &map) {
        switch(state_) {
	case state::IDLE:
		setSpeed({0, 0});
		break;
        case state::RUN:
                setSpeed({speedOfRun_, 0});
                break;
        case state::JUMP:
                break;
	case state::FALL:
		break;	
	default:
		break;	
        }
	
	if (speed_.y < speedOfRun_) {
		speed_.y += acel_ * time;
		if (speed_.y > speedOfRun_)
			speed_.y = speedOfRun_;
	}

	interactWithMap(map);

        coord_ += speed_ * time;
        border_ += speed_ * time;
        coord_frame_ += speed_ * time;

        sprite.setPosition(coord_frame_);
}

void Vessel::readStateTable() {
        std::ifstream in;
        in.open("data/" + name_ + "/state.dat");
       
	in >> idle_;
	in >> run_;
	in >> jump_;
	in >> fall_;
	in >> attack_;
	in >> hurt_;
	in >> death_;

        in.close();
}

void Vessel::writeStateTable() {
        std::ofstream out;
        out.open("data/" + name_ + "/testState.dat");
        out << idle_ << " " << run_ << " " << jump_ << " " << fall_ << " " << attack_ << " " << hurt_ << " " << death_ << std::endl;
        out.close();
}

void Vessel::initVessel(std::string name, sf::Vector2f coord, long int mapWidth) {
	name_ = name;
        coord_ = coord;
	mapWidth_ = mapWidth;
	
	readProperties();
	
	coord_frame_ = {coord_.x - shiftX_.x, coord_.y - shiftY_.x};
	border_ = coord_ + psize_;
	speed_ = {0, 0};

	dir_ = dir::RIGHT;
	dir_attack_ = dir_attack::RIGHT;
	state_ = state::IDLE;	

        loadImageFromFile("images/" + name + "/image.png", image);
        image.createMaskFromColor(sf::Color(255, 255, 255));
        texture.loadFromImage(image);
        sprite.setTexture(texture);
	
	readStateTable();
};

void Vessel::readProperties() {
        std::ifstream in;
        in.open("data/" + name_ + "/properties.dat");
	
	in >> acel_;
	in >> speedOfRun_;
	in >> speedOfJump_;
        in >> frame_border_.x;
        in >> frame_border_.y;
	in >> shiftX_.x;
	in >> shiftX_.y;
	in >> shiftY_.x;
        in >> shiftY_.y;
        in.close();

	psize_.x = frame_border_.x - shiftX_.x - shiftX_.y;
	psize_.y = frame_border_.y - shiftY_.x - shiftY_.y;
	tsize_.x = std::ceil(psize_.x / static_cast<float>(TILE_WIDTH));
	tsize_.y = std::ceil(psize_.y / static_cast<float>(TILE_HEIGHT));
}

void Vessel::writeProperties() const{
        std::ofstream out;
        out.open("data/maps/" + name_ + "/testProperties.dat");
        out << acel_ << " " << speedOfRun_ << " " << speedOfJump_ << std::endl;
        out.close();
}

sf::Vector2f Vessel::getBorder() const {
	return border_;
}

void Vessel::setBorder(sf::Vector2f border) {
	border_ = border;
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
        switch(dir_) {
                case dir::RIGHT:
                        speed_ = speed;
                        break;
                case dir::LEFT:
                        speed_ = {-speed.x, speed.y};
                        break;
        }
}

sf::Vector2f Vessel::getSize() const {
        return sf::Vector2f{psize_.x, psize_.y};
}

void Vessel::setSize(sf::Vector2f psize) {
	psize_ = psize;
}

Vessel::~Vessel() {}

void Person::initPerson(std::string name, sf::Vector2f coord, long int mapWidth) {
	initVessel(name, coord, mapWidth);

	soul::PERSON;
	
	sprite.setTextureRect(sf::IntRect(0, frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	
}
