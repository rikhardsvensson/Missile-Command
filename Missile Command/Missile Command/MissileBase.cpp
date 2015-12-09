#include "MissileBase.h"

MissileBase::MissileBase()
{

}

MissileBase::MissileBase(sf::Vector2f size, sf::Vector2f position)
{
	missileBaseShape.setFillColor(sf::Color::White);
	missileBaseShape.setSize(size);
	missileBaseShape.setPosition(position);
	alive = true;

	deadMissileBaseShape = missileBaseShape;
	deadMissileBaseShape.move(0, deadMissileBaseShape.getSize().y * 0.8);
	deadMissileBaseShape.setScale(1.0, 0.2);

	missileOrigin = position;
	missileOrigin.x += size.x / 2;
}

MissileBase::~MissileBase()
{

}

void MissileBase::render(sf::RenderWindow* window)
{
	if (alive)
	{
		window->draw(missileBaseShape);
	}
	else
	{
		window->draw(deadMissileBaseShape);
	}
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

void MissileBase::setAlive(bool val)
{
	alive = val;
	missileBaseShape.setScale(1.0, 0.1);
}

sf::Vector2f MissileBase::getMissileOrigin()
{
	return missileOrigin;
}

bool MissileBase::getAlive() const
{
	return alive;
}
