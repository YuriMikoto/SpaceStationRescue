#include "Grid.h"



Grid::Grid()
{


	collisionVec.reserve(100);
	loadFiles();
	testingAssignMethod();
	findCollisionTiles();

}

Grid::Grid(int vectorX, int vectorY, int startPos, int)
{
	collisionVec.reserve(100);
	findCollisionTiles();
}

//Grid::Grid(int vectorX, int vectorY)
//{
//	squareVec.reserve(vectorY);
//	for (size_t i = 0; i < vectorY; i++)
//	{
//		squareVec[i].reserve(vectorX);
//	}
//}


Grid::~Grid()
{
}

void Grid::testingAssignMethod()
{
	squareVec.reserve(20);
	std::vector<Square> tempVec;
	Square tempBlock;
	tempBlock.pos.x = 0;
	tempBlock.pos.y = 0;
	tempVec.reserve(20);
	for (size_t i = 0; i < 1; i++)
	{
//		squareVec[i+1].reserve(20);
		for (size_t o = 0; o < 4; o++)
		{
			tempBlock = Square(sf::Vector2f(tileSize*o+100, 100), sf::Vector2f(tileSize, tileSize), 0);
			tempBlock.setTileType(o);
			//tempBlock.setupRect();
			tempVec.push_back(tempBlock);

		}
		squareVec.push_back(tempVec);
		tempVec.clear();
	}

}

void Grid::update()
{
}

void Grid::render()
{
	std::cout << "defunct renderer caled"<<std::endl;
}

void Grid::render(sf::RenderWindow & win)
{	
	for (size_t i = 0; i < squareVec.size(); i++)
	{
		for (size_t o = 0; o < squareVec[i].size(); o++)
		{
			getSpriteType(squareVec[i][o].tileType);
			currentSprite->setPosition(squareVec[i][o].pos);
			win.draw(*currentSprite);
		}
	}
}

std::vector<std::vector<Square>>& Grid::getVector()
{
	// TODO: insert return statement here
	return squareVec;
}

sf::FloatRect Grid::checkCollisionRectangleVector(sf::FloatRect rect)
{
	//return sf::Vector2f();
	sf::FloatRect temp;
	for (size_t i = 0; i < collisionVec.size(); i++)
	{
		if (!collisionVec[i]->rect.intersects(rect, temp))
		{
			temp.top = 0;
			temp.left = 0;
			temp.height = 0;
			temp.width = 0;
		}
	}
	return temp;
}

bool Grid::checkCollisionRectangleBool(sf::FloatRect rect)
{
	bool temp;
	for (size_t i = 0; i < collisionVec.size(); i++)
	{
		temp = collisionVec[i]->rect.intersects(rect);
	}
	return temp;
}

bool Grid::checkCollisionCircleBool(sf::Vector2f originPos, float radius)
{
	float distA, distB, distC;
	bool temp=false;
	for (size_t i = 0; i < collisionVec.size(); i++)
	{
		distA = originPos.x - collisionVec[i]->center.x;
		distA *= distA;
		distB = originPos.y - collisionVec[i]->center.y;
		distB *= distB;
		distC = sqrtf(distA + distB);
		if (distC >= radius + collisionVec[i]->center.y);
		{
			temp = true;
		}
	}
	return temp;
}

void Grid::loadFiles()
{
	wallSpriteRef = &wallSprite;
	spaceSpriteRef = &spaceSprite;
	dirtySpriteRef = &dirtySprite;
	groundSpriteRef = &groundSprite;
	if (!texture.loadFromFile("ASSETS\\IMAGES\\TestTiles.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading tiles" << std::endl;
	}
	tileSize = texture.getSize().x / 4;
	groundSpriteRef->setTexture(texture);
	wallSpriteRef->setTexture(texture);
	spaceSpriteRef->setTexture(texture);
	dirtySpriteRef->setTexture(texture);

	groundSpriteRef->setTextureRect(sf::IntRect(0, 0, tileSize, tileSize));
	wallSpriteRef->setTextureRect(sf::IntRect(tileSize, 0, tileSize, tileSize));
	spaceSpriteRef->setTextureRect(sf::IntRect(tileSize * 2, 0, tileSize, tileSize));
	dirtySpriteRef->setTextureRect(sf::IntRect(tileSize * 3, 0, tileSize, tileSize));
	
}

void Grid::findCollisionTiles()
{
	for (size_t i = 0; i < squareVec.size(); i++)
	{
		for (size_t o = 0; o < squareVec[i].size(); o++)
		{
			if (squareVec[i][o].tileType == wall)
			{
				collisionVec.push_back(&squareVec[i][o]);
			}
		}
	}
}

void Grid::getSpriteType(tileTypes type)
{
	switch (type)
	{
	case ground:
		currentSprite = &groundSprite;
		break;
	case wall:
		currentSprite = &wallSprite;
		break;
	case space:
		currentSprite = &spaceSprite;
		break;
	case dirtyFloor:
		currentSprite = &dirtySprite;
		break;
	default:
		break;
	}
}

