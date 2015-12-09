#pragma once
#include <SFML/Graphics.hpp>
#include "Util.h"

class Explosion
{
public:
	Explosion(ProjectileType projectileType, sf::Vector2f centerPosition, float maximumRadius, float propagationSpeed, sf::Color explosionColor);
	~Explosion();

	void update();
	void render(sf::RenderWindow* window);
	bool getAlive() const;
	ProjectileType getProjectileType() const;
	sf::CircleShape getExplosionShape() const;
private:
	ProjectileType projectileType;
	sf::Vector2f centerPosition;
	sf::CircleShape explosionShape;
	float maximumRadius;
	float propagationSpeed;
	bool alive;
};