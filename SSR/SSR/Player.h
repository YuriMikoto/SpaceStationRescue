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
	void HandleInput();
private:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Texture texture;
	sf::Sprite spr;

};

