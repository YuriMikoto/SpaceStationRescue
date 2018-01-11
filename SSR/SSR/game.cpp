// author Peter Lowe

using namespace std;
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1600, 1200, 32 }, "Space Station Rescue" },

	m_exitGame{ false } //when true game will exit
{
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(1);
	pRect = &p1.getRect();
	
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
	*pRect = p1.getRect();

	for (int i = 0; i < WORKER_COUNT; i++)
	{
		workers.push_back(new Worker());
	}
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
	handleCollisions();
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
		//Update vector of Workers. End game if no workers are alive.

		for (int i = 0; i < workers.size(); i++)
		{
			if (p1.getPosition().x + p1.getDimensions().x > workers[i]->getPosition().x &&
				p1.getPosition().x < workers[i]->getPosition().x + workers[i]->getDimensions().x &&
				p1.getPosition().y + p1.getDimensions().y > workers[i]->getPosition().y &&
				p1.getPosition().y < workers[i]->getPosition().y + workers[i]->getDimensions().y)
			{
				workers[i]->alive = false;
			}
		}

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
* During GAME_MODE:
* Determines if any win/loss conditions are met, and changes gameState to GAME_OVER.
* If no Workers remain on the field, game ends with a win.
* If the player's health ever reaches zero, game ends with a loss.
* In either case, alter the game over screen's string to display the correct message.
*/
void Game::checkStateChange()
{
	if (gameState == GameState::GAME_MODE)
	{
		if (p1.getHP() <= 0)
		{
			m_gameOverMessage.setString("YOU DIED\nPress Enter to retry.");
			gameState = GameState::GAME_OVER;
		}

		int workersleft = 0; //Number of Workers remaining on the field. 

		for (int i = 0; i < workers.size(); i++)
		{
			if (workers[i]->alive)
			{
				workers[i]->Update();
				workersleft++;
			}
		}

		if (workersleft == 0)
		{
			m_gameOverMessage.setString("MISSION ACCOMPLISHED\nPress Enter to restart.");
			gameState = GameState::GAME_OVER;
		}
	}
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	//rect.setPosition(pRect->left-p1.getRadius(), pRect->top-p1.getRadius());
	//rect.setSize(sf::Vector2f(pRect->width, pRect->height));
	m_window.clear(sf::Color::Black);
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);

	//m_window.draw(rect);
	if (gameState == GameState::MAIN_MENU)
	{
		m_window.draw(m_mainMenuMessage);
	}

	else if (gameState == GameState::GAME_MODE)
	{
	gameGrid.render(m_window);
		p1.Draw(m_window);
		for (int i = 0; i < p1.getBullets().size(); i++)
		{
			if (p1.getBullets()[i]->alive)
			{
				p1.getBullets()[i]->Draw(m_window);
			}
		}

		for (int i = 0; i < workers.size(); i++)
		{
			if (workers[i]->alive)
			{
				workers[i]->Draw(m_window);
			}
		}

		//Draw HP gauge. Changes width depending on HP, does not change height.
		m_hpGauge.setSize(sf::Vector2f(p1.getHP() * 8.0f, m_hpGauge.getSize().y));
		m_window.draw(m_hpGaugeBack);
		m_window.draw(m_hpGauge);
	}
	else if (gameState == GameState::GAME_OVER)
	{
		m_window.draw(m_gameOverMessage);
	}

	m_window.display();
}

void Game::handleCollisions()
{
	pRect->top -= p1.getRadius();
	pRect->left -= p1.getRadius();
	int collisionBump = 2;
	tempDisplacement=&gameGrid.checkCollisionRectangleVector(*pRect);
		pRect->top += p1.getRadius();
		pRect->left += p1.getRadius();
	if (tempDisplacement->top != 0 || tempDisplacement->left != 0) {
	//std::cout << "x: " << tempDisplacement->left << " y: " << tempDisplacement->top << std::endl;
		/*if (tempDisplacement->height != pRect->height)
		{
		pRect->top-=tempDisplacement->height;
		}
		if (tempDisplacement->width != pRect->width)
		{
		pRect->left -= tempDisplacement->width;
		}*/
		//pRect->left += tempDisplacement->width*tempDisplacement->left;
		//pRect->top += tempDisplacement->height*tempDisplacement->top;
		pRect->top += collisionBump*tempDisplacement->top;
		pRect->left += collisionBump*tempDisplacement->left;




		p1.getPos().x = pRect->left;
		p1.getPos().y = pRect->top;
		

	}


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

	m_hpGauge = sf::RectangleShape(sf::Vector2f(p1.getHP() * 8.0f, 20));
	m_hpGauge.setPosition(sf::Vector2f(m_hpGaugeBack.getPosition().x + 2, m_hpGaugeBack.getPosition().y + 2));
	m_hpGauge.setFillColor(sf::Color::Red);

	p1.SetupSprite();
}