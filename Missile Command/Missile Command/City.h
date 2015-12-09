#pragma once
#include <SFML/Graphics.hpp>

class City
{
public:
	City();
	~City();

	void render(sf::RenderWindow* window);

	sf::RectangleShape getCityShape() const;
	void setCityShape(sf::RectangleShape val);
	sf::Vector2f getMeteorTarget();
	bool getAlive() const;
	void setAlive(bool val);
private:
	sf::RectangleShape cityShape;
	sf::RectangleShape deadCityShape;
	bool alive;
};