#include "Powerup.h"

/**
 * Constructor function. When created, randomly assigns a type.
 * Currently, since only one type exists, it just selects the existing type.
 */
Powerup::Powerup()
{
	//type = (rand() % (ENUM_END-1)) +1; //Uncomment this if more than one powerup ever gets added in.
	type = PowerupType::HEALING; //Until then, we'll just use this basic type.

	position = sf::Vector2f(rand() % 1600, rand() % 1200); //Spawns at a random point on screen.

	SetupSprite();
}

/**
 * Destructor function.
 */
Powerup::~Powerup()
{

}

/**
 * Draws the powerup at its current position on the screen.
 * @param window - Specifies the window to draw to.
 */
void Powerup::Draw(sf::RenderWindow &window)
{
	spr.setPosition(position);
	window.draw(spr);
}

/**
* Called at game start.
* Sets up the sprite for use with the current powerup.
*/
void Powerup::SetupSprite()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\PowerupField.png"))
	{
		// simple error message if previous call fails
		//std::cout << "problem loading logo" << std::endl;
	}

	spr.setTexture(texture);

	spr.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

/**
 * Returns type value of this powerup object.
 */
int Powerup::getType()
{
	return type;
}

/**
 * Returns the worker's current position.
 */
sf::Vector2f Powerup::getPosition()
{
	return position;
}

/**
 * Returns the width and height of the worker's sprite as a vector.
 */
sf::Vector2f Powerup::getDimensions()
{
	return sf::Vector2f(texture.getSize().x * spr.getScale().x, texture.getSize().y * spr.getScale().y);
}