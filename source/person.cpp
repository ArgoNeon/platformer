#include <SFML/Graphics.hpp>
#include <cmath>
#include <fstream>
#include <iostream>

#include "../include/person.hpp"
#include "../include/functions.hpp"

void Person::control(float time, Camera &camera) {	
	if (life_ == true) {
	
	/*if (hit_enemy_ && hurt_clock_.getElapsedTime().asMilliseconds() > 500) {
                hurt_clock_.restart();
                isHurt_ = true;
                hit_enemy_ = false;
        }*/
	
	switch(onGround_) {
	case true:
		if(isAttack_ || isHurt_) {
		if(isAttack_) {
			isAttack_ = attack();
			camera.setCoordView(border_);
		}
		
		if(isHurt_ && (hitpoints_ > 0)) {
                        isHurt_ = hurt();
                        camera.setCoordView(border_);
                }
		
		if((isHurt_ && (hitpoints_ <= 0)) || (isDeath_)) {
			life_ = false;
			isDeath_ = death();
                        camera.setCoordView(border_);
                }

		} else {
		
        	if(!((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
			idle();
			camera.setCoordView(border_);
		}
		
       		if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			runRight();
			camera.setCoordView(border_);
		}

     		if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			runLeft();
			camera.setCoordView(border_);
		}

		if(mouse_left_ && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && (attack_clock_.getElapsedTime().asMilliseconds() > 700) && (jump_clock_.getElapsedTime().asMilliseconds() > 150)) {
			frame_ = 0;
			mouse_left_ = false;
			isAttack_ = true;
			attack_clock_.restart();
                        attack();
			camera.setCoordView(border_);
		}
		
		if ((space_ && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (onGround_) && (jump_clock_.getElapsedTime().asMilliseconds() > 150)) {
			onGround_ = false;
			space_ = false;
			speed_.y = -speedOfJump_;
			jump();
			camera.setCoordView(border_);
		}
		}

		break;
	case false:
		if (speed_.y > 0) {
 
			if(!((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
                	        fall();
				camera.setCoordView(border_);
			}
		
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                        	fallRight();
				camera.setCoordView(border_);
			}

                	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                        	fallLeft();
				camera.setCoordView(border_);
			}
		} else {
			if(!((sf::Keyboard::isKeyPressed(sf::Keyboard::D)) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
                                jump();
				camera.setCoordView(border_);
			}
			
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                                jumpRight();
				camera.setCoordView(border_);
			}

                        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                                jumpLeft();
				camera.setCoordView(border_);
			}
		}
		break;	
		} } else {
		frame_ = death_ - 1;
		setTextureFrameRight();
	}
}

void Imperson::control(float time) {
	prevdir_ = dir_;

        switch(onGround_) {
        case true:
               if(isAttack_)
                        isAttack_ = attack();
                else {
		if (attack_clock_.getElapsedTime().asMilliseconds() <= 700)
			idle();
		
		else {
		if (hit_wall_ || hit_ally_ || hit_cliff_) {
			//printf("hit:%d %d %d prd %d d %d\n", hit_wall_, hit_ally_, hit_cliff_, prevdir_, dir_);
			hit_ally_ = false;

			if(dir_ == dir::RIGHT)
				dir_ = dir::LEFT;
			else
				dir_ = dir::RIGHT;
		}

		if ((hit_enemy_) && ((attack_clock_.getElapsedTime().asMilliseconds() > 700))) {
			frame_ = 0;
			hit_enemy_ = false;
			isAttack_ = true;
                        attack_clock_.restart();
                        attack();
		}

                if(dir_ == dir::RIGHT)
                        runRight();
		else
			runLeft();
		}
		}

        case false:
                if (speed_.y > 0) 
			fall();
	break;
	}
}

void Vessel::interactWithAnother(Vessel *another) {
	if (soul_ == another->soul_) {
	if((dir_ == dir::RIGHT) && (border_.x >= another->coord_.x) && (coord_.x <= another->coord_.x) && (border_.y >= another->coord_.y) && (coord_.y <= another->border_.y)) {
		speed_.x = 0;
		hit_ally_ = true;
	}
	
	if((dir_ == dir::LEFT) && (coord_.x <= another->border_.x) && (border_.x >= another->border_.x) && (border_.y >= another->border_.y) && (coord_.y <= another->border_.y)) {
		speed_.x = 0;
                hit_ally_ = true;
	}	
	} else {
	if (another->soul_ == soul::PERSON) {
	if (dir_ == dir::RIGHT) {
		if((border_.x >= another->coord_.x) && (coord_.x <= another->coord_.x) && (border_.y >= another->coord_.y) && (coord_.y <= another->border_.y)) {
			//printf("%d %d\n", border_ld_str_, border_ld_col_);
			hit_enemy_ = true;
       		}
		if ((coord_.x <= another->border_.x) && (border_.x >= another->border_.x) && (border_.y >= another->coord_.y) && (coord_.y <= another->border_.y)) {
			dir_ = dir::LEFT;
			hit_enemy_ = true;			
		}
	}
	
	if (dir_ == dir::LEFT) {
                if((border_.x >= another->coord_.x) && (coord_.x <= another->coord_.x) && (border_.y >= another->coord_.y) && (coord_.y <= another->border_.y)) {
                        //printf("%d %d\n", border_ld_str_, border_ld_col_);
			dir_ = dir::RIGHT;
                        hit_enemy_ = true;
                }
                if ((coord_.x <= another->border_.x) && (border_.x >= another->border_.x) && (border_.y >= another->coord_.y) && (coord_.y <= another->border_.y)) {
                        hit_enemy_ = true;
                }
        }
	}
	}
}

