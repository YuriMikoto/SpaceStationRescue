#pragma once
#include <SFML\Graphics.hpp>
#include "TileTypes.h"
class Block
{
public:
	Block();
	Block(sf::Vector2f position, sf::Vector2f dimensions, int w);
	~Block();
	sf::Vector2f pos;
	sf::Vector2f size;
	sf::Vector2f center;
	int weight;//for pathfinding
	int type;
	tileTypes tileType;

	void setTileType(int i);
	void setTileType(tileTypes i);
	int returnTileTypeNum();
	tileTypes returnTiletype();
};

