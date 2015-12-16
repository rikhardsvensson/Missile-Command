#pragma once
#include <SFML/Graphics.hpp>

class MissileBase
{
public:
	MissileBase();
	MissileBase(sf::Vector2f size, sf::Vector2f position, int ammo, int missilesTilCooldown);
	~MissileBase();

	void render(sf::RenderWindow* window);

	sf::RectangleShape getMissileBaseShape() const;
	void setMissileBaseShape(sf::RectangleShape val);
	sf::Vector2f getMeteorTarget();
	sf::Vector2f getMissileOrigin();

	int getAmmunition() const;
	void setAmmunition(int val);
	void offsetAmmunition(int val);
	int getCurrentMissilesTilCooldown() const;
	void setCurrentMissilesTilCooldown(int val);
	void offsetCurrentMissilesTilCooldown(int val);
private:
	sf::RectangleShape missileBaseShape;
	sf::Vector2f missileOrigin;
	int ammunition;
	int currentMissilesTilCooldown;
};