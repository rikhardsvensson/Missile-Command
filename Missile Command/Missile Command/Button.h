#pragma once
#include <SFML/Graphics.hpp>

class Button
{
public:
	enum {CLICKED};

	Button();
	Button(sf::Text buttonText, sf::RectangleShape buttonShape);
	int update();
	void render(sf::RenderWindow* window);
private:
	sf::Text buttonText;
	sf::RectangleShape buttonShape;

};