#pragma once
#include "TileTypes.h"
#include <vector>
#include <iostream>
#include "Square.h"
#include "Levels.h"
#include "SFML\Graphics.hpp"
class Grid
{
public:
	Grid();
	Grid(int vectorX, int vectorY, int startPos, int);
	~Grid();

	std::vector<std::vector<Square>> squareVec;
	std::vector<Square*> collisionVec;
	void update();
	void render();
	void render(sf::RenderWindow &win);
	std::vector<std::vector<Square>> & getVector();
	sf::Vector2f& checkCollisionRectangleVector(sf::FloatRect rect);
	bool checkCollisionRectangleBool(sf::FloatRect rect);
	bool checkCollisionCircleBool(sf::Vector2f originPos, float radius);
	void loadLevel();

private:
	sf::Texture texture;
	sf::Sprite groundSprite,wallSprite,spaceSprite,dirtySprite;
	sf::Sprite *groundSpriteRef, *wallSpriteRef, *spaceSpriteRef, *dirtySpriteRef;
	sf::Sprite *currentSprite;
	void findCollisionTiles();
	void getSpriteType(tileTypes type);
	void loadFiles();
	void testingAssignMethod();
	int tileSize;
	Levels lvlSet;
};

