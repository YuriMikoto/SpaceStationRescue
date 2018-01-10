#pragma once
#include "NPC.h"

class Worker : public NPC
{
public:
	Worker();
	~Worker();
	void Draw(sf::RenderWindow &window);
	void Update();
	void SetupSprite();
	sf::Vector2f getPosition();
	sf::Vector2f getDimensions();

	bool alive = true;
private:
	sf::Vector2f position;
	float velocity; //Current speed. Paired with orientation.
	float orientation; //Current direction. Paired with velocity.
	sf::Texture texture;
	sf::Sprite spr;
};