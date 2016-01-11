#pragma once
#include <SFML/Graphics.hpp>
#include "SettingsParser.h"
#include "Button.h"

class GameOverScreen
{
public:
	enum {RESTART, NO_ACTION};

	GameOverScreen();
	~GameOverScreen();
	void init(Settings* settings);
	int update(sf::RenderWindow* window, Settings* settings);
	void render(sf::RenderWindow* window);

private:
	sf::Text gameOverText;
	Button restartButton;
};