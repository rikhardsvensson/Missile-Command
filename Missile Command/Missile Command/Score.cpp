#include "Score.h"

Score::Score()
{
	resetScore();
	scoreText = sf::Text();
}

Score::Score(Settings* settings, sf::Vector2f position, sf::Color color)
{
	this->settings = settings;
	score = 0;
	currentScorePosition = settings->highScoreList.size();
	this->currentHighScore = settings->highScoreList[0];
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
	return currentHighScore;
}

void Score::updateHighScore()
{
	if (currentScorePosition < settings->highScoreList.size())
	{
		settings->highScoreList.erase(settings->highScoreList.begin() + currentScorePosition);
	}

	bool scoreListUpdated = false;
	for (int i = currentScorePosition - 1; i >= 0; i--)
	{
		if (score > settings->highScoreList[i])
		{
			currentScorePosition = i;
		}
	}

	settings->highScoreList.insert(settings->highScoreList.begin() + currentScorePosition, score);

	while (settings->highScoreList.size() > 5)
	{
		settings->highScoreList.pop_back();
	}

	currentHighScore = settings->highScoreList[0];
	updateScoreText();
}

void Score::offsetScore(int val)
{
	score += val;
	updateHighScore();
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
	outputText += std::to_string(currentHighScore);
	outputText += "\n" + scoreName;
	outputText += std::to_string(score);
	scoreText.setString(outputText);
}
