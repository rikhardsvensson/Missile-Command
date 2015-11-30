#include "City.h"

City::City()
{

}

City::~City()
{

}

void City::render(sf::RenderWindow* window)
{
	window->draw(cityShape);
}

void City::setCityShape(sf::RectangleShape val)
{
	cityShape = val;
}

sf::RectangleShape City::getCityShape() const
{
	return cityShape;
}

void City::setAlive(bool val)
{
	alive = val;
}

bool City::getAlive() const
{
	return alive;
}
