#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{

}

GameOverScreen::~GameOverScreen()
{

}

void GameOverScreen::init(Settings* settings)
{
	gameOverText = sf::Text(settings->gameOverText, settings->font, settings->gameOverTextCharacterSize);
	gameOverText.setPosition
		(
		static_cast<float>(settings->resolution.x) / 2 - static_cast<float>(gameOverText.getGlobalBounds().width) / 2, 
		static_cast<float>(settings->resolution.y) / 3
		);

	sf::Text buttonText = sf::Text(settings->restartButtonText, settings->font, settings->restartButtonTextCharacterSize);
	sf::FloatRect buttonTextBounds = buttonText.getGlobalBounds();

	sf::Vector2f buttonSize;
	buttonSize.x = settings->restartButtonTextPadding * 2 + buttonTextBounds.width;
	buttonSize.y = settings->restartButtonTextPadding * 2 + buttonTextBounds.height;
	sf::RectangleShape buttonShape;
	buttonShape.setSize(buttonSize);
	buttonShape.setFillColor(sf::Color::Black);
	buttonShape.setOutlineColor(sf::Color::White);
	buttonShape.setOutlineThickness(1);
	buttonShape.setPosition
		(
		static_cast<float>(settings->resolution.x) / 2 - static_cast<float>(buttonSize.x) / 2,
		static_cast<float>(settings->resolution.y) / 2
		);
	
	restartButton = Button(buttonText, buttonShape);
}

int GameOverScreen::update(sf::RenderWindow* window, Settings* settings)
{
	if (restartButton.update(window, settings) == Button::CLICKED)
	{
		return RESTART;
	}
	return NO_ACTION;
}

void GameOverScreen::render(sf::RenderWindow* window)
{
	window->draw(gameOverText);
	restartButton.render(window);
}