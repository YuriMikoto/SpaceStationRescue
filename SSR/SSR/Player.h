#pragma once
#include <SFML\Graphics.hpp>
#include <vector>//might be useful for a vector of bullets
class Player
{
public:
	Player();
	~Player();
	void Draw(sf::RenderWindow &window);
	void Update();
	void SetupSprite();

	void Thrusters(float acceleration);
	void Steer(float steering);
	bool forward;
	bool backwards;
	bool left;
	bool right;
	float maxSpeed=8;
	float thrustSpeed=0.1;
	float frictionDiv = 1.1;
	float rotSpeed=0.02;
private:
	float pi = 3.14159265359;

	sf::Vector2f position;
	float velocity; //Current speed. Paired with orientation.
	float orientation; //Current direction. Paired with velocity.
	sf::Texture texture;
	sf::Sprite spr;
};

