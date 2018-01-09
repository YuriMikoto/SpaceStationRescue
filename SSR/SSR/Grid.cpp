#include "Grid.h"



Grid::Grid()
{



	loadFiles();
	testingAssignMethod();


}

Grid::Grid(int vectorX, int vectorY, int startPos, int)
{

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
	std::vector<Block> tempVec;
	Block tempBlock;
	tempBlock.pos.x = 0;
	tempBlock.pos.y = 0;
	tempVec.reserve(20);
	for (size_t i = 0; i < 1; i++)
	{
//		squareVec[i+1].reserve(20);
		for (size_t o = 0; o < 4; o++)
		{
			//squareVec[i][o].setTileType(o);
			tempBlock.pos.x=tileSize*o;
			tempBlock.setTileType(o);
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
			//getSpriteType(squareVec[i][o].tileType);
			switch (squareVec[i][o].tileType)
			{
			case ground:
				currentSprite = groundSpriteRef;
				break;
			case wall:
				currentSprite = wallSpriteRef;
				break;
			case space:
				currentSprite = spaceSpriteRef;
				break;
			case dirtyFloor:
				currentSprite = dirtySpriteRef;
				break;
			default:
				break;
			}
			currentSprite->setPosition(squareVec[i][o].pos);
			win.draw(*currentSprite);
		}
	}
}

std::vector<std::vector<Block>>& Grid::getVector()
{
	// TODO: insert return statement here
	return squareVec;
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

void Grid::getSpriteType(tileTypes type)
{
	//switch (type)
	//{
	//case ground:
	//	currentSprite = &groundSprite;
	//	break;
	//case wall:
	//	currentSprite = &wallSprite;
	//	break;
	//case space:
	//	currentSprite = &spaceSprite;
	//	break;
	//case dirtyFloor:
	//	currentSprite = &dirtySprite;
	//	break;
	//default:
	//	break;
	//}
}

