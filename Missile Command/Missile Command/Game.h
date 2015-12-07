#pragma once
#include "MissileBase.h"
#include "City.h"
#include "Missile.h"

class Game
{
public:
	Game();
	~Game();
	int run();
	void init();

private:
	//Hard coded data that should be moved to config files.
	sf::Vector2i windowSize = sf::Vector2i(1280, 720);
	sf::Color colorBrown = sf::Color(100, 50, 0);

	sf::RenderWindow* window;

	sf::Color backgroundColor;
	sf::RectangleShape groundShape;
	MissileBase missileBase;
	City cities[6];

	float missileSpeed = 5.0;
	std::vector<Missile*> missiles;

	void update(sf::Time elapsedTime);
	void render();
	void fireMissile(sf::Vector2i mousePos);
};