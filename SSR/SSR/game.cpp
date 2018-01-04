// author Peter Lowe

using namespace std;
#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1600, 1200, 32 }, "Space Station Rescue" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}


Game::~Game()
{
}

void Game::initializeObjects()
{
	p1 = Player();
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

			else if (event.key.code == sf::Keyboard::W)
			{
				//p1.Thrusters(2);
				p1.forward = true;
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				//p1.Thrusters(-2);
				p1.backwards = true;
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				//p1.Steer(-6);
				p1.left = true;
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				//p1.Steer(6);
				p1.right = true;
			}

		}
		if (event.type == sf::Event::KeyReleased)
		{

			if (event.key.code == sf::Keyboard::W)
			{
				//p1.Thrusters(2);
				p1.forward = false;
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				//p1.Thrusters(-2);
				p1.backwards = false;
			}
			else if (event.key.code == sf::Keyboard::A)
			{
				//p1.Steer(-6);
				p1.left = false;
			}
			else if (event.key.code == sf::Keyboard::D)
			{
				//p1.Steer(6);
				p1.right = false;
			}
			else if (event.key.code == sf::Keyboard::Space)
			{//Fire a bullet.
				p1.Fire();
			}
			else if (event.key.code == sf::Keyboard::BackSpace)
			{//Debug command. Reduces player's HP.
				p1.damageHP(2);
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

	p1.Update();

	/*if (p1.getHP() <= 0)
	{
		//Game over.
	}*/

	for (int i = 0; i < p1.getBullets().size(); i++)
	{//Go through each bullet, check if alive, update position.
		if (p1.getBullets()[i]->alive)
		{
			p1.getBullets()[i]->Update();
		}
	}

	/*I am bad at iterators. This is my weak attempt at deleting dead bullets. It's a start, maybe?
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

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);

	p1.Draw(m_window);
	for (int i = 0; i < p1.getBullets().size(); i++)
	{
		if (p1.getBullets()[i]->alive)
		{
			p1.getBullets()[i]->Draw(m_window);
		}
	}

	//Draw HP gauge. Changes width depending on HP, does not change height.
	m_hpGauge.setSize(sf::Vector2f(p1.getHP()*5, m_hpGauge.getSize().y));
	m_window.draw(m_hpGaugeBack);
	m_window.draw(m_hpGauge);

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
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);

	m_hpGaugeBack = sf::RectangleShape(sf::Vector2f(504, 14));
	m_hpGaugeBack.setPosition(sf::Vector2f(150, 200));
	m_hpGaugeBack.setFillColor(sf::Color(32, 32, 32, 255));

	m_hpGauge = sf::RectangleShape(sf::Vector2f(p1.getHP()*5, 10));
	m_hpGauge.setPosition(sf::Vector2f(m_hpGaugeBack.getPosition().x + 2, m_hpGaugeBack.getPosition().y + 2));
	m_hpGauge.setFillColor(sf::Color::Red);

	p1.SetupSprite();
}
