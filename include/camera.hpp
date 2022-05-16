#ifndef CAMERA_HPP
#define CAMERA_HPP

#define CAMERA_W 480
#define CAMERA_W2 240
#define CAMERA_H 270
#define CAMERA_H2 120
#define CAMERA_SPEED 0.4

class Camera{
	private:
		sf::View view;
		sf::Vector2f coord_;
		sf::Vector2f border_;
	public:	
		sf::Vector2f finitCoord(sf::Vector2f coord);
		void initCamera(sf::Vector2f coord, sf::Vector2f border);

		sf::View getView() const;
		void setCoordView(sf::Vector2f coord);

		void setCoord(sf::Vector2f coord);
		void setBorder(sf::Vector2f border);

		sf::Vector2f getCoord() const;
		sf::Vector2f getBorder() const;
		
		void viewMap(float time);

		Camera() {}
		~Camera() = default;
};

#endif// CAMERA_H
