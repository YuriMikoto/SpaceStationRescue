#pragma once
#include <SFML\Graphics.hpp>

#include "EnemyTypes.h"
class Enemy
{
public:
	Enemy();
	virtual ~Enemy();
	int Type;
	virtual void Draw(sf::RenderWindow &window)=0;
	virtual void Update() = 0;
	//might include a pointer to player here, let's each ai requestion position and bool for moving
	
};

