#include "Square.h"



Square::Square()
{
}

Square::Square(sf::Vector2f position, sf::Vector2f dimensions, int w):pos(position), size(dimensions), weight(w)
{
	center = pos;


	center.x += size.x / 2;
	center.y += size.y / 2;

	rect.top = pos.y;
	rect.left = pos.x;
	rect.height = size.y;
	rect.width = size.x;
}


Square::~Square()
{
}

void Square::setupRect()
{
	rect.left = pos.x;
	rect.top = pos.y;
	rect.width = size.x;
	rect.height = size.y;
}

void Square::setTileType(int i)
{
	type = i;
	switch (i)
	{
	case 0:
		tileType = ground;
		break;
	case 1:
		tileType = wall;
		break;
	case 2:
		tileType = space;
		break;
	case 3:
		tileType = dirtyFloor;
		break;
	default:
		break;
	}
}

void Square::setTileType(tileTypes i)
{
	tileType = i;
	type = tileType;
}

tileTypes Square::returnTiletype()
{
	return tileType;
}

int Square::returnTileTypeNum()
{
	return type;
}
