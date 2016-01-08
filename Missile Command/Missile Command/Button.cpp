#include "Button.h"

Button::Button()
{

}

Button::Button(sf::Text buttonText, sf::RectangleShape buttonShape)
{
	this->buttonShape = buttonShape;
	this->buttonText = buttonText;
}

int Button::update()
{

}

void Button::render(sf::RenderWindow* window)
{
	window->draw(buttonShape);
	window->draw(buttonText);
}
