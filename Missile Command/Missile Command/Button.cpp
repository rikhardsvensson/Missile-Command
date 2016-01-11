#include "Button.h"

Button::Button()
{

}

Button::Button(sf::Text buttonText, sf::RectangleShape buttonShape)
{
	this->buttonShape = buttonShape;
	this->buttonText = buttonText;
	sf::Vector2f buttonTextPosition = buttonShape.getPosition();
	buttonTextPosition.x += (buttonShape.getSize().x - buttonText.getGlobalBounds().width) / 2; //Adjusts position to center text on button.
	this->buttonText.setPosition(buttonTextPosition);
}

int Button::update(sf::RenderWindow* window, Settings* settings)
{
	sf::Vector2i mousePosition = getScaledMouseCoords(window, settings);
	bool isMouseOverButton = rectanglePointCollision(buttonShape, mousePosition);

	if (isMouseOverButton)
	{
		buttonShape.setFillColor(settings->restartButtonHoverColor);
	}
	else
	{
		buttonShape.setFillColor(settings->restartButtonColor);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverButton)
	{
		return CLICKED;
	}
	return NOT_CLICKED;
}

void Button::render(sf::RenderWindow* window)
{
	window->draw(buttonShape);
	window->draw(buttonText);
}
