#include <SFML/Graphics.hpp>

#include "include/person.hpp"
#include "include/camera.hpp"
#include "include/map.hpp"

#define WINDOW_W 1920
#define WINDOW_H 1080
#define HERO_W 256
#define HERO_H 256

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), "GAME", sf::Style::Default);
    Map map("background0.jpg", "tile0.jpg", 105, 66, 1);
    Person hero("Hero.jpg", 100, 100, HERO_W,  HERO_H);
    Camera camera(100, 100, WINDOW_W, WINDOW_H);
    
    float Frame;
    float speed = 0.2;
    float frameSpeed = 0.2;
    sf::Clock clock;

    while (window.isOpen())
    {
	float time = clock.getElapsedTime().asMicroseconds();
	clock.restart();
	time = time/800;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || (sf::Keyboard::isKeyPressed(sf::Keyboard::A)))) {
		hero.dir = 1;
		hero.speed = speed;
		Frame += frameSpeed;
	     	if(Frame >= 3) 
	       		Frame -= 3;
 		hero.sprite.setTextureRect(sf::IntRect(HERO_W * (int(Frame) + 1), 0, -HERO_W, HERO_H));
	}

	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
		hero.dir = 0;
		hero.speed = speed;
		Frame += frameSpeed;
                if(Frame >= 3)
                        Frame -= 3;
                hero.sprite.setTextureRect(sf::IntRect(HERO_W * int(Frame), 0, HERO_W, HERO_H));
	}

	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
                hero.dir = 3;
		hero.speed = speed;
		hero.sprite.setTextureRect(sf::IntRect(0, 0, HERO_W, HERO_H));
	}

	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
		hero.dir = 2;
		hero.speed = speed;
		hero.sprite.setTextureRect(sf::IntRect(0, 0, HERO_W, HERO_H));
        }

	camera.getCoordinateView(hero.getCoordinateX(), hero.getCoordinateY());

	hero.update(time);

	window.setView(camera.getView());
        window.clear();
	window.draw(map.sprite);
        window.draw(hero.sprite);
        window.display();
    }

    return 0;
}
