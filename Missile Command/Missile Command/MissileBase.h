#pragma once
#include <SFML/Graphics.hpp>

class MissileBase
{
public:
	MissileBase();
	MissileBase(sf::Vector2f size, sf::Vector2f position);
	~MissileBase();

	void render(sf::RenderWindow* window);

	sf::RectangleShape getMissileBaseShape() const;
	void setMissileBaseShape(sf::RectangleShape val);
	bool getAlive() const;
	void setAlive(bool val);
	sf::Vector2f getMissileOrigin();
private:
	sf::RectangleShape missileBaseShape;
	bool alive;
	sf::Vector2f missileOrigin;
};