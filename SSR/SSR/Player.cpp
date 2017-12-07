#include "Player.h"



Player::Player()
{
	position = sf::Vector2f(800, 600);
	velocity = 0;
	orientation = 0; //Facing north.
}

Player::~Player()
{
}

void Player::Draw(sf::RenderWindow &window)
{
	spr.setPosition(position);
	spr.setRotation(orientation);
	window.draw(spr);
}

void Player::Update()
{
	position.x += velocity * std::sin(orientation * pi/180);
	position.y -= velocity * std::cos(orientation * pi/180);
}

void Player::Thrusters(float acceleration)
{
	velocity += acceleration;
}

void Player::Steer(float steering)
{
	orientation += steering;
}

void Player::SetupSprite()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\PlayerShip.png"))
	{
		// simple error message if previous call fails
		//std::cout << "problem loading logo" << std::endl;
	}

	spr.setTexture(texture);

	spr.setScale(sf::Vector2f(0.5f, 0.5f));
	spr.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}