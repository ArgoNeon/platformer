#include <SFML/Graphics.hpp>

#include "../include/camera.hpp"

void Camera::initCamera(sf::Vector2f coord, sf::Vector2f sizeMap) {
	
	border_ = {sizeMap.x - static_cast<float>(CAMERA_W2), sizeMap.y - static_cast<float>(CAMERA_H2)};
	
	coord_ = finitCoord(coord);
	
	view.reset(sf::FloatRect(0, 0, CAMERA_W, CAMERA_H));
	view.setCenter(coord_);
}

sf::View Camera::getView() const{
	return view;
}

sf::Vector2f Camera::finitCoord(sf::Vector2f coord) {
	sf::Vector2f finit_coord;

	if (coord.x < CAMERA_W2)
                finit_coord.x = CAMERA_W2;

        else if (coord.x > border_.x)
                finit_coord.x = border_.x;
        else
                finit_coord.x = coord.x;

        if (coord.y < CAMERA_H2)
                finit_coord.y = CAMERA_H2;

        else if(coord.y > border_.y)
                finit_coord.y = border_.y;

        else
                finit_coord.y = coord.y;

	return finit_coord;
}

void Camera::setCoordView(sf::Vector2f coord) {
        view.setCenter(finitCoord(coord));
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
