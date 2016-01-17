#include "Score.h"

Score::Score()
{
	resetScore();
	scoreText = sf::Text();
}

Score::Score(Settings* settings, sf::Vector2f position, sf::Color color)
{
	score = 0;
	this->highScore = settings->highScore;
	this->scoreName = settings->scoreName;
	this->highScoreName = settings->highScoreName;
	scoreText = sf::Text("", settings->font, settings->scoreTextCharacterSize);
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

void Score::setFont(const sf::Font& val)
{
	scoreText.setFont(val);
}

void Score::setPosition(const sf::Vector2f& val)
{
	scoreText.setPosition(val);
}

void Score::setColor(const sf::Color& val)
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
