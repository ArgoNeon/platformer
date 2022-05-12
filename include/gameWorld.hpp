#ifndef GAMEWORLD_HPP
#define GAMEWORLD_HPP

class GameWorld {
	public:
		sf::Image imageBackground
		sf::Image imageTileSet
		sf::Texture textureBackground
                sf::Texture textureTileSet
		sf::Sprite spriteBackground
                sf::Sprite spriteTileSet

		sf::Vector2i exitPos;
		sf::Vector2i playerPos;
		std::vector<sf::Vector2i> enemyPos;
		std::vector<std::vector<GameTile *> > tiles
		int weight, height;

		GameWorld(int weight, int height);

		void setPlayerPos();
		void setEnemiesPos();
		void setTilesPos();
};

#endif //GAMEWORLD_HPP