bool Vessel::attack() {
        state_ = state::ATTACK;
        frame_ += frame_speed_;

        if (frame_ < attack_) {

        	if (dir_ == dir::RIGHT)
                	setTextureFrameRight();
        	else
                	setTextureFrameLeft();

		return true;
        } else
		return false;
}

bool Vessel::hurt() {
        state_ = state::HURT;
        frame_ += frame_speed_;

	if (frame_ < hurt_) {

                if (dir_ == dir::RIGHT)
                        setTextureFrameRight();
                else
                        setTextureFrameLeft();

                return true;
        } else
                return false;

}

bool Vessel::death() {
        state_ = state::DEATH;
        frame_ += frame_speed_;

        if (frame_ < death_) {

                if (dir_ == dir::RIGHT)
                        setTextureFrameRight();
                else
                        setTextureFrameLeft();

                return true;
        } else
                return false;

}

void Vessel::jump() {
        state_ = state::JUMP;
        frame_ += frame_speed_;

        if(frame_ >= jump_)
                frame_ = std::fmod(frame_, jump_);
	
	if (dir_ == dir::RIGHT)
		setTextureFrameRight();
	else
	        setTextureFrameLeft();
}

void Vessel::fall() {
        state_ = state::FALL;
        frame_ += frame_speed_;

        if(frame_ >= fall_)
                frame_ = std::fmod(frame_, fall_);

	if (dir_ == dir::RIGHT)
        	setTextureFrameRight();	
	else 
		setTextureFrameLeft();
}

void Vessel::fallRight() {
	dir_ = dir::RIGHT;
        dir_attack_ = dir_attack::RIGHT;
        state_ = state::FALL;
        frame_ += frame_speed_;
	speed_.x = speedOfRun_;

        if(frame_ >= fall_)
                frame_ = std::fmod(frame_, fall_);

       	setTextureFrameRight(); 
}

void Vessel::fallLeft() {
        dir_ = dir::LEFT;
        dir_attack_ = dir_attack::LEFT;
        state_ = state::FALL;
        frame_ += frame_speed_;
	speed_.x = -speedOfRun_;

        if(frame_ >= fall_)
                frame_ = std::fmod(frame_, fall_);

        setTextureFrameLeft();
}

void Vessel::jumpRight() {
	dir_ = dir::RIGHT;
	dir_attack_ = dir_attack::RIGHT;
        state_ = state::JUMP;
        frame_ += frame_speed_;
	speed_.x = speedOfRun_;

        if(frame_ >= jump_)
                frame_ = std::fmod(frame_, jump_);

        setTextureFrameRight();
}

void Vessel::jumpLeft() {
	dir_ = dir::LEFT;
	dir_attack_ = dir_attack::LEFT;
        state_ = state::JUMP;
        frame_ += frame_speed_;
	speed_.x = -speedOfRun_;

        if(frame_ >= jump_)
                frame_ = std::fmod(frame_, jump_);

        setTextureFrameLeft();
}

void Vessel::idle() {
	state_ = state::IDLE;
        frame_ += frame_speed_;

	if(frame_ >= idle_)
        	frame_ = std::fmod(frame_, idle_);

	if (dir_ == dir::RIGHT)
       		setTextureFrameRight();
  	else
        	setTextureFrameLeft();
}

void Vessel::runRight() {
	dir_ = dir::RIGHT;
        dir_attack_ = dir_attack::RIGHT;
        state_ = state::RUN;
        frame_ += frame_speed_;

     	if(frame_ >= run_)
        	frame_ = std::fmod(frame_, run_);

        setTextureFrameRight();
}

void Vessel::runLeft() {
	dir_ = dir::LEFT;
	dir_attack_ = dir_attack::LEFT;
        state_ = state::RUN;
        frame_ += frame_speed_;

        if(frame_ >= run_)
        	frame_ = std::fmod(frame_, run_);

   	setTextureFrameLeft();
}

