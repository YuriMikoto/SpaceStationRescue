#include "Player.h"



Player::Player()
{
	position = sf::Vector2f(800, 600);
	velocity = 0;
	orientation = 0; //Facing north.
	maxSpeed = 8;
	thrustSpeed = 0.1;
	frictionDiv = 1.1;
	rotSpeed = 1;
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

void Player::Fire()
{
	sf::Vector2f bulletPos = position;
	bulletPos.x += (texture.getSize().y/5) * std::sin(orientation * pi / 180);
	bulletPos.y -= (texture.getSize().y/5) * std::cos(orientation * pi / 180);
	bullets.push_back(new Bullet(bulletPos, orientation));
}

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

std::vector<Bullet*> Player::getBullets()
{
	return bullets;
}

int Player::getHP()
{
	return hp;
}

void Player::damageHP(int dmg)
{//Reduces the player's HP. Input a negative value to restore HP.
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