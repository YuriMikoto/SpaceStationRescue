#pragma once
#include <SFML\Graphics.hpp>

#include "EnemyTypes.h"
class NPC
{
public:
	NPC();
	virtual ~NPC();
	int Type;
	virtual void Draw(sf::RenderWindow &window)=0;
	virtual void Update() = 0;
	//might include a pointer to player here, let's each ai requestion position and bool for moving
	
	float pi = 3.14159265359f;
};

