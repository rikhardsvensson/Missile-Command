#include "MissileBase.h"

MissileBase::MissileBase()
{

}

MissileBase::MissileBase(sf::Vector2f size, sf::Vector2f position, int ammunition, int missilesTilCooldown)
{
	missileBaseShape.setFillColor(sf::Color::White);
	missileBaseShape.setSize(size);
	missileBaseShape.setPosition(position);
	this->ammunition = ammunition;
	currentMissilesTilCooldown = missilesTilCooldown;

	missileOrigin = position;
	missileOrigin.x += size.x / 2;
}

MissileBase::~MissileBase()
{

}

void MissileBase::render(sf::RenderWindow* window)
{
	window->draw(missileBaseShape);
}

void MissileBase::setMissileBaseShape(sf::RectangleShape val)
{
	missileBaseShape = val;
}

sf::Vector2f MissileBase::getMeteorTarget()
{
	sf::Vector2f centerPos = missileBaseShape.getPosition();
	centerPos.x += missileBaseShape.getSize().x / 2;
	return centerPos;
}

sf::RectangleShape MissileBase::getMissileBaseShape() const
{
	return missileBaseShape;
}

sf::Vector2f MissileBase::getMissileOrigin()
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
}

void MissileBase::offsetAmmunition(int val)
{
	ammunition += val;
}

int MissileBase::getCurrentMissilesTilCooldown() const
{
	return currentMissilesTilCooldown;
}

void MissileBase::setCurrentMissilesTilCooldown(int val)
{
	currentMissilesTilCooldown = val;
}

void MissileBase::offsetCurrentMissilesTilCooldown(int val)
{
	currentMissilesTilCooldown += val;
}
