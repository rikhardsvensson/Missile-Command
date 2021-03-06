#include "Projectile.h"

Projectile::Projectile(const ProjectileParameters& mp)
{
	projectileType = mp.projectileType;
	origin = mp.origin;
	currentPosition = origin;
	destination = mp.destination;
	speed = mp.projectileSpeed;
	projectileColor = mp.projectileColor;
	explosionColor = mp.explosionColor;
	explosionMaximumRadius = mp.explosionMaximumRadius;
	explosionPropagationSpeed = mp.explosionPropagationSpeed;
	alive = true;
	dying = false;
	reachedDestination = false;
	if (mp.projectileType == ProjectileType::METEOR)
	{
		isWaveSpawner = mp.isWaveSpawner;
	}
	else
	{
		isWaveSpawner = false;
	}
	origToDest = destination - origin;
	origToDestDist = getVectorLength(origToDest);
}

Projectile::~Projectile()
{

}

void Projectile::update(std::vector<Explosion*>* explosions)
{
	sf::Vector2f currPosToDest = currentPosition - destination;
	float currPosToDestDist = getVectorLength(currPosToDest);

	if (currPosToDestDist <= speed || dying) //Kills the projectile.
	{
		alive = false;
		if (currPosToDestDist <= speed)
		{
			reachedDestination = true;
		}
		explosions->push_back(new Explosion(projectileType, currentPosition, explosionMaximumRadius, explosionPropagationSpeed, explosionColor));
	}
	else //Moves the projectile along it's path.
	{
		sf::Vector2f origToCurrPos = currentPosition - origin;
		float origToCurrPosDist = getVectorLength(origToCurrPos);
		origToCurrPosDist += speed;

		if (origToCurrPosDist > std::numeric_limits<float>::epsilon()) //Avoid division with zero
		{
			float distanceFactor = origToCurrPosDist / origToDestDist;
			currentPosition = origin + origToDest * distanceFactor;
		}
	}
}

void Projectile::render(sf::RenderWindow* window)
{
	sf::Vertex line[] =
	{
		sf::Vertex(origin, projectileColor),
		sf::Vertex(currentPosition, projectileColor)
	};

	window->draw(line, 2, sf::Lines);
}

bool Projectile::getAlive() const
{
	return alive;
}

void Projectile::setAlive(bool val)
{
	alive = val;
}

sf::Vector2f Projectile::getCurrentPosition() const
{
	return currentPosition;
}

void Projectile::setDying(bool val)
{
	dying = val;
}

bool Projectile::getIsWaveSpawner() const
{
	return isWaveSpawner;
}

void Projectile::setIsWaveSpawner(bool val)
{
	isWaveSpawner = val;
}

bool Projectile::getReachedDestination() const
{
	return reachedDestination;
}
