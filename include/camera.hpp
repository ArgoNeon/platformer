#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>

class Camera{
	private:
		sf::View view;
		float w, h;
		float speed;
	public:	
		Camera(float x, float y, float w, float h, float speed, float wind_w, float wind_h);
		sf::View getView();
		void viewMap(float time);
		void getCoordinateView(float x,float y);

};

#endif// VIEW_H
