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
	Game(std::mt19937* mt);
	~Game();
	int run();
	void init();

private:
	//Hard coded data that should be moved to config files.
	std::string fontPath = "arial.ttf";
	sf::Vector2i windowSize = sf::Vector2i(1280, 720);
	sf::Color groundColor = sf::Color(100, 50, 0);
	sf::Color missileColor = sf::Color::Magenta;
	sf::Color missileExplosionColor = sf::Color::Magenta;
	sf::Color meteorExplosionColor = sf::Color::Green;
	sf::Color meteorColor = sf::Color::Green;
	int ammunitionTextCharacterSize = 20;
	int scoreTextCharacterSize = 20;
	float missileSpeed = 5;
	float initialMeteorSpeed = 0.4f;
	float meteorSpeedIncreasePerLevel = 0.2f;
	float explosionMaximumRadius = 50;
	float explosionPropagationSpeed = 0.75f;
	int ammunitionPerLevel = 30;
	int initialNrOfMeteors = 12;
	int increaseOfMeteorsPerLevel = 3;
	int baseHitAmmunitionOffset = -10;
	int missilesTilCooldown = 3;
	int missileBaseCooldownTime = 3;
	int maxNrOfMeteorsPerLevel = 20;
	int maxNrOfMeteorsInWave = 5;
	int maxNrOfSpawnersInWave = 1;
	int scoreForMeteor = 25;
	int scoreForCity = 100;
	int scoreForRemainingMissile = 5;

	//Necessities
	sf::RenderWindow* window;
	sf::Font arial;
	std::mt19937* mt;

	//Visuals
	sf::Color backgroundColor;
	sf::RectangleShape groundShape;
	MissileBase missileBase;
	City cities[6];
	sf::Text ammunitionText;
	Score score;

	//Movables
	std::vector<Projectile*> missiles;
	std::vector<Projectile*> meteors;
	std::vector<Explosion*> explosions;

	//Utils
	ProjectileParameters missileParameters;
	ProjectileParameters meteorParameters;
	sf::Clock missileBaseCooldownTimer;

	int currentLevel;
	int nrOfMeteorsLeftTilNextLevel;

	void initGround();
	void initMissileBase();
	void initCities();
	void initProjectileParameters();
	void initText();
	void update();
	void handleInput();
	void solveCollisions();
	void render();
	void fireMissile(sf::Vector2i mousePos);
	void dropMeteor(bool isWaveSpawner);
	void setAmmunitionText(int ammunition);
	void increaseLevel();
	void setRandomBackgroundColor();
	void dropMeteorWave();
};