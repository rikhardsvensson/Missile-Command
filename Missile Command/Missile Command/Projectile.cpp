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

	origToDest = destination - origin;
	origToDestDist = sqrtf(origToDest.x * origToDest.x + origToDest.y * origToDest.y);
}

Projectile::~Projectile()
{

}

void Projectile::update(std::vector<Explosion*>* explosions)
{
	sf::Vector2f currPosToDest = currentPosition - destination;
	if (sqrtf(currPosToDest.x * currPosToDest.x + currPosToDest.y * currPosToDest.y) <= speed || dying)
	{
		alive = false;
		explosions->push_back(new Explosion(projectileType, currentPosition, explosionMaximumRadius, explosionPropagationSpeed, explosionColor));
	}
	else
	{
		sf::Vector2f origToCurrPos = currentPosition - origin;
		float origToCurrPosDist = sqrtf(origToCurrPos.x * origToCurrPos.x + origToCurrPos.y * origToCurrPos.y);
		origToCurrPosDist += speed;

		//Avoid division with zero
		if (origToCurrPosDist > std::numeric_limits<float>::epsilon())
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
