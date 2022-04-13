#include "../include/camera.hpp"

Camera::Camera(float X, float Y, float W, float H) {
	view.reset(sf::FloatRect(X, Y, W, H));

}

sf::View Camera::getView(){
	return view;
}

void Camera::getCoordinateView(float x,float y) {
        view.setCenter(x, y);
}
