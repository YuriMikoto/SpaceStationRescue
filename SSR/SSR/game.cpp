// author Peter Lowe

using namespace std;
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1600, 1200, 32 }, "Space Station Rescue" },
	m_exitGame{ false } //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture

	gameState = GameState::MAIN_MENU;
}


Game::~Game()
{
}

void Game::initializeObjects()
{
	p1 = Player();
	p1.SetupSprite();
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	if (gameState == GameState::GAME_MODE)
	{
		if (p1.forward == true)
		{
			p1.Thrusters(p1.thrustSpeed);
		}
		if (p1.backwards == true)
		{
			p1.Thrusters(p1.thrustSpeed*-1);
		}
		if (p1.left == true)
		{
			p1.Steer(p1.rotSpeed*-1);
		}
		if (p1.right == true)
		{
			p1.Steer(p1.rotSpeed);
		}
	}
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed) // window message
		{
			m_window.close();
		}
		if (event.type == sf::Event::KeyPressed) //user key press
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				m_exitGame = true;
			}

			if (gameState == GameState::GAME_MODE)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					p1.forward = true;
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					p1.backwards = true;
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					p1.left = true;
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					p1.right = true;
				}
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			if (gameState == GameState::GAME_MODE)
			{
				if (event.key.code == sf::Keyboard::W)
				{
					p1.forward = false;
				}
				else if (event.key.code == sf::Keyboard::S)
				{
					p1.backwards = false;
				}
				else if (event.key.code == sf::Keyboard::A)
				{
					p1.left = false;
				}
				else if (event.key.code == sf::Keyboard::D)
				{
					p1.right = false;
				}
				else if (event.key.code == sf::Keyboard::Space)
				{//Fire a bullet.
					p1.Fire();
				}
				else if (event.key.code == sf::Keyboard::BackSpace)
				{//Debug command. Reduces player's HP.
					p1.damageHP(20);
				}
			}
			else if (gameState == GameState::MAIN_MENU || gameState == GameState::GAME_OVER)
			{
				if (event.key.code == sf::Keyboard::Return)
				{
					gameState = GameState::GAME_MODE;
					initializeObjects();
				}
			}
		}
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (gameState == GameState::MAIN_MENU)
	{

	}

	else if (gameState == GameState::GAME_MODE)
	{
		p1.Update();
		checkStateChange();

		for (int i = 0; i < p1.getBullets().size(); i++)
		{//Go through each bullet; if alive, update position.
			if (p1.getBullets()[i]->alive)
			{
				p1.getBullets()[i]->Update();
			}
		}

		/*I am bad at iterators. This is my weak attempt at deleting dead bullets. It's a start, maybe? Also, probably should move these to a separate function...
		vector<Bullet*> p1Bullets = p1.getBullets();
		vector<Bullet*>::iterator p1BulletItr;

		for (p1BulletItr = p1Bullets.begin(); p1BulletItr != p1Bullets.end(); p1BulletItr++)
		{//Go through each bullet again outside of first iteration, remove dead bullets.
		if (!(*p1BulletItr)->alive)
		{
		//p1.getBullets().erase(p1.getBullets().begin() + i);
		p1Bullets.erase(p1BulletItr);
		//p1BulletItr--;
		}
		}*/

		//Check vector of player bullets for dead bullets (!alive) and remove them from the vector.
		//Update vector of enemies.
		//Update vector of enemy bullets and missiles. Remove dead bullets.
		//Update vector of Workers.

		//Check for collision between player bullet and any enemy.
		//Check for collision between player and enemy bullet, missile, or body.
		//Check for collision between player and Worker. 
	}

	else if (gameState == GameState::GAME_OVER)
	{

	}
}

/**
 * Used every update to check if the game's state should change.
 *
 * During MAIN_MENU:
 * If the player chooses to start the game, gameState becomes GAME_MODE and all objects are initialized.
 * 
 * During GAME_MODE:
 * Determines if any win/loss conditions are met, and changes gameState to GAME_OVER.
 * If no Workers remain on the field, game ends with a win. [NOT IMPLEMENTED]
 * If the player's health ever reaches zero, game ends with a loss.
 * 
 * During GAME_OVER:
 * If the player chooses to return to the main menu, gameState becomes MAIN_MENU.
 * If the player chooses to restart the game, gameState becomes GAME_MODE and all objects are reinitialized.
 */
void Game::checkStateChange()
{
	/*if (gameState == GameState::MAIN_MENU)
	{Leave this out for now. No main menu exists.

	}*/
	/*else*/ if (gameState == GameState::GAME_MODE)
	{
		if (p1.getHP() <= 0)
		{
			gameState = GameState::GAME_OVER;
		}
	}
	/*else if (gameState == GameState::GAME_OVER)
	{Leave this out for now. This is already determined in event handling.

	}*/
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{

	m_window.clear(sf::Color::Black);
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);

	if (gameState == GameState::MAIN_MENU)
	{
		m_window.draw(m_mainMenuMessage);
	}

	else if (gameState == GameState::GAME_MODE)
	{
		p1.Draw(m_window);
		for (int i = 0; i < p1.getBullets().size(); i++)
		{
			if (p1.getBullets()[i]->alive)
			{
				p1.getBullets()[i]->Draw(m_window);
			}
		}

		//Draw HP gauge. Changes width depending on HP, does not change height.
		m_hpGauge.setSize(sf::Vector2f(p1.getHP() * 8, m_hpGauge.getSize().y));
		m_window.draw(m_hpGaugeBack);
		m_window.draw(m_hpGauge);
	}
	else if (gameState == GameState::GAME_OVER)
	{
		m_window.draw(m_gameOverMessage);
	}

	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_mainMenuMessage.setFont(m_ArialBlackfont);
	m_mainMenuMessage.setString("SPACE STATION RESCUE\nPress Enter to start game.\nPress Escape to quit.");
	m_mainMenuMessage.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_mainMenuMessage.setPosition(40.0f, 40.0f);
	m_mainMenuMessage.setCharacterSize(80);
	m_mainMenuMessage.setOutlineColor(sf::Color::Black);
	m_mainMenuMessage.setFillColor(sf::Color::White);
	m_mainMenuMessage.setOutlineThickness(3.0f);

	m_gameOverMessage.setFont(m_ArialBlackfont);
	m_gameOverMessage.setString("YOU DIED\nPress Enter to restart.");
	m_gameOverMessage.setStyle(sf::Text::Italic | sf::Text::Bold);
	m_gameOverMessage.setPosition(40.0f, 40.0f);
	m_gameOverMessage.setCharacterSize(80);
	m_gameOverMessage.setOutlineColor(sf::Color::Black);
	m_gameOverMessage.setFillColor(sf::Color::White);
	m_gameOverMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	/*if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);*/

	m_hpGaugeBack = sf::RectangleShape(sf::Vector2f(804, 24));
	m_hpGaugeBack.setPosition(sf::Vector2f(10, 10));
	m_hpGaugeBack.setFillColor(sf::Color(32, 32, 32, 255));

	m_hpGauge = sf::RectangleShape(sf::Vector2f(p1.getHP() * 8, 20));
	m_hpGauge.setPosition(sf::Vector2f(m_hpGaugeBack.getPosition().x + 2, m_hpGaugeBack.getPosition().y + 2));
	m_hpGauge.setFillColor(sf::Color::Red);

	p1.SetupSprite();
}