#include "Square.h"



Square::Square()
{
}

Square::Square(sf::Vector2f position, sf::Vector2f dimensions, int w):pos(position), size(dimensions), weight(w)
{
	center.x = size.x / 2;
	center.y = size.y / 2;
}


Square::~Square()
{
}

void Square::setTileType(int i)
{
	tileType = i;
	type = tileType;
}

int Square::returnTileType()
{
	return tileType;
}
