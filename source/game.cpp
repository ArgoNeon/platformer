#include <string>

#include "../include/game.hpp"

namespace gameModel {

Game::Game() {
	window.create(sf::VideoMode(WINDOW_W, WINDOW_H), "GAME", sf::Style::Default);
}

void Game::initImpersonList(Map &map) {
	for (std::vector<sf::Vector2f>::size_type k = 0; k < map.enemies_coord_.size(); k++) {
		Imperson *imperson = new Imperson();
		imperson->initImperson("slime", map.enemies_coord_[k], map.getWidth());
		enemies_list_.push_front(imperson);
	}
}

void Game::controlEnemies() {
	for (auto &enemy: enemies_list_)
                enemy->control(time_);
}

Person *Game::newSoul(Map &map) {
	Person *person = new Person();
	person->initPerson("hero", map.getHeroCoord(), map.getWidth());
	return person;
}

void Game::endGame() {
	for (auto &enemy: enemies_list_)
		delete enemy;
	
	delete hero;
}

void Game::interactSouls() {
	for (auto &enemy1: enemies_list_)
		for(auto &enemy2: enemies_list_) {
			if (enemy1 != enemy2)
                	enemy1->interactWithAnother(dynamic_cast<Vessel *> (enemy2));
		}

	for (auto &enemy: enemies_list_) {
		enemy->interactWithAnother(dynamic_cast<Vessel *> (hero));
		hero->interactWithAnother(dynamic_cast<Vessel *> (enemy));
	}	
}

void Game::updateEnemies(Map &map) {
	for (auto &enemy: enemies_list_)
                enemy->update(time_, map);
}

void Game::drawEnemies() {
	for (auto &enemy: enemies_list_) 
		window.draw(enemy->sprite);
}

void Game::startMusic() {
	if (!music.openFromFile("music/music_0.wav"))
        	throw std::invalid_argument ("Music  doesn't open\n");

        music.play();
        music.setLoop(true);
}

void Game::start(std::string nameMap) {
        map.initMap(nameMap);

	hero = newSoul(map);
	initImpersonList(map);
	
        camera.initCamera(hero->getBorder(), map.getPixels());

        startMusic();

  	while (window.isOpen()) {
        time_ = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time_ = time_/1000;

        while (window.pollEvent(event)) {
            	if (event.type == sf::Event::Closed)
                	window.close();
	
	        if ((event.type == sf::Event::MouseButtonReleased) && (event.mouseButton.button == sf::Mouse::Left))
        	        hero->resetMouseLeft();
	
       		if ((event.type == sf::Event::KeyReleased) && (event.key.code == sf::Keyboard::Space))
                	hero->resetSpace();

        }
        
	window.setView(camera.getView());
        camera.viewMap(time_);

	controlEnemies();	
	hero->control(time_, camera);
	
	interactSouls();

	updateEnemies(map);
        hero->update(time_, map);

        window.clear();

        window.draw(map.sprite_back);
        map.drawTiles(window);

	drawEnemies();
        window.draw(hero->sprite);

        window.display();
   	}
	endGame();
}
}	//namespace gameModel
