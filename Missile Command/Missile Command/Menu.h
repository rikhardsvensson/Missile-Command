#pragma once
#include <SFML/Graphics.hpp>
#include "SettingsParser.h"
#include "Button.h"

class Menu
{
public:
	enum {RESTART, NO_ACTION};

	Menu();
	~Menu();
	void init(sf::RenderWindow* window, Settings* settings);
	int update(sf::Event* event, int currentState);
	void render();
	void handleInput(sf::Event* event, int* currentState);
	void initState(int currentState);
private:
	void updateHighScoreText();
	sf::RenderWindow* window;
	Settings* settings;
	sf::Text headerText;
	sf::Text highScoreText;
	Button button;
};