#include <string>

#include "../include/game.hpp"

namespace gameModel {

Game::Game() {
	window.create(sf::VideoMode(WINDOW_W, WINDOW_H), "GAME", sf::Style::Default);
}

void Game::startMusic() {
	if (!music.openFromFile("music/music_0.wav"))
        	throw std::invalid_argument ("Music  doesn't open\n");

        music.play();
        music.setLoop(true);
}

void Game::start(std::string nameMap) {
        map.initMap(nameMap);

	hero.initPerson("hero", map.getHeroCoord(), map.getWidth());
	
        camera.initCamera(hero.getBorder(), map.getPixels());

        startMusic();

  	while (window.isOpen()) {
        time_ = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time_ = time_/1000;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
	window.setView(camera.getView());
        camera.viewMap(time_);
	hero.control(time_, camera);
        hero.update(time_, map);
        window.clear();
        window.draw(map.sprite_back);
        map.drawTiles(window);
        window.draw(hero.sprite);
        window.display();
    }
}
}	//namespace gameModel
