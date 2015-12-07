#include "Missile.h"

Missile::Missile(sf::Vector2f origin, sf::Vector2f destination, float speed)
{
	this->origin = origin;
	this->destination = destination;
	currentPosition = origin;
	this->speed = speed;
	alive = true;
}

Missile::~Missile()
{

}

void Missile::update()
{
	sf::Vector2f currPosToDest = currentPosition - destination;
	if (sqrtf(currPosToDest.x * currPosToDest.x + currPosToDest.y * currPosToDest.y) <= speed)
	{
		alive = false;
	}
	else
	{
		sf::Vector2f origToDest = destination - origin;
		float origToDestDist = sqrtf(origToDest.x * origToDest.x + origToDest.y * origToDest.y);

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

void Missile::render(sf::RenderWindow* window)
{
	sf::Vertex line[] =
	{
		sf::Vertex(origin, sf::Color::Magenta),
		sf::Vertex(currentPosition, sf::Color::Magenta)
	};

	window->draw(line, 2, sf::Lines);
}

bool Missile::getAlive() const
{
	return alive;
}