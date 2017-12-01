#pragma once
#include <SFML\Graphics.hpp>
#include "EnemyTypes.h"
class Enemy
{
public:
	Enemy();
	~Enemy();
	int Type;
	//might include a pointer to player here, let's each ai requestion position and bool for moving
};

