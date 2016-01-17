#pragma once
#include <SFML/Graphics.hpp>
#include "SettingsParser.h"
#include "Util.h"

class MissileBase
{
public:
	MissileBase();
	MissileBase(sf::Vector2f size, sf::Vector2f position, Settings* settings);
	~MissileBase();

	void render(sf::RenderWindow* window);

	sf::RectangleShape getMissileBaseShape() const;
	void setMissileBaseShape(const sf::RectangleShape& val);
	sf::Vector2f getMeteorTarget() const; //Used when creating meteors to get the missile base's center position.
	sf::Vector2f getMissileOrigin() const; //Returns the position at which new missiles are first created.
	int getAmmunition() const;
	void setAmmunition(int val);
	void offsetAmmunition(int val);
private:
	sf::RectangleShape missileBaseShape;
	sf::Vector2f missileOrigin;
	int ammunition;
	sf::Text ammunitionText;

	void updateAmmunitionText();
};