bool Vessel::checkRoof(std::vector<char>::size_type &str, std::vector<char>::size_type &col) {
	return ((speed_.y < 0) && (coord_ld_str_ == str) && (coord_.x + 0.5 < (col + 1) * TILE_WIDTH ) && (coord_.y + 0.5 < (str + 1) * TILE_HEIGHT) && (border_.x - 0.5 > col * TILE_WIDTH));
}
                
bool Vessel::checkFloor(std::vector<char>::size_type &str, std::vector<char>::size_type &col) {
	return ((speed_.y > 0) && (border_ld_str_ == str) && (coord_.x + 0.5 < (col + 1) * TILE_WIDTH ) && (border_.y - 0.5 < str * TILE_HEIGHT) && (border_.x - 0.5 > col * TILE_WIDTH));
}

void Vessel::removeStack(std::vector<char>::size_type &str, std::vector<char>::size_type &col) {
	if ((speed_.y > 0) && (border_ld_str_ == str) && (coord_.x + 0.5 < (col + 1) * TILE_WIDTH ) && (border_.y - 0.5 > str * TILE_HEIGHT) && (border_.x - 0.5 > col * TILE_WIDTH)) 
		speed_.y = -speedOfRun_;
}

bool Vessel::checkChangeDir() {
	if (prevdir_ != dir_) {
		hit_wall_ = false;
		hit_cliff_ = false;
		return true;
	} else
		return false;
				
}

void Vessel::checkWall(std::vector<char>::size_type &col) {

	if ((speed_.x > 0) && (border_ld_col_ == col)) {
        	speed_.x = -0.0001;
		hit_wall_ = true;
	}

	if ((speed_.x < 0) && (coord_ld_col_ == col)) {
           	speed_.x = 0.0001;
		hit_wall_ = true;
	}
}

void Vessel::interactWithMap(Map &map) {
	int counter = 0;

        coord_ld_ = map.getTileFromCoord(coord_);
        coord_ld_str_ = coord_ld_ / mapWidth_;
        coord_ld_col_ = coord_ld_ %  mapWidth_;

        border_ld_ = map.getTileFromCoord(border_);
        border_ld_str_ = border_ld_ / mapWidth_;
        border_ld_col_ = border_ld_ %  mapWidth_;

	for(std::vector<char>::size_type col = coord_ld_col_; col <= border_ld_col_; col++)
		switch(map.mapOfTiles_[border_ld_str_ * mapWidth_ + col]) {
		case 'g':
			counter++;
			break;
		case '0':
			if (onGround_)
				if (((coord_ld_col_ == col) && (dir_ == dir::LEFT)) || ((border_ld_col_ == col) && (dir_ == dir::RIGHT)))
					hit_cliff_ = true;
			break;
		}

	checkChangeDir();

	if (counter == 0) {
		onGround_ = false;
		hit_cliff_ = false;	
	}

        for (std::vector<char>::size_type str = coord_ld_str_; str <= border_ld_str_; str++)
                for (std::vector<char>::size_type col = coord_ld_col_; col <= border_ld_col_; col++)
                        if (map.mapOfTiles_[str * mapWidth_ + col] == 'g') {
				removeStack(str, col);
                                if (checkFloor(str, col)) {
                                        if (!onGround_)
						jump_clock_.restart();

					speed_.y = 0;
                                        onGround_ = true;
                                }  

                                if (checkRoof(str, col))
                                        speed_.y = 0;

				if (onGround_ && (str < border_ld_str_)) 
					checkWall(col);

				else if (!onGround_)
					checkWall(col);
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
	case state::ATTACK:
		setSpeed({0, 0});
		break;
	case state::HURT:
		setSpeed({0, 0});
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

bool Vessel::checkLife() {

	if (hitpoints_ <= 0)
		life_ = false;

	return life_;
}

void Imperson::initImperson(std::string name, sf::Vector2f coord, long int mapWidth) {
	initVessel(name, coord, mapWidth);

	soul_ = soul::IMPERSON;
	
	sprite.setTextureRect(sf::IntRect(0, frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	
}

void Person::resetMouseLeft() {
	mouse_left_ = true;
}

void Person::resetSpace() {
	space_ = true;
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
	prevdir_ = dir::RIGHT;
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
	

	in >> hitpoints_;
	in >> damage_;
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

void Vessel::setTextureFrameRight() {
	sprite.setTextureRect(sf::IntRect(frame_border_.x * static_cast<int>(frame_), frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
}

void Vessel::setTextureFrameLeft() {
	sprite.setTextureRect(sf::IntRect(frame_border_.x * (static_cast<int>(frame_) + 1), frame_border_.y * static_cast<int>(state_), -frame_border_.x, frame_border_.y));
}

Vessel::~Vessel() {}

void Person::initPerson(std::string name, sf::Vector2f coord, long int mapWidth) {
	initVessel(name, coord, mapWidth);

	soul_ = soul::PERSON;
	
	sprite.setTextureRect(sf::IntRect(0, frame_border_.y * static_cast<int>(state_), frame_border_.x, frame_border_.y));
	
}
