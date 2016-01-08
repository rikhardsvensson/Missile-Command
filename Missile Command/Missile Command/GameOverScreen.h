#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class GameOverScreen
{
public:
	enum {RESTART};

	GameOverScreen();
	~GameOverScreen();
	int run();

private:
	sf::Text gameOverText;
	Button restartButton;
};