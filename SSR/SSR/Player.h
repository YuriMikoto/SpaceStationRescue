#pragma once
#include <SFML\Graphics.hpp>
#include <vector>//might be useful for a vector of bullets

#include "Bullet.h"

class Player
{
public:
	Player();
	~Player();
	void Draw(sf::RenderWindow &window);
	void DrawBullets(sf::RenderWindow &window);
	void Update();
	void SetupSprite();
	std::vector<Bullet*> getBullets();
	int getHP();
	void damageHP(int dmg);

	void Thrusters(float acceleration);
	void Steer(float steering);
	void Fire();
	bool forward;
	bool backwards;
	bool left;
	bool right;
	float maxSpeed;
	float thrustSpeed;
	float frictionDiv;
	float rotSpeed;
private:
	float pi = 3.14159265359;

	int hp = 100; //Health value. Reduced when damaged. Game over if this reaches 0.

	sf::Vector2f position;
	float velocity; //Current speed. Paired with orientation.
	float orientation; //Current direction. Paired with velocity.
	sf::Texture texture;
	sf::Sprite spr;
	std::vector<Bullet*> bullets;
};
