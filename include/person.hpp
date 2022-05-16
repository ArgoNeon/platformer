#ifndef PERSON_HPP
#define PERSON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "map.hpp"

#define FRAME_SPEED 0.05

class Vessel {
	protected:
		sf::Vector2f coord_;	//coordinate
		sf::Vector2f speed_;	//speed
		sf::Vector2f acel_;	//aceleration
		sf::Vector2f size_;	//size

		int idle_;
		int run_;
		int jump_;
		int fall_;

		float frame_;
		float speedOfRun_;
	public:
		enum class soul {
			PERSON,
			IMPERSON
		};

		enum class dir {
			RIGHT,
			LEFT,
			UP,
			DOWN
		};

		enum class state {
			IDLE,
			RUN,
			JUMP,
			FALL	
		};

		std::string name_;

		dir dir_;
		state state_;

		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;
		
		void readStateTable();
		void writeStateTable();
	
		void initVessel(std::string name, sf::Vector2f coord);
		
		Vessel() {}
		virtual ~Vessel() = 0;

		void readSize();
		void writeSize() const;

		sf::Vector2f getCoord() const;
		void setCoord(sf::Vector2f coord);
		sf::Vector2f getSpeed() const;
                void setSpeed(sf::Vector2f speed);
		sf::Vector2f getAcel() const;
                void setAcel(sf::Vector2f acel);
		sf::Vector2f getSize() const;
                void setSize(sf::Vector2f size);

		void update(float time);
};

class Person: public Vessel {
	private:
	public:
		void initPerson(std::string name, sf::Vector2f coord);
		void interactWithMap(Map &map);
		void control();
		
		Person() : Vessel() {}
		~Person() override = default;
		
};

class Imperson: public Vessel {
	private:

	public:
		
};

#endif //PERSON_CPP
