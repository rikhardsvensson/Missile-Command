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

void City::setCityShape(sf::RectangleShape val)
{
	cityShape = val;

	deadCityShape = val;
	deadCityShape.move(0, deadCityShape.getSize().y * 0.8);
	deadCityShape.setScale(1.0, 0.2);
}

sf::Vector2f City::getMeteorTarget()
{
	sf::Vector2f centerPos;
	if (alive)
	{
		centerPos = cityShape.getPosition();
		centerPos.x += cityShape.getSize().x / 2;
	}
	else
	{
		centerPos = deadCityShape.getPosition();
		centerPos.x += deadCityShape.getSize().x / 2;
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
