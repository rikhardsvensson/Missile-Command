#pragma once
#include <random>
#include "MissileBase.h"
#include "City.h"
#include "Projectile.h"
#include "Explosion.h"

class Game
{
public:
	Game(std::mt19937* mt);
	~Game();
	int run();
	void init();

private:
	//Hard coded data that should be moved to config files.
	sf::Vector2i windowSize = sf::Vector2i(1280, 720);
	sf::Color groundColor = sf::Color(100, 50, 0);
	sf::Color missileColor = sf::Color::Magenta;
	sf::Color missileExplosionColor = sf::Color::Magenta;
	sf::Color meteorExplosionColor = sf::Color::Green;
	sf::Color meteorColor = sf::Color::Green;
	float missileSpeed = 5;
	float meteorSpeed = 3;
	float explosionMaximumRadius = 50;
	float explosionPropagationSpeed = 3;

	sf::RenderWindow* window;
	
	std::mt19937* mt;

	sf::Color backgroundColor;
	sf::RectangleShape groundShape;
	MissileBase missileBase;
	City cities[6];

	ProjectileParameters missileParameters;
	std::vector<Projectile*> missiles;
	ProjectileParameters meteorParameters;
	std::vector<Projectile*> meteors;
	std::vector<Explosion*> explosions;

	void update(sf::Time elapsedTime);
	void handleInput();
	void solveCollisions();
	void render();
	void fireMissile(sf::Vector2i mousePos);
	void dropMeteor();
	
};