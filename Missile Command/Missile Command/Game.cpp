#include "Game.h"

Game::Game(std::mt19937* mt)
{
	settings = settingsParser.getSettings();

	window = new sf::RenderWindow();
	createWindow(settings->fullscreen);

	this->mt = mt;
}

Game::~Game()
{
	score.updateHighScore();
	settings->highScore = score.getHighScore();
	settingsParser.setSettings(settings);
	cleanMovables();
	delete window;
}

void Game::init()
{
	isGameOver = false;
	backgroundColor = sf::Color(0, 0, 0);
	currentLevel = 0;
	nrOfMeteorsLeftTilNextLevel = 0;

	initGround();
	initMissileBase();
	initCities();
	initProjectileParameters();
	score = Score(settings, sf::Vector2f(5, 5), sf::Color::White);
	gameOverScreen.init(settings);
}

void Game::createWindow(bool fullscreen)
{
	sf::VideoMode videoMode = sf::VideoMode(settings->resolution.x, settings->resolution.y, 32);
	if (fullscreen)
	{
		window->create(videoMode, "Missile Command", sf::Style::Fullscreen);
	}
	else
	{
		window->create(videoMode, "Missile Command", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	}
	window->setVerticalSyncEnabled(true);
}

void Game::cleanMovables()
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
}

void Game::initGround()
{
	groundShape = sf::RectangleShape();
	groundShape.setFillColor(settings->groundColor);
	groundShape.setSize(sf::Vector2f(static_cast<float>(settings->resolution.x), static_cast<float>(settings->resolution.y) / 15));
	groundShape.setPosition(0, settings->resolution.y - groundShape.getSize().y);
}

void Game::initMissileBase()
{
	sf::Vector2f missileBaseSize = sf::Vector2f(sf::Vector2f(static_cast<float>(settings->resolution.x) / 20, static_cast<float>(settings->resolution.y) / 20));
	sf::Vector2f missileBasePosition = sf::Vector2f(settings->resolution.x / 2 - missileBaseSize.x / 2, settings->resolution.y - missileBaseSize.y - groundShape.getSize().y);
	missileBase = MissileBase(missileBaseSize, missileBasePosition, settings);
}

void Game::initCities()
{
	sf::RectangleShape cityShape;
	cityShape.setFillColor(sf::Color::Blue);
	cityShape.setSize(sf::Vector2f(static_cast<float>(settings->resolution.x) / 20, static_cast<float>(settings->resolution.y) / 20));
	float cityPosY = settings->resolution.y - cityShape.getSize().y - groundShape.getSize().y;
	for (int i = 0; i < 6; i++)
	{
		int offsetPosX = i + 1;
		if (i > 2)
		{
			offsetPosX++;
		}
		float cityPosX = offsetPosX * (settings->resolution.x / 8) - cityShape.getSize().x / 2;
		cityShape.setPosition(cityPosX, cityPosY);
		cities[i].setCityShape(cityShape);
		cities[i].setAlive(true);
	}
}

