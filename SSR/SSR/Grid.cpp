#include "Grid.h"



Grid::Grid()
{
	testingAssignMethod();
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
	squareVec.reserve(4);
	for (size_t i = 0; i < 4; i++)
	{
		squareVec[i].reserve(4);
	}
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t o = 0; o < 4; o++)
		{
			squareVec[i][o].setTileType(o);
		}

	}
}

void Grid::update()
{
}

void Grid::render()
{
}

std::vector<std::vector<Square>>& Grid::getVector()
{
	// TODO: insert return statement here
	return squareVec;
}

void Grid::loadFiles()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\TestTiles.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading tiles" << std::endl;
	}
	
}
