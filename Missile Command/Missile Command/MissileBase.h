#pragma once
#include <SFML/Graphics.hpp>

class MissileBase
{
public:
	MissileBase();
	~MissileBase();

	void render(sf::RenderWindow* window);

	sf::RectangleShape getMissileBaseShape() const;
	void setMissileBaseShape(sf::RectangleShape val);
	bool getAlive() const;
	void setAlive(bool val);
private:
	sf::RectangleShape missileBaseShape;
	bool alive;
};