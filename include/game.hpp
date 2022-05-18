#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <list>

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

	std::list<Imperson *> enemies_list_;

	float time_;
	float Frame_;

	void startMusic();
	void initImpersonList(Map &map);

	public:
	void drawEnemies();
	void controlEnemies();
	void updateEnemies(Map &map);
	void interactSouls(); 
	void start(std::string nameMap);

	Game();
	~Game() = default;		
};
} 	// namespace gameModel

#endif // GAME_HPP
