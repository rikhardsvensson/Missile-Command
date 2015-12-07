#pragma once
#include <SFML/Graphics.hpp>

class Missile
{
public:
	Missile(sf::Vector2f origin, sf::Vector2f destination, float speed);
	~Missile();
	void update();
	void render(sf::RenderWindow* window);

	bool getAlive() const;
private:
	sf::Vector2f currentPosition;
	sf::Vector2f origin;
	sf::Vector2f destination;
	float speed;
	bool alive;
};