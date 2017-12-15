#pragma once
#include <SFML\Graphics.hpp>

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
};

