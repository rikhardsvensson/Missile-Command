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

sf::RectangleShape MissileBase::getMissileBaseShape() const
{
	return missileBaseShape;
}

void MissileBase::setAlive(bool val)
{
	alive = val;
}

sf::Vector2f MissileBase::getMissileOrigin()
{
	return missileOrigin;
}

bool MissileBase::getAlive() const
{
	return alive;
}
