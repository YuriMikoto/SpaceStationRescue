#pragma once
#include <SFML\Graphics.hpp>

//Creates an object in the game world. When game object is touched, alters a Player variable to indicate the player now possesses a powerup. 
//There are two slots for held powerups, one for the Q key and one for the E key.
//In Game, when the Q or E key is pressed, the player uses the powerup in that slot by calling powerupQ.Activate(); or powerupE.Activate();.
class Powerup
{
public:
	Powerup();
	~Powerup();

	void Draw(sf::RenderWindow &window);

	enum PowerupType {//Only one type available at the moment.
		NONE,
		HEALING,
		ENUM_END //Above maximum value for the random number generator to generate. Makes implementing new types slightly easier.
	};

	void SetupSprite();

	int getType();
	sf::Vector2f getPosition();
	sf::Vector2f getDimensions();

	bool alive = true;

private:
	sf::Vector2f position;
	sf::Texture texture;
	sf::Sprite spr;
	int type;
};