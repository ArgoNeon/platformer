#include <SFML/Graphics.hpp>

#include "../include/gameObjInanimate.hpp"
#include "../include/gameTile.hpp"

GameObjInanimate::GameObjInanimate(float X, float Y, int W, int H, bool S) {
	position = {X, Y};
	size = {W, H};
	solidity = S;
}

void GameObjInanimate::setSolidity(bool S) {
	solidity = S;
}

void GameObjInanimate::setSprite(GameTile tile){
	
}

bool GameObjInanimate::getSolidity() {

}
