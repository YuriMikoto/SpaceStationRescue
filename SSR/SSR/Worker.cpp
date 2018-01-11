#include "Worker.h"

/**
* Constructor function. Sets up several set variables.
*/
Worker::Worker()
{
	position = sf::Vector2f(rand() % 1600, rand() % 1200); //Spawns at a random point on screen.
	velocity = 2.0f;
	orientation = rand() % 360; //Random facing.

	SetupSprite();
}

/**
* Destructor function.
*/
Worker::~Worker()
{

}

/**
* Draws the worker sprite on screen.
*
* @param window - Specifies the window to draw to.
*/
void Worker::Draw(sf::RenderWindow &window)
{
	spr.setPosition(position);
	spr.setRotation(orientation);
	window.draw(spr);
}

/**
 * Called each frame from game.cpp.
 * Worker will always be moving forward in the direction they're facing at a very slow pace. 
 * Each tick, they will also slightly alter their movement direction.
 * At this time, they cannot move off the screen.
 * TODO: Functionality to prevent running into walls.
 */
void Worker::Update()
{
	orientation += (rand() % 3) - 1;

	position.x += velocity * std::sin(orientation * pi / 180);
	position.y -= velocity * std::cos(orientation * pi / 180);

	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x > 1600)
	{
		position.x = 1600;
	}
	if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.y > 1200)
	{
		position.y = 1200;
	}
}

/**
* Called at game start.
* Sets up the sprite for use with all workers.
*/
void Worker::SetupSprite()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\shiptoast.png"))
	{
		// simple error message if previous call fails
		//std::cout << "problem loading logo" << std::endl;
	}

	spr.setTexture(texture);

	spr.setScale(sf::Vector2f(1.5f, 1.5f));
	spr.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
}

/**
* Returns the worker's current position.
*/
sf::Vector2f Worker::getPosition()
{
	return position;
}

/**
* Returns the width and height of the worker's sprite as a vector.
*/
sf::Vector2f Worker::getDimensions()
{
	return sf::Vector2f(texture.getSize().x * spr.getScale().x, texture.getSize().y * spr.getScale().y);
}

void Worker::setPosition(sf::Vector2f newPos)
{
	position = newPos;
}
