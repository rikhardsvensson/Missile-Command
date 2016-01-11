#pragma once
#include <SFML/Graphics.hpp>
#include "Explosion.h"
#include "Util.h"

class Projectile
{
public:
	Projectile(const ProjectileParameters& mp);
	~Projectile();
	void update(std::vector<Explosion*>* explosions);
	void render(sf::RenderWindow* window);

	bool getAlive() const;
	void setAlive(bool val);
	sf::Vector2f getCurrentPosition() const;
	void setDying(bool val);
	bool getIsWaveSpawner() const;
	void setIsWaveSpawner(bool val);
	bool getReachedDestination() const;
private:
	ProjectileType projectileType;
	sf::Vector2f currentPosition;
	sf::Vector2f origin;
	sf::Vector2f destination;
	sf::Color projectileColor;
	float speed;
	bool alive;
	bool dying;
	bool reachedDestination;
	bool isWaveSpawner;

	sf::Vector2f origToDest; //Describes the path the projectile will travel as a vector.
	float origToDestDist; //The total distance of aforementioned path.

	sf::Color explosionColor;
	float explosionMaximumRadius;
	float explosionPropagationSpeed;
};