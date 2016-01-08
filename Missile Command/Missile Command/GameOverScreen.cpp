#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{

}

GameOverScreen::~GameOverScreen()
{

}

int GameOverScreen::update()
{
	return restartButton.update();
}

void GameOverScreen::render(sf::RenderWindow* window)
{
	window->draw(gameOverText);
	restartButton.render(window);
}