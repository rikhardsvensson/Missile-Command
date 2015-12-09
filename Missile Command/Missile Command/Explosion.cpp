#include "Explosion.h"

Explosion::Explosion(ProjectileType projectileType, sf::Vector2f centerPosition, float maximumRadius, float propagationSpeed, sf::Color explosionColor)
{
	this->projectileType = projectileType;
	this->centerPosition = centerPosition;
	explosionShape.setPosition(centerPosition);
	explosionShape.setFillColor(explosionColor);
	explosionShape.setRadius(0);
	this->maximumRadius = maximumRadius;
	this->propagationSpeed = propagationSpeed;
	alive = true;
}

Explosion::~Explosion()
{

}

void Explosion::update()
{
	if (explosionShape.getRadius() >= maximumRadius)
	{
		propagationSpeed = -propagationSpeed;
	}
	explosionShape.setRadius(explosionShape.getRadius() + propagationSpeed);
	centerPosition.x -= propagationSpeed;
	centerPosition.y -= propagationSpeed;
	explosionShape.setPosition(centerPosition);

	if (propagationSpeed < 0 && explosionShape.getRadius() <= 0)
	{
		alive = false;
	}
}

void Explosion::render(sf::RenderWindow* window)
{
	window->draw(explosionShape);
}

bool Explosion::getAlive() const
{
	return alive;
}

ProjectileType Explosion::getProjectileType() const
{
	return projectileType;
}

sf::CircleShape Explosion::getExplosionShape() const
{
	return explosionShape;
}
