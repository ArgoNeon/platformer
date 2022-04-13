#include <SFML/Graphics.hpp>

#include "include/person.hpp"
#include "include/camera.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "GAME", sf::Style::Default);
    
    Person hero("Ghost.png", 50, 50, 600, 450);
    Camera camera(50, 50, 1200, 1000);

    float Frame;
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
		hero.speed = 0.1;
		Frame += 0.2;
	     	if(Frame >= 3) 
	       		Frame -= 3;
 		hero.sprite.setTextureRect(sf::IntRect(600 * int(Frame) + 600, 0, -600, 450));	
		camera.getCoordinateView(hero.getCoordinateX(), hero.getCoordinateY());
	}

	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || (sf::Keyboard::isKeyPressed(sf::Keyboard::D)))) {
		hero.dir = 0;
                hero.speed = 0.1;
		Frame += 0.2;
                if(Frame >= 3)
                        Frame -= 3;
                hero.sprite.setTextureRect(sf::IntRect(600 * int(Frame), 0, 600, 450));
		camera.getCoordinateView(hero.getCoordinateX(), hero.getCoordinateY());
	}

	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || (sf::Keyboard::isKeyPressed(sf::Keyboard::W)))) {
                hero.dir = 3;
                hero.speed = 0.1;
		hero.sprite.setTextureRect(sf::IntRect(0, 450, 600, 450));
		camera.getCoordinateView(hero.getCoordinateX(), hero.getCoordinateY());
	}

	if((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || (sf::Keyboard::isKeyPressed(sf::Keyboard::S)))) {
		hero.dir = 2;
                hero.speed = 0.1;
		hero.sprite.setTextureRect(sf::IntRect(0, 450, 600, 450));
		camera.getCoordinateView(hero.getCoordinateX(), hero.getCoordinateY());
        }

	hero.update(time);

	window.setView(camera.getView());
        window.clear();
        window.draw(hero.sprite);
        window.display();
    }

    return 0;
}
