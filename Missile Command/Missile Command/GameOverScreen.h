#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"

class GameOverScreen
{
public:
	enum {RESTART};

	GameOverScreen();
	~GameOverScreen();
	int update();
	void render(sf::RenderWindow* window);

private:
	sf::Text gameOverText;
	Button restartButton;
};