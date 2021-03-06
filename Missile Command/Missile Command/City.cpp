#include "City.h"

City::City()
{

}

City::~City()
{

}

void City::render(sf::RenderWindow* window)
{
	if (alive)
	{
		window->draw(cityShape);
	}
	else
	{
		window->draw(deadCityShape);
	}
}

void City::setCityShape(const sf::RectangleShape& val)
{
	cityShape = val;

	deadCityShape = val;
	deadCityShape.move(0.0f, deadCityShape.getSize().y * 0.8f);
	deadCityShape.setScale(1.0f, 0.2f);
}

sf::Vector2f City::getMeteorTarget() const
{
	sf::Vector2f centerPos;
	if (alive)
	{
		centerPos = getRectangleCenterPosition(cityShape);
	}
	else
	{
		centerPos = getRectangleCenterPosition(deadCityShape);
	}
	return centerPos;
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
