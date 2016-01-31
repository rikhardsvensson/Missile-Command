#pragma once
#include <random>
#include "MissileBase.h"
#include "City.h"
#include "Projectile.h"
#include "Explosion.h"
#include "Score.h"

class Game
{
public:
	Game();
	Game(std::mt19937* mt);
	~Game();

	void init(sf::RenderWindow* window, Settings* settings);
	void resetGame();
	int update(sf::Event* event);
	void render();

private:
	//Necessities
	sf::RenderWindow* window;
	std::mt19937* mt;

	//Visuals
	sf::Color backgroundColor;
	sf::RectangleShape groundShape;
	MissileBase missileBase;
	City cities[6];
	Score score;

	//Movables
	std::vector<Projectile*> missiles;
	std::vector<Projectile*> meteors;
	std::vector<Explosion*> explosions;

	//Utils
	Settings* settings;
	ProjectileParameters missileParameters;
	ProjectileParameters meteorParameters;
	bool isGameOver;
	int currentLevel;
	int nrOfMeteorsLeftTilNextLevel;
	int currentState;

	void initGround();
	void initMissileBase();
	void initCities();
	void initProjectileParameters();
	void handleInput(sf::Event* event);
	void fireMissile(sf::Vector2i mousePos);
	void solveCollisions();
	void dropMeteor(bool isWaveSpawner);
	void dropMeteorWave();
	void increaseLevel();
	void setRandomBackgroundColor();
	void cleanMovables();
};