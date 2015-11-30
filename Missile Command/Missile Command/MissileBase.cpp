#include "MissileBase.h"


MissileBase::MissileBase()
{

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

bool MissileBase::getAlive() const
{
	return alive;
}
