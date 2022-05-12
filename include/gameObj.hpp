#ifndef GAMEOBJ_HPP
#define GAMEOBJ_HPP

class GameObj {
	public:
		GameObj(float X, float Y, float W, float H);
		void setCoordinate(float X, float Y);
		void setSize(float W, float H);
		sf::Vector2f getCoordinate();
		sf::Vector2f getSize();
	private:
		sf::Vector2f position;
		sf::Vector2f size;
};

#endif //GAMEOBJ_HPP
