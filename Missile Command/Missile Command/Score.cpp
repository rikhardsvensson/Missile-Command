#include "Score.h"

Score::Score()
{
	resetScore();
	scoreText = sf::Text();
}

Score::Score(sf::Font* font, sf::Vector2f position, sf::Color color, int characterSize, int highScore, std::string scoreName, std::string highScoreName)
{
	score = 0;
	this->highScore = highScore;
	this->scoreName = scoreName;
	this->highScoreName = highScoreName;
	scoreText = sf::Text("", *font, characterSize);
	updateScoreText();
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

int Score::getHighScore() const
{
	return highScore;
}

void Score::updateHighScore()
{
	if (score > highScore)
	{
		highScore = score;
		updateScoreText();
	}
}

void Score::offsetScore(int val)
{
	score += val;
	updateScoreText();
}

void Score::resetScore()
{
	score = 0;
	updateScoreText();
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

void Score::updateScoreText()
{
	std::string outputText;
	outputText += highScoreName;
	outputText += std::to_string(highScore);
	outputText += "\n" + scoreName;
	outputText += std::to_string(score);
	scoreText.setString(outputText);
}
