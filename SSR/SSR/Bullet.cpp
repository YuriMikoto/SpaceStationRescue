#include "Bullet.h"
#include <iostream>

Bullet::Bullet(sf::Vector2f pos, float angle) 
	: position(pos), orientation(angle), velocity(10), timetolive(100)
{
	SetupSprite();
}

Bullet::~Bullet()
{

}

void Bullet::Draw(sf::RenderWindow &window)
{
	spr.setPosition(position);
	spr.setRotation(orientation);
	window.draw(spr);
}

void Bullet::Update()
{
	position.x += velocity * std::sin(orientation * pi / 180);
	position.y -= velocity * std::cos(orientation * pi / 180);
	if (timetolive-- <= 0)
	{
		alive = false;
	}
}

void Bullet::SetupSprite()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\Bullet.png"))
	{
		// simple error message if previous call fails
		std::cout << "Bullet.png not found." << std::endl;
	}

	spr.setTexture(texture);

	spr.setScale(sf::Vector2f(0.5f, 0.5f));
	spr.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}