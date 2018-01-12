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
 * Activates a held powerup.
 * Effect depends on the powerup type in the used slot.
 *
 * @param which - Indicates which slot to use. Value of 0 indicates Q key, value of 1 indicates E key.
 */
void Player::activatePowerup(bool which)
{
	if (which == 0)
	{//If 0 is passed in, Q key was pressed; use the powerup in that slot.
		if (powerupQ == Powerup::HEALING)
		{
			damageHP(-50);
		}

		powerupQ = Powerup::NONE;
	}
	else
	{//If 1 is passed in, E key was pressed; use the powerup in that slot.
		if (powerupE == Powerup::HEALING)
		{
			damageHP(-50);
		}

		powerupE = Powerup::NONE;
	}

	//Remove powerup from inventory.
}

/**
 * When a powerup is picked up, this adds it to the player's inventory.
 * Attempts to find an empty slot and add it there. If none exists, the powerup is not picked up.
 * Returns true if the item was successfully added, to indicate it should be removed from the game world. False means it should stay.
 * 
 * @param item - Type of powerup to be added.
 */
bool Player::addPowerup(int item)
{
	if (powerupQ == Powerup::NONE)
	{
		powerupQ = item;
		return true;
	}
	else if (powerupE == Powerup::NONE)
	{
		powerupE = item;
		return true;
	}
	return false;
}

/**
 * Returns the type of the powerup in the stated slot.
 *
 * @param which - Indicates which slot to use. Value of 0 indicates Q key, value of 1 indicates E key.
 */
int Player::getPowerup(bool which)
{
	if (which == 0)
	{
		return powerupQ;
	}
	else
	{
		return powerupE;
	}
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
	if (!texture.loadFromFile("ASSETS\\IMAGES\\PlayerShip.png"))
	{
		// simple error message if previous call fails
		//std::cout << "problem loading logo" << std::endl;
	}

	spr.setTexture(texture);

	spr.setScale(sf::Vector2f(0.5f, 0.5f));
	spr.setOrigin(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f);
}