void Game::initProjectileParameters()
{
	missileParameters.projectileType = ProjectileType::MISSILE;
	missileParameters.origin = missileBase.getMissileOrigin();
	missileParameters.projectileColor = settings->missileColor;
	missileParameters.projectileSpeed = settings->missileSpeed;
	missileParameters.explosionColor = settings->missileExplosionColor;

	meteorParameters.projectileType = ProjectileType::METEOR;
	meteorParameters.projectileColor = settings->meteorColor;
	meteorParameters.projectileSpeed = settings->initialMeteorSpeed;
	meteorParameters.explosionColor = settings->meteorExplosionColor;

	meteorParameters.explosionMaximumRadius = missileParameters.explosionMaximumRadius = settings->explosionMaximumRadius;
	meteorParameters.explosionPropagationSpeed = missileParameters.explosionPropagationSpeed = settings->explosionPropagationSpeed;
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

	if (isGameOver)
	{
		if (gameOverScreen.update(window, settings) == GameOverScreen::RESTART)
		{
			resetGame();
		}
	}
	else
	{
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
				if (!meteors[i]->getReachedDestination())
				{
					score.offsetScore(settings->scoreForMeteor);
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
				if (!isGameOver)
				{
					fireMissile(getScaledMouseCoords(window, settings));
				}
			}
			break;
		case sf::Event::KeyPressed:
			if (event.key.code == sf::Keyboard::Escape)
			{
				window->close();
			}
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) && event.key.code == sf::Keyboard::Return)
			{
				settings->fullscreen = !settings->fullscreen;
				createWindow(settings->fullscreen);
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
			if (!explosion->isExpended()) //Explosions expend themselves when hitting a city or the missile base as to avoid multiple collision calculations.
			{
				if (rectangleCircleCollision(missileBase.getMissileBaseShape(), explosion->getExplosionShape()))
				{
					if (missileBase.getAmmunition() >= 0)
					{
						int updatedAmmunition = missileBase.getAmmunition() + settings->baseHitAmmunitionOffset;
						updatedAmmunition = std::max(updatedAmmunition, 0); //Ensures that ammunition can not be lower than zero.
						missileBase.setAmmunition(updatedAmmunition);
					}
					explosion->setExpended(true);
				}
				for (int i = 0; i < 6; i++)
				{
					if (rectangleCircleCollision(cities[i].getCityShape(), explosion->getExplosionShape()))
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

	score.render(window);

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

	if (isGameOver)
	{
		gameOverScreen.render(window);
	}

	window->display();
}

void Game::fireMissile(sf::Vector2i mousePos)
{
	if (mousePos.y < missileBase.getMissileBaseShape().getPosition().y)
	{
		if (missileBase.getAmmunition() > 0)
		{
			missileParameters.destination = sf::Vector2f(mousePos);
			missiles.push_back(new Projectile(missileParameters));

			missileBase.offsetAmmunition(-1);
		}
	}
}

void Game::dropMeteor(bool isWaveSpawner)
{
	std::uniform_real_distribution<float> randMeteorOrigin(0.0, static_cast<float>(settings->resolution.x));
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

void Game::increaseLevel()
{
	meteorParameters.projectileSpeed = settings->initialMeteorSpeed + currentLevel * settings->meteorSpeedIncreasePerLevel;
	nrOfMeteorsLeftTilNextLevel = settings->initialNrOfMeteors + currentLevel * settings->increaseOfMeteorsPerLevel;
	if (nrOfMeteorsLeftTilNextLevel > settings->maxNrOfMeteorsPerLevel)
	{
		nrOfMeteorsLeftTilNextLevel = settings->maxNrOfMeteorsPerLevel;
	}

	if (currentLevel > 0)
	{
		isGameOver = true;
		for (int i = 0; i < 6; i++)
		{
			if (cities[i].getAlive())
			{
				isGameOver = false;
				score.offsetScore(settings->scoreForCity);
			}
		}

		for (int i = 0; i < missileBase.getAmmunition(); i++)
		{
			score.offsetScore(settings->scoreForRemainingMissile);
		}

		score.updateHighScore();
	}

	if (!isGameOver)
	{
		missileBase.setAmmunition(settings->ammunitionPerLevel);
		currentLevel++;
	}
}

void Game::setRandomBackgroundColor()
{
	std::uniform_int_distribution<int> randColorValue(0, 95);
	backgroundColor = sf::Color(randColorValue(*mt), randColorValue(*mt), randColorValue(*mt));
}

void Game::dropMeteorWave()
{
	std::uniform_int_distribution<int> randNrOfMeteorsInWave(1, settings->maxNrOfMeteorsInWave);
	std::uniform_int_distribution<int> randNrOfSpawnersInWave(1, settings->maxNrOfSpawnersInWave);

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

void Game::resetGame()
{
	isGameOver = false;
	cleanMovables();
	for (int i = 0; i < 6; i++)
	{
		cities[i].setAlive(true);
	}
	backgroundColor = sf::Color(0, 0, 0);
	currentLevel = 0;
	nrOfMeteorsLeftTilNextLevel = 0;
	missileBase.setAmmunition(settings->ammunitionPerLevel);
	score.resetScore();
	dropMeteorWave();
}