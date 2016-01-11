#pragma once
#include <SFML/Graphics.hpp>
#include "SettingsParser.h"
#include "Util.h"

class Button
{
public:
	enum {CLICKED, NOT_CLICKED};

	Button();
	Button(sf::Text buttonText, sf::RectangleShape buttonShape);
	int update(sf::RenderWindow* window, Settings* settings);
	void render(sf::RenderWindow* window);
private:
	sf::Text buttonText;
	sf::RectangleShape buttonShape;
};