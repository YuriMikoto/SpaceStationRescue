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
	sf::Vector2f getPosition();
	sf::Vector2f getDimensions();
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
	float &getRadius();
	sf::Vector2f&getPos();
	sf::Vector2f&getOrigin();
	sf::FloatRect&getRect();
		bool xStop = false, yStop = false;
private:
	float pi = 3.14159265359f;

	int hp; //Health value. Reduced when damaged. Game over if this reaches 0.

	sf::Vector2f position;
	sf::Vector2f origin;
	sf::FloatRect rect;
	float radius;

	float velocity; //Current speed. Paired with orientation.
	float orientation; //Current direction. Paired with velocity.
	sf::Texture texture;
	sf::Sprite spr;
	std::vector<Bullet*> bullets;
};
