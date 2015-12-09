#include "Game.h"

Game::Game(std::mt19937* mt)
{
	sf::VideoMode videoMode = sf::VideoMode(windowSize.x, windowSize.y, 32);
	window = new sf::RenderWindow(videoMode, "Missile Command", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	window->setVerticalSyncEnabled(true);

	this->mt = mt;
}

Game::~Game()
{
	for (unsigned i = 0; i < missiles.size(); i++)
	{
		delete missiles[i];
	}
	missiles.clear();

	for (unsigned i = 0; i < explosions.size(); i++)
	{
		delete explosions[i];
	}
	explosions.clear();

	for (unsigned i = 0; i < meteors.size(); i++)
	{
		delete meteors[i];
	}
	meteors.clear();

	delete window;
}

void Game::init()
{
	backgroundColor = sf::Color(0, 0, 0);

	groundShape = sf::RectangleShape();
	groundShape.setFillColor(groundColor);
	groundShape.setSize(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) / 15));
	groundShape.setPosition(0, windowSize.y - groundShape.getSize().y);

	sf::Vector2f missileBaseSize = sf::Vector2f(sf::Vector2f(static_cast<float>(windowSize.x) / 20, static_cast<float>(windowSize.y) / 20));
	sf::Vector2f missileBasePosition = sf::Vector2f(windowSize.x / 2 - missileBaseSize.x / 2, windowSize.y - missileBaseSize.y - groundShape.getSize().y);
	missileBase = MissileBase(missileBaseSize, missileBasePosition);

	sf::RectangleShape cityShape;
	cityShape.setFillColor(sf::Color::Blue);
	cityShape.setSize(sf::Vector2f(static_cast<float>(windowSize.x) / 20, static_cast<float>(windowSize.y) / 20));
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

	missileParameters.projectileType = ProjectileType::MISSILE;
	missileParameters.origin = missileBase.getMissileOrigin();
	missileParameters.projectileColor = missileColor;
	missileParameters.projectileSpeed = missileSpeed;
	missileParameters.explosionColor = missileExplosionColor;

	meteorParameters.projectileType = ProjectileType::METEOR;
	meteorParameters.projectileColor = meteorColor;
	meteorParameters.projectileSpeed = meteorSpeed;
	meteorParameters.explosionColor = meteorExplosionColor;

	meteorParameters.explosionMaximumRadius = missileParameters.explosionMaximumRadius = explosionMaximumRadius;
	meteorParameters.explosionPropagationSpeed = missileParameters.explosionPropagationSpeed = explosionPropagationSpeed;
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
	handleInput();
	solveCollisions();

	for (unsigned i = 0; i < missiles.size(); i++)
	{
		if (missiles[i]->getAlive())
		{
			missiles[i]->update(&explosions);
		}
		else
		{
			delete missiles[i];
			missiles.erase(missiles.begin() + i);
		}
	}
	for (unsigned i = 0; i < meteors.size(); i++)
	{
		if (meteors[i]->getAlive())
		{
			meteors[i]->update(&explosions);
		}
		else
		{
			delete meteors[i];
			meteors.erase(meteors.begin() + i);
		}
	}
	for (unsigned i = 0; i < explosions.size(); i++)
	{
		if (explosions[i]->getAlive())
		{
			explosions[i]->update();
		}
		else
		{
			delete explosions[i];
			explosions.erase(explosions.begin() + i);
		}
	}
}

void Game::handleInput()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(*window);
				fireMissile(mousePos);
			}

			//TODO: Remove debug functionality
			else if (event.mouseButton.button == sf::Mouse::Right)
			{
				dropMeteor();
			}
			break;

		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			break;

		default:
			break;
		}
	}
}

void Game::solveCollisions()
{
	for (auto explosion : explosions)
	{
		if (explosion->getProjectileType() == ProjectileType::MISSILE)
		{
			for (auto meteor : meteors)
			{
				if (pointCircleCollision(meteor->getCurrentPosition(), explosion->getExplosionShape()))
				{
					meteor->setDying(true);
				}
			}
		}
		else
		{
			if (rectangleSphereCollision(missileBase.getMissileBaseShape(), explosion->getExplosionShape()))
			{
				missileBase.setAlive(false);
			}
			for (int i = 0; i < 6; i++)
			{
				if (rectangleSphereCollision(cities[i].getCityShape(), explosion->getExplosionShape()))
				{
					cities[i].setAlive(false);
				}
			}
		}
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

	for (auto missile : missiles)
	{
		missile->render(window);
	}
	for (auto meteor : meteors)
	{
		meteor->render(window);
	}
	for (auto explosion : explosions)
	{
		explosion->render(window);
	}

	window->display();
}

void Game::fireMissile(sf::Vector2i mousePos)
{
	missileParameters.destination = sf::Vector2f(mousePos);
	missiles.push_back(new Projectile(missileParameters));
}

void Game::dropMeteor()
{
	std::uniform_real_distribution<float> randMeteorOrigin(0.0, static_cast<float>(windowSize.x));
	std::uniform_int_distribution<int> randMeteorDestination(0, 6);

	meteorParameters.origin = sf::Vector2f(randMeteorOrigin(*mt), 0);

	int target = randMeteorDestination(*mt);
	if (target == 6)
	{
		meteorParameters.destination = missileBase.getMeteorTarget();
	}
	else
	{
		meteorParameters.destination = cities[target].getMeteorTarget();
	}

	meteors.push_back(new Projectile(meteorParameters));
}