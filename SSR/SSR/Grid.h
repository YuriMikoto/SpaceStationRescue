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
	void testingAssignMethod();
	std::vector<std::vector<Square>> squareVec;
	void update();
	void render();
	std::vector<std::vector<Square>> & getVector();
	void loadFiles();
	sf::Texture texture;
	sf::Sprite sprite;
};

