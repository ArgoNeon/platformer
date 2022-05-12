#ifndef GAMETILE_HPP
#define GAMETILE_HPP

#define GAMETILE_W 24
#define GAMETILE_H 24

class GameTile{
private:
	sf::Image image;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f position;
public:
	GameTile(std::string file, float X, float Y);
};

#endif //GAMETILE_HPP

