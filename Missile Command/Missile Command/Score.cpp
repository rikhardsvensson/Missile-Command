#include "Score.h"

Score::Score()
{
	resetScore();
	scoreText = sf::Text();
}

Score::Score(sf::Font* font, sf::Vector2f position, sf::Color color, int characterSize)
{
	score = 0;
	scoreText = sf::Text("0", *font, characterSize);
	scoreText.setColor(color);
	setPosition(position);
}

Score::~Score()
{

}

void Score::render(sf::RenderWindow* window)
{
	window->draw(scoreText);
}

int Score::getScore() const
{
	return score;
}

void Score::offsetScore(int val)
{
	score += val;
	scoreText.setString(std::to_string(score));
}

void Score::resetScore()
{
	score = 0;
	scoreText.setString(std::to_string(score));
}

void Score::setCharacterSize(int val)
{
	scoreText.setCharacterSize(val);
}

void Score::setFont(sf::Font val)
{
	scoreText.setFont(val);
}

void Score::setPosition(sf::Vector2f val)
{
	scoreText.setPosition(val);
}

void Score::setColor(sf::Color val)
{
	scoreText.setColor(val);
}
