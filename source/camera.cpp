#include <SFML/Graphics.hpp>

#include "../include/camera.hpp"

void Camera::initCamera(sf::Vector2f coord, sf::Vector2f sizeMap) {
	
	border_ = {sizeMap.x - static_cast<float>(CAMERA_W2), sizeMap.y - static_cast<float>(CAMERA_H2)};
	if (coord.x < CAMERA_W2)
		coord_.x = CAMERA_W2;
	else if (coord.x > border_.x)
		coord_.x = border_.x;
	else 
		coord_.x = coord.x;

	if (coord.y < CAMERA_H2)
		coord_.y = CAMERA_H2;

	else if(coord.y > border_.y)
		coord_.y = border_.y;

	else 
		coord_.y = coord.y;

	view.reset(sf::FloatRect(0, 0, CAMERA_W, CAMERA_H));
	view.setCenter(coord_);
}

sf::View Camera::getView(){
	return view;
}

void Camera::getCoordView(sf::Vector2f coord) {
	/*if (coord.x < (CAMERA_W / 2)) 
		coordx = (CAMERA_W / 2);
	if (y < (h / 2)) 
		y = (w / 2);
	if (y > (w / 2))
		y = (w / 2);*/
        view.setCenter(coord.x, coord.y);
}

void Camera::viewMap(float time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		if (coord_.x < border_.x) {
		coord_.x += CAMERA_SPEED * time;
		view.move(CAMERA_SPEED * time, 0);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (coord_.y < border_.y) {
		coord_.y += CAMERA_SPEED * time;
		view.move(0, CAMERA_SPEED * time);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		if (coord_.x > CAMERA_W2) {
		coord_.x -= CAMERA_SPEED * time;
		view.move(-CAMERA_SPEED * time, 0);
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		if (coord_.y > CAMERA_H2) {
		coord_.y -= CAMERA_SPEED * time;
		view.move(0, -CAMERA_SPEED * time);
		}
	}
}
