// author Peter Lowe
#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Worker.h"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:
	const int WORKER_COUNT = 3; //Number of workers that the game generates at startup. 

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void checkStateChange();
	
	void setupFontAndText();
	void setupSprite();
	void initializeObjects();
	void initializeCamera();
	void updateCamera();

	sf::RenderWindow m_window; // main SFML window
	sf::View camera;
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_gameOverMessage; // text used for message on screen
	sf::Text m_mainMenuMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	sf::RectangleShape m_hpGauge; //A rectangle for the HP gauge.
	sf::RectangleShape m_hpGaugeBack; //Rectangle for the black back of the HP gauge.
	bool m_exitGame; // control exiting game
	enum class GameState {
		MAIN_MENU,
		GAME_MODE,
		GAME_OVER
	};
	GameState gameState;

	Player p1;

	std::vector<Worker*> workers;
};

#endif // !GAME
