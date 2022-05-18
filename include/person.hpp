#ifndef PERSON_HPP
#define PERSON_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "map.hpp"
#include "camera.hpp"

class Vessel {
	protected:
		sf::Vector2f coord_;	//coordinate
		sf::Vector2f border_;
		sf::Vector2f coord_frame_;
		sf::Vector2f frame_border_;

		sf::Vector2f speed_;	//speed
		sf::Vector2f psize_;	//size in pixels
		sf::Vector2i tsize_;	//size in tiles
		sf::Vector2f shiftX_;
		sf::Vector2f shiftY_;
			
		sf::Event event_;
			
		sf::Clock jump_clock_;
		sf::Clock attack_clock_;
                sf::Time elapsed_;
		
		long int mapWidth_;
        	std::vector<char>::size_type coord_ld_;
		std::vector<char>::size_type coord_ld_str_;
        	std::vector<char>::size_type coord_ld_col_;

        	std::vector<char>::size_type border_ld_;
        	std::vector<char>::size_type border_ld_str_;
        	std::vector<char>::size_type border_ld_col_;
	
		int idle_;
		int run_;
		int jump_;
		int fall_;
		int attack_;
		int hurt_;
		int death_;

		float frame_;
		float speedOfRun_;
		float speedOfJump_;
		float acel_;
		const float frame_speed_ = 0.04;
		
		int hitpoints_;
		int damage_;
		
		bool hit_wall_ = false;	
		bool onGround_ = false;
		bool isAttack = false;
		bool life_ = true;

		void readProperties();
		void readStateTable();
		
		void setTextureFrameRight();
		void setTextureFrameLeft();
		
		bool checkLife();
		bool checkRoof(std::vector<char>::size_type &str, std::vector<char>::size_type &col);
		bool checkFloor(std::vector<char>::size_type &str, std::vector<char>::size_type &col);
		void removeStack(std::vector<char>::size_type &str, std::vector<char>::size_type &col);		
		void checkWall(std::vector<char>::size_type &col);
		bool checkChangeDir();
		void interactWithMap(Map &map);

		void initVessel(std::string name, sf::Vector2f coord, long int mapWidth);

		void idle();
                void runRight();
                void runLeft();
                void run();
                void jump();
                void jumpRight();
                void jumpLeft();
                void fall();
                void fallRight();
                void fallLeft();
		bool attack();
		void hurt();
		void death();

	public:
		enum class soul {
			PERSON,
			IMPERSON
		};

		enum class dir_attack {
			RIGHT,
			LEFT,
			UP,
			DOWN
		};
		
		enum class dir {
			RIGHT,
			LEFT
		};

		enum class state {
			IDLE,
			RUN,
			JUMP,
			FALL,
			ATTACK,
			HURT,
			DEATH	
		};

		std::string name_;

		dir dir_;
		dir prevdir_;
		dir_attack dir_attack_;
		state state_;

		sf::Image image;
		sf::Texture texture;
		sf::Sprite sprite;

		Vessel() {}
		virtual ~Vessel() = 0;

		void writeProperties() const;
		void writeStateTable();
		
		sf::Vector2f getBorder() const;
		void setBorder(sf::Vector2f border);
		sf::Vector2f getCoord() const;
		void setCoord(sf::Vector2f coord);
		sf::Vector2f getSpeed() const;
                void setSpeed(sf::Vector2f speed);
		sf::Vector2f getSize() const;
                void setSize(sf::Vector2f size);

		void update(float time, Map &map);
};

class Person: public Vessel {
	private:
		bool space_ = true;
                bool mouse_left_ = true;
	public:	
		void resetMouseLeft();
                void resetSpace();
		
		void initPerson(std::string name, sf::Vector2f coord, long int mapWidth);
		void control(float time, Camera &camera);

		Person() : Vessel() {}
		~Person() override = default;
		
};

class Imperson: public Vessel {
	private:
	public:
		Imperson() : Vessel() {}
                ~Imperson() override = default;
		
		void initImperson(std::string name, sf::Vector2f coord, long int mapWidth);
		void control(float time);		
};

#endif //PERSON_CPP
