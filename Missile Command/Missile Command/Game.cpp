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
	if (!arial.loadFromFile(fontPath))
	{
		//TODO: error handling
	}

	backgroundColor = sf::Color(0, 0, 0);

	initGround();
	initMissileBase();
	initCities();
	initProjectileParameters();

	currentLevel = 0;
	nrOfMeteorsLeftTilNextLevel = 0;

	missileBaseCooldownTimer = sf::Clock();
	//TODO: complete the cooldown timer
}

void Game::initGround()
{
	groundShape = sf::RectangleShape();
	groundShape.setFillColor(groundColor);
	groundShape.setSize(sf::Vector2f(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y) / 15));
	groundShape.setPosition(0, windowSize.y - groundShape.getSize().y);
}

void Game::initMissileBase()
{
	sf::Vector2f missileBaseSize = sf::Vector2f(sf::Vector2f(static_cast<float>(windowSize.x) / 20, static_cast<float>(windowSize.y) / 20));
	sf::Vector2f missileBasePosition = sf::Vector2f(windowSize.x / 2 - missileBaseSize.x / 2, windowSize.y - missileBaseSize.y - groundShape.getSize().y);
	missileBase = MissileBase(missileBaseSize, missileBasePosition, ammunitionPerLevel, missilesTilCooldown);

	ammunitionText.setColor(sf::Color::White);
	ammunitionText.setCharacterSize(20);
	ammunitionText.setFont(arial);
	setAmmunitionText(missileBase.getAmmunition());
}

void Game::initCities()
{
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
}

void Game::initProjectileParameters()
{
	missileParameters.projectileType = ProjectileType::MISSILE;
	missileParameters.origin = missileBase.getMissileOrigin();
	missileParameters.projectileColor = missileColor;
	missileParameters.projectileSpeed = missileSpeed;
	missileParameters.explosionColor = missileExplosionColor;

	meteorParameters.projectileType = ProjectileType::METEOR;
	meteorParameters.projectileColor = meteorColor;
	meteorParameters.projectileSpeed = initialMeteorSpeed;
	meteorParameters.explosionColor = meteorExplosionColor;

	meteorParameters.explosionMaximumRadius = missileParameters.explosionMaximumRadius = explosionMaximumRadius;
	meteorParameters.explosionPropagationSpeed = missileParameters.explosionPropagationSpeed = explosionPropagationSpeed;
}

int Game::run()
{
	while (window->isOpen())
	{
		update();
		render();
	}

	return 0;
}

void Game::update()
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
			if (meteors[i]->getIsWaveSpawner())
			{
				dropMeteorWave();
			}

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

	if (nrOfMeteorsLeftTilNextLevel <= 0 && meteors.empty())
	{
		if (currentLevel != 0)
		{
			setRandomBackgroundColor();
		}
		increaseLevel();
		dropMeteorWave();
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
		for (auto meteor : meteors)
		{
			if (pointCircleCollision(meteor->getCurrentPosition(), explosion->getExplosionShape()))
			{
				meteor->setDying(true);
			}
		}
		if (explosion->getProjectileType() == ProjectileType::METEOR)
		{
			if (!explosion->isExpended())
			{
				if (rectangleSphereCollision(missileBase.getMissileBaseShape(), explosion->getExplosionShape()))
				{
					if (missileBase.getAmmunition() >= 0)
					{
						missileBase.offsetAmmunition(baseHitAmmunitionOffset);
						if (missileBase.getAmmunition() < 0)
						{
							missileBase.setAmmunition(0);
						}
						setAmmunitionText(missileBase.getAmmunition());
					}
					explosion->setExpended(true);
				}
				for (int i = 0; i < 6; i++)
				{
					if (rectangleSphereCollision(cities[i].getCityShape(), explosion->getExplosionShape()))
					{
						cities[i].setAlive(false);
						explosion->setExpended(true);
					}
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

	window->draw(ammunitionText);

	window->display();
}

void Game::fireMissile(sf::Vector2i mousePos)
{
	if (mousePos.y < missileBase.getMissileBaseShape().getPosition().y)
	{
		if (missileBase.getAmmunition() > 0)
		{
			if (missilesTilCooldown > 0)
			{
				missileParameters.destination = sf::Vector2f(mousePos);
				missiles.push_back(new Projectile(missileParameters));

				missileBase.offsetAmmunition(-1);
				setAmmunitionText(missileBase.getAmmunition());
				missileBase.offsetCurrentMissilesTilCooldown(-1);
			}
		}
	}
}

void Game::dropMeteor(bool isWaveSpawner)
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

	meteorParameters.isWaveSpawner = isWaveSpawner;

	meteors.push_back(new Projectile(meteorParameters));

	nrOfMeteorsLeftTilNextLevel--;
}

void Game::setAmmunitionText(int ammunition)
{
	ammunitionText.setString(std::to_string(missileBase.getAmmunition()));
	sf::FloatRect ammunitionTextRect = ammunitionText.getGlobalBounds();
	ammunitionText.setPosition(windowSize.x / 2 - ammunitionTextRect.width / 2, windowSize.y - groundShape.getSize().y);
}

void Game::increaseLevel()
{
	meteorParameters.projectileSpeed = initialMeteorSpeed + currentLevel * meteorSpeedIncreasePerLevel;
	nrOfMeteorsLeftTilNextLevel = initialNrOfMeteors + currentLevel * increaseOfMeteorsPerLevel;
	if (nrOfMeteorsLeftTilNextLevel > maxNrOfMeteorsPerLevel)
	{
		nrOfMeteorsLeftTilNextLevel = maxNrOfMeteorsPerLevel;
	}
	missileBase.setAmmunition(ammunitionPerLevel);
	setAmmunitionText(missileBase.getAmmunition());
	currentLevel++;
}

void Game::setRandomBackgroundColor()
{
	std::uniform_int_distribution<int> randColorValue(0, 95);
	backgroundColor = sf::Color(randColorValue(*mt), randColorValue(*mt), randColorValue(*mt));
}

void Game::dropMeteorWave()
{
	std::uniform_int_distribution<int> randNrOfMeteorsInWave(1, maxNrOfMeteorsInWave);
	std::uniform_int_distribution<int> randNrOfSpawnersInWave(1, maxNrOfSpawnersInWave);

	int nrOfMeteorsInWave = randNrOfMeteorsInWave(*mt);
	if (nrOfMeteorsInWave > nrOfMeteorsLeftTilNextLevel)
	{
		nrOfMeteorsInWave = nrOfMeteorsLeftTilNextLevel;
	}

	int nrOfSpawnersInWave = randNrOfSpawnersInWave(*mt);
	if (nrOfSpawnersInWave > nrOfMeteorsInWave)
	{
		nrOfSpawnersInWave = nrOfMeteorsInWave;
	}

	while (nrOfSpawnersInWave > 0)
	{
		dropMeteor(true);
		nrOfSpawnersInWave--;
		nrOfMeteorsInWave--;
	}

	while (nrOfMeteorsInWave > 0)
	{
		dropMeteor(false);
		nrOfMeteorsInWave--;
	}
}
