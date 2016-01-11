#pragma once
#include <random>
#include "MissileBase.h"
#include "City.h"
#include "Projectile.h"
#include "Explosion.h"
#include "Score.h"
#include "GameOverScreen.h"
#include "SettingsParser.h"

class Game
{
public:
	Game(std::mt19937* mt);
	~Game();

	int run();
	void init();

private:
	//Necessities
	sf::RenderWindow* window;
	std::mt19937* mt;

	//Visuals
	GameOverScreen gameOverScreen;
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
	SettingsParser settingsParser;
	Settings* settings;
	ProjectileParameters missileParameters;
	ProjectileParameters meteorParameters;
	bool isGameOver;
	int currentLevel;
	int nrOfMeteorsLeftTilNextLevel;

	void initGround();
	void initMissileBase();
	void initCities();
	void initProjectileParameters();
	void createWindow(bool fullscreen);
	void update();
	void handleInput();
	void fireMissile(sf::Vector2i mousePos);
	void solveCollisions();
	void dropMeteor(bool isWaveSpawner);
	void dropMeteorWave();
	void increaseLevel();
	void setRandomBackgroundColor();
	void resetGame();
	void cleanMovables();
	void render();
};