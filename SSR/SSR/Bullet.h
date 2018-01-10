#pragma once
#include <SFML\Graphics.hpp>

class Bullet
{
public:
	Bullet(sf::Vector2f position, float orientation);
	~Bullet();
	void Draw(sf::RenderWindow &window);
	void Update();
	void SetupSprite();

	bool alive = true;
private:
	float pi = 3.14159265359f;

	sf::Vector2f position;
	float velocity; //Current speed. Paired with orientation.
	float orientation; //Current direction. Paired with velocity.
	sf::Texture texture;
	sf::Sprite spr;
	int timetolive;
};
