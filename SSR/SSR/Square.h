#pragma once
#include <SFML\Graphics.hpp>
#include "TileTypes.h"
class Square
{
public:
	Square();
	Square(sf::Vector2f position, sf::Vector2f dimensions, int w);
	~Square();
	sf::Vector2f pos;
	sf::FloatRect rect;
	sf::Vector2f size;
	sf::Vector2f center;
	int weight;//for pathfinding
	int type;
	tileTypes tileType;
	void setupRect();
	void setTileType(int i);
	void setTileType(tileTypes i);
	int returnTileTypeNum();
	tileTypes returnTiletype();
};

