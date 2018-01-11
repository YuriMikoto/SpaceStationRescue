#include "Player.h"


/**
 * Constructor function. Sets up several set variables.
 */
Player::Player()
{
	position = sf::Vector2f(800, 600);
	hp = 100;
	velocity = 0;
	orientation = 0; //Facing north.
	maxSpeed = 8;
	thrustSpeed = 0.01f;
	frictionDiv = 1.1f;
	rotSpeed = 0.03f;
}

/**
 * Destructor function.
 */
Player::~Player()
{
}

/**
 * Draws the player sprite on screen.
 * 
 * @param window - Specifies the window to draw to.
 */
void Player::Draw(sf::RenderWindow &window)
{
	spr.setPosition(position);
	spr.setRotation(orientation);
	window.draw(spr);
}

/**
 * Called each frame from game.cpp.
 * Player moves depending on player input. If no input, slows to a stop unless already stopped.
 */
void Player::Update()
{
	if (forward == false || backwards == false)
	{
		velocity /= frictionDiv;
	}
	position.x += velocity * std::sin(orientation * pi / 180);
	position.y -= velocity * std::cos(orientation * pi / 180);
	rect.top = position.y;
	rect.left = position.x;
}

/**
 * Changes the player's speed when W or S are pressed, allowing acceleration and reversing.
 * 
 * @param acceleration - Speed at which velocity increases.
 */
void Player::Thrusters(float acceleration)
{

	if (velocity < maxSpeed&&velocity>maxSpeed*-1)
	{
		velocity += acceleration;
	}



}

/**
 * Rotates the player when A or D is pressed, allowing them to aim.
 * 
 * @param steering - Number of (confirm: degrees/radians?) by which to rotate each frame.
 */
void Player::Steer(float steering)
{
	orientation += steering;
}

float & Player::getRadius()
{
	return radius;
}

sf::Vector2f & Player::getPos()
{
	return position;
}

sf::Vector2f & Player::getOrigin()
{
	return origin+position;
}

sf::FloatRect & Player::getRect()
{
	return rect;
}

/**
 * Command the player to fire their weapon.
 * Creates a bullet at player position pointed in the direction faced.
 */
void Player::Fire()
{
	sf::Vector2f bulletPos = position;
	bulletPos.x += (texture.getSize().y / 5) * std::sin(orientation * pi / 180);
	bulletPos.y -= (texture.getSize().y / 5) * std::cos(orientation * pi / 180);
	bullets.push_back(new Bullet(bulletPos, orientation));
}

/**
 * Iterate through the player's vector of Bullets and draw each one.
 *
 * @param window - Specifies the window to draw to.
 */
void Player::DrawBullets(sf::RenderWindow &window)
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i]->alive)
		{
			bullets[i]->Draw(window);
		}
	}
}

/**
 * Returns the player's vector of Bullets. 
 */
std::vector<Bullet*> Player::getBullets()
{
	return bullets;
}

/**
* Returns the player's current position.
*/
sf::Vector2f Player::getPosition()
{
	return position;
}

/**
* Returns the width and height of the player's sprite as a vector.
*/
sf::Vector2f Player::getDimensions()
{
	return sf::Vector2f(texture.getSize().x * spr.getScale().x, texture.getSize().y * spr.getScale().y);
}

/**
 * Returns the player's remaining health. 
 */
int Player::getHP()
{
	return hp;
}

/**
 * Reduces the player's health by a certain amount. 
 * Cannot reduce health below 0. 
 * 
 * @param dmg - Damage to be dealt in percentage of maximum health. Input a negative value to restore health instead.
 */
void Player::damageHP(int dmg)
{
	hp -= dmg;
	if (hp < 0)
	{
		hp = 0;
	}
	else if (hp > 100)
	{
		hp = 100;
	}
}

/**
 * Called at game start.
 * Sets up the sprite for use with player.
 */
void Player::SetupSprite()
{
	if (!texture.loadFromFile("ASSETS\\IMAGES\\altShip.png"))
	{
		// simple error message if previous call fails
		//std::cout << "problem loading logo" << std::endl;
	}

	spr.setTexture(texture);

	spr.setScale(sf::Vector2f(0.5f, 0.5f));
	spr.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	origin = sf::Vector2f(texture.getSize().x / 2, texture.getSize().y / 2);
	radius = texture.getSize().x / 2;
	rect.width = radius * 2;
	rect.height = radius * 2;
}