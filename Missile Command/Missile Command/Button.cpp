#include "Button.h"

Button::Button()
{

}

Button::Button(sf::RenderWindow* window, Settings* settings, sf::Text buttonText, sf::RectangleShape buttonShape)
{
	this->settings = settings;
	this->window = window;
	this->buttonShape = buttonShape;
	this->buttonText = buttonText;
	sf::Vector2f buttonTextPosition = buttonShape.getPosition();
	buttonTextPosition.x += (buttonShape.getSize().x - buttonText.getGlobalBounds().width) / 2; //Adjusts position to center text on button.
	this->buttonText.setPosition(buttonTextPosition);
}

void Button::update()
{
	bool mouseOverButton = isMouseOverButton();

	if (mouseOverButton)
	{
		buttonShape.setFillColor(settings->buttonHoverColor);
	}
	else
	{
		buttonShape.setFillColor(settings->buttonColor);
	}
}

void Button::render()
{
	window->draw(buttonShape);
	window->draw(buttonText);
}

bool Button::isMouseOverButton()
{
	sf::Vector2i mousePosition = getScaledMouseCoords(window, settings);
	return rectanglePointCollision(buttonShape, mousePosition);
}

void Button::setButtonText(const std::string& buttonText)
{
	this->buttonText.setString(buttonText);

	sf::FloatRect buttonTextBounds = this->buttonText.getGlobalBounds();

	sf::Vector2f buttonSize;
	buttonSize.x = settings->buttonTextPadding * 2 + buttonTextBounds.width;
	buttonSize.y = settings->buttonTextPadding * 2 + buttonTextBounds.height;
	buttonShape.setSize(buttonSize);

	sf::Vector2f buttonTextPosition = buttonShape.getPosition();
	buttonTextPosition.x += (buttonShape.getSize().x - this->buttonText.getGlobalBounds().width) / 2; //Adjusts position to center text on button.
	this->buttonText.setPosition(buttonTextPosition);
}
