#include "Game.h"

Game::Game()
{
	sf::VideoMode videoMode = sf::VideoMode(windowSize.x, windowSize.y, 32);
	window = new sf::RenderWindow(videoMode, "Missile Command", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	window->setVerticalSyncEnabled(true);
}

Game::~Game()
{
}

void Game::init()
{
	backgroundColor = sf::Color(0, 0, 0);

	groundShape = sf::RectangleShape();
	groundShape.setFillColor(colorBrown);
	groundShape.setSize(sf::Vector2f(windowSize.x, windowSize.y / 15));
	groundShape.setPosition(0, windowSize.y - groundShape.getSize().y);

	sf::RectangleShape missileBaseShape;
	missileBaseShape.setFillColor(sf::Color::White);
	missileBaseShape.setSize(sf::Vector2f(windowSize.x / 20, windowSize.y / 20));
	float missileBasePosX = windowSize.x / 2 - missileBaseShape.getSize().x / 2;
	float missileBasePosY = windowSize.y - missileBaseShape.getSize().y - groundShape.getSize().y;
	missileBaseShape.setPosition(missileBasePosX, missileBasePosY);
	missileBase.setMissileBaseShape(missileBaseShape);
	missileBase.setAlive(true);

	sf::RectangleShape cityShape;
	cityShape.setFillColor(sf::Color::Blue);
	cityShape.setSize(sf::Vector2f(windowSize.x / 20, windowSize.y / 20));
	float cityPosY = windowSize.y - cityShape.getSize().y - groundShape.getSize().y;
	for (int i = 0; i < 6; i++)
	{
		int offsetPosX = i + 1;
		if (i > 2)
		{
			offsetPosX++;
		}
		float cityPosX = offsetPosX * (windowSize.x / 8) - cityShape.getSize().x / 2;
		cityShape.setPosition(cityPosX, cityPosY);
		cities[i].setCityShape(cityShape);
		cities[i].setAlive(true);
	}
}

int Game::run()
{
	sf::Clock clock;

	while (window->isOpen())
	{
		sf::Time elapsedTime = clock.getElapsedTime();
		clock.restart();

		update(elapsedTime);
		render();
	}

	return 0;
}

void Game::update(sf::Time elapsedTime)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
		{
			window->close();
			break;
		}
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
		fireMissile(mousePos);
	}

}

void Game::render()
{
	window->clear(backgroundColor);

	window->draw(groundShape);
	for (int i = 0; i < 6; i++)
	{
		cities[i].render(window);
	}

	missileBase.render(window);

	window->display();
}

void Game::fireMissile(sf::Vector2i mousePos)
{
	
}
