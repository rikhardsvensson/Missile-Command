#include "MissileBase.h"

MissileBase::MissileBase()
{

}

MissileBase::MissileBase(sf::Vector2f size, sf::Vector2f position, Settings* settings)
{
	missileBaseShape.setFillColor(sf::Color::White);
	missileBaseShape.setSize(size);
	missileBaseShape.setPosition(position);
	
	this->ammunition = settings->ammunitionPerLevel;
	ammunitionText.setColor(sf::Color::White);
	ammunitionText.setCharacterSize(settings->ammunitionTextCharacterSize);
	ammunitionText.setFont(settings->font);

	missileOrigin = position;
	missileOrigin.x += size.x / 2;
}

MissileBase::~MissileBase()
{

}

void MissileBase::render(sf::RenderWindow* window)
{
	window->draw(missileBaseShape);
	window->draw(ammunitionText);
}

void MissileBase::setMissileBaseShape(const sf::RectangleShape& val)
{
	missileBaseShape = val;
}

sf::Vector2f MissileBase::getMeteorTarget() const
{
	return getRectangleCenterPosition(missileBaseShape);
}

sf::RectangleShape MissileBase::getMissileBaseShape() const
{
	return missileBaseShape;
}

sf::Vector2f MissileBase::getMissileOrigin() const
{
	return missileOrigin;
}

int MissileBase::getAmmunition() const
{
	return ammunition;
}

void MissileBase::setAmmunition(int val)
{
	ammunition = val;
	updateAmmunitionText();
}

void MissileBase::offsetAmmunition(int val)
{
	ammunition += val;
	updateAmmunitionText();
}

void MissileBase::updateAmmunitionText()
{
	ammunitionText.setString(std::to_string(ammunition));
	sf::FloatRect ammunitionTextRect = ammunitionText.getGlobalBounds();
	sf::Vector2f missileBasePos = missileBaseShape.getPosition();
	sf::Vector2f missileBaseSize = missileBaseShape.getSize();
	ammunitionText.setPosition(missileBasePos.x + missileBaseSize.x / 2 - ammunitionTextRect.width / 2, missileBasePos.y + missileBaseSize.y);
}
