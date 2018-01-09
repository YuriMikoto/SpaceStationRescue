#include "Square.h"



Block::Block()
{
}

Block::Block(sf::Vector2f position, sf::Vector2f dimensions, int w):pos(position), size(dimensions), weight(w)
{
	center.x = size.x / 2;
	center.y = size.y / 2;
}


Block::~Block()
{
}

void Block::setTileType(int i)
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

void Block::setTileType(tileTypes i)
{
	tileType = i;
	type = tileType;
}

tileTypes Block::returnTiletype()
{
	return tileType;
}

int Block::returnTileTypeNum()
{
	return type;
}
