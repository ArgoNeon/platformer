#ifndef VIEW_HPP
#define VIEW_HPP

#include <SFML/Graphics.hpp>

class Camera{
	private:
		sf::View view;
	public:	
		Camera(float X, float Y, float W, float H);
		sf::View getView();
		void getCoordinateView(float x,float y);

};

#endif// VIEW_H
