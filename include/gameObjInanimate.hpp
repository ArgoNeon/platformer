#ifndef GAMEOBJ_INANIMATE_HPP
#define GAMEOBJ_INANIMATE_HPP

class GameObjInanimate: public gameObj{
	public:
		GameObjInanimate(float X, float Y, int W, int H, bool solidity);
		void setSolid(bool S);
		void setSprite();		
		bool getSolidity();
	private:
		sf::Sprite sprite;
		bool solidity;
};

#endif //GAMEOBJ_INANIMATE_HPP

