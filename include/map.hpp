#ifndef MAP_HPP
#define MAP_HPP

#define TILE_HEIGHT  16
#define TILE_WIDTH 16

class Map{
	private:
                sf::Vector2f pixels_;
                sf::Vector2f tiles_;	
		sf::Vector2f hero_coord_;
		long int width_;		
	public:
		std::string name_;

		sf::Image image_back;
		sf::Image image_tile;

                sf::Texture texture_back;
		sf::Texture texture_tile;

                sf::Sprite sprite_back;
		sf::Sprite sprite_tile;

		std::vector<char> mapOfTiles_;
		
		std::vector<char>::size_type getTileFromCoord(sf::Vector2f coord);

		void loadMap();
		void initMap(std::string name);	
		
		void readMapOfTiles();
		void writeMapOfTiles();

		void readSize();
		void writeSize() const;

		void setPixels(sf::Vector2f);
		void setTiles(sf::Vector2f);
		void setHeroCoord(sf::Vector2f);
		void setWidth(long int width);
		
		sf::Vector2f getHeroCoord() const;
		sf::Vector2f getPixels() const;
		sf::Vector2f getTiles() const;
		long int getWidth() const;

		void drawTiles(sf::RenderWindow &);	
		
		Map() {}
		~Map() = default;
};

#endif//MAP_HPP
