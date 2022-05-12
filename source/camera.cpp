#include "../include/camera.hpp"

Camera::Camera(float X, float Y, float W, float H, float Speed, float wind_w, float wind_h) {
	w = wind_w;
	h = wind_h;
	speed = Speed;
	view.reset(sf::FloatRect(0, 0, W, H));
	view.setCenter(X, Y);
}

sf::View Camera::getView(){
	return view;
}

void Camera::getCoordinateView(float x,float y) {
	/*if (x < (w / 2)) 
		x = (w / 2);
	if (y < (h / 2)) 
		y = (w / 2);
	if (y > (w / 2))
		y = (w / 2);*/
        view.setCenter(x, y);
}

void Camera::viewMap(float time) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		view.move(speed * time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		view.move(0, speed * time);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		view.move(-speed * time, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		view.move(0, -speed * time);
	}
}
