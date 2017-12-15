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
	sf::Vector2f size;
	sf::Vector2f center;
	int weight;//for pathfinding
	int tileType;
	int type;
	void setTileType(int i);
	int returnTileType();
};

