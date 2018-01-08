#include "Bullet.h"
#include <iostream>

/**
 * Constructor function.
 *
 * @param pos - Bullet's starting position. 
 */
Bullet::Bullet(sf::Vector2f pos, float angle)
	: position(pos), orientation(angle), velocity(10), timetolive(100)
{
	SetupSprite();
}

/**
 * Destructor function.
 */
Bullet::~Bullet()
{

}

/**
 * Draw the current bullet on screen. 
 * 
 * @param window - Specifies the window to draw to.
 */
void Bullet::Draw(sf::RenderWindow &window)
{
	spr.setPosition(position);
	spr.setRotation(orientation);
	window.draw(spr);
}

/**
 * Called each frame from game.cpp.
 * Bullets will move in the direction they're facing relative to speed.
 * A bullet whose lifetime is expired will be marked as not alive, for deletion later.
 */
void Bullet::Update()
{
	position.x += velocity * std::sin(orientation * pi / 180);
	position.y -= velocity * std::cos(orientation * pi / 180);
	if (timetolive-- <= 0)
	{
		alive = false;
	}
}

/**
 * Called at game start.
 * Sets up the sprite for use with all future bullets.
 */
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