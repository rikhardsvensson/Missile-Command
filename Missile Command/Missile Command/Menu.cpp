#include "Menu.h"

Menu::Menu()
{

}

Menu::~Menu()
{

}

void Menu::init(sf::RenderWindow* window, Settings* settings)
{
	this->settings = settings;
	this->window = window;

	headerText = sf::Text(settings->title, settings->font, settings->headerTextCharacterSize);
	headerText.setPosition(
		static_cast<float>(settings->resolution.x) / 2 - static_cast<float>(headerText.getGlobalBounds().width) / 2, 
		static_cast<float>(settings->resolution.y) / 3);

	highScoreText = sf::Text("", settings->font, settings->scoreTextCharacterSize);
	highScoreText.setColor(sf::Color::White);
	updateHighScoreText();

	sf::Text buttonText = sf::Text(settings->startButtonText, settings->font, settings->buttonTextCharacterSize);
	sf::FloatRect buttonTextBounds = buttonText.getGlobalBounds();

	sf::Vector2f buttonSize;
	buttonSize.x = settings->buttonTextPadding * 2 + buttonTextBounds.width;
	buttonSize.y = settings->buttonTextPadding * 2 + buttonTextBounds.height;
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
	
	button = Button(window, settings, buttonText, buttonShape);
}

int Menu::update(sf::Event* event, int currentState)
{
	handleInput(event, &currentState);
	button.update();
	return currentState;
}

void Menu::render()
{
	window->draw(headerText);
	window->draw(highScoreText);
	button.render();
}

void Menu::handleInput(sf::Event* event, int* currentState)
{
	switch (event->type)
	{
	case sf::Event::MouseButtonReleased:
		if (event->mouseButton.button == sf::Mouse::Left)
		{
			if (button.isMouseOverButton())
			{
				(*currentState) = State::GAME;
			}
		}
		break;
	case sf::Event::KeyPressed:
		if (event->key.code == sf::Keyboard::Escape)
		{
			window->close();
		}
		break;
	default:
		break;
	}
}

void Menu::initState(int currentState)
{
	if (currentState == State::MENU)
	{
		headerText.setString(settings->title);
		button.setButtonText(settings->continueButtonText);
	}
	else if (currentState == State::GAME_OVER)
	{
		headerText.setString(settings->gameOverText);
		button.setButtonText(settings->restartButtonText);
	}
	headerText.setPosition(
		static_cast<float>(settings->resolution.x) / 2 - static_cast<float>(headerText.getGlobalBounds().width) / 2,
		static_cast<float>(settings->resolution.y) / 3);

	updateHighScoreText();
}

void Menu::updateHighScoreText()
{
	std::string highScoreString = settings->highScoreName;

	int scorePosition = 1;

	for each (int highScore in settings->highScoreList)
	{
		highScoreString += "\n" + std::to_string(scorePosition) + ". " + std::to_string(highScore);
		scorePosition++;
	}

	highScoreText.setString(highScoreString);
}
