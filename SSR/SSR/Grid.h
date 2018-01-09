#pragma once
#include "TileTypes.h"
#include <vector>
#include <iostream>
#include "Square.h"
#include "SFML\Graphics.hpp"
class Grid
{
public:
	Grid();
	Grid(int vectorX, int vectorY, int startPos, int);
	~Grid();

	std::vector<std::vector<Block>> squareVec;
	//std::vector<std::vector<Block&>> collisionVec;
	void update();
	void render();
	void render(sf::RenderWindow &win);
	std::vector<std::vector<Block>> & getVector();


private:
	sf::Texture texture;
	sf::Sprite groundSprite,wallSprite,spaceSprite,dirtySprite;
	sf::Sprite *groundSpriteRef, *wallSpriteRef, *spaceSpriteRef, *dirtySpriteRef;
	sf::Sprite *currentSprite;
	void getSpriteType(tileTypes type);
	void loadFiles();
	void testingAssignMethod();
	int tileSize;
};

