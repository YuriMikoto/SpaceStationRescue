#include "Player.h"



Player::Player()
{
	position = sf::Vector2f(800, 600);
	velocity = 0;
	orientation = 0; //Facing north.
	maxSpeed = 8;
	thrustSpeed = 0.1;
	frictionDiv = 1.1;
	rotSpeed = 0.02;
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
	if (forward == false || backwards == false)
	{
		velocity /= frictionDiv;
	}
	position.x += velocity * std::sin(orientation * pi/180);
	position.y -= velocity * std::cos(orientation * pi/180);
}

void Player::Thrusters(float acceleration)
{

	if (velocity < maxSpeed&&velocity>maxSpeed*-1)
	{
		velocity += acceleration;
	}



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