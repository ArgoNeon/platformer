#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "person.hpp"
#include "camera.hpp"
#include "map.hpp"

#define WINDOW_W 1920
#define WINDOW_H 1080

namespace gameModel {
class Game {
	private:
	sf::RenderWindow window;
        sf::Clock clock;
	sf::Event event;
	sf::Music music;

        Camera camera;
	Map map;
        Person hero;

	float time_;
	float Frame_;

	public:
	void start(std::string nameMap);
	void startMusic();

	Game();
	~Game() = default;		
};
} 	// namespace gameModel

#endif // GAME_HPP
