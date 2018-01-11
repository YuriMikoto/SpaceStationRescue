// author Peter Lowe

#include "Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode{ 1600, 1200, 32 }, "Space Station Rescue" },

	m_exitGame{false} //when true game will exit
{
	rect.setOutlineColor(sf::Color::White);
	rect.setOutlineThickness(1);
	pRect = &p1.getRect();

	setupFontAndText(); // load font 
	setupSprite(); // load texture
}


Game::~Game()
{
}

void Game::initializeObjects()
{
	p1 = Player();
	*pRect = p1.getRect();
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
}

/// <summary>
/// draw the frame and then switch bufers
/// </summary>
void Game::render()
{
	//rect.setPosition(pRect->left-p1.getRadius(), pRect->top-p1.getRadius());
	//rect.setSize(sf::Vector2f(pRect->width, pRect->height));
	m_window.clear(sf::Color::Magenta);
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);
	gameGrid.render(m_window);
	//m_window.draw(rect);
	p1.Draw(m_window);

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

	p1.SetupSprite();
}
