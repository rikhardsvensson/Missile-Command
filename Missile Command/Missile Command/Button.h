#pragma once
#include <SFML/Graphics.hpp>
#include "SettingsParser.h"
#include "Util.h"

class Button
{
public:
	Button();
	Button(sf::RenderWindow* window, Settings* settings, sf::Text buttonText, sf::RectangleShape buttonShape);
	void update();
	void render();
	bool isMouseOverButton();
	void setButtonText(const std::string& buttonText);
private:
	sf::RenderWindow* window;
	Settings* settings;
	sf::Text buttonText;
	sf::RectangleShape buttonShape;
};