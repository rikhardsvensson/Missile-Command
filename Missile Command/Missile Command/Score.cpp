#include "Score.h"

Score::Score()
{
	resetScore();
	scoreText = sf::Text();
}

Score::Score(sf::Font* font, sf::Vector2f position, sf::Color color, int characterSize, std::string scorePath)
{
	score = 0;
	highScore = 0;
	this->scorePath = scorePath;
	loadHighscore(scorePath);
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

void Score::loadHighscore(std::string path)
{
	std::string line;
	std::ifstream scoreFile(path);
	if (scoreFile.is_open())
	{
		std::getline(scoreFile, line);
		highScore = std::stoi(line);
		scoreFile.close();
	}
}

void Score::writeHighScore(std::string path)
{
	if (score > highScore)
	{
		std::ofstream scoreFile(path, std::ofstream::out);
		if (scoreFile.is_open())
		{
			scoreFile << score;
			scoreFile.close();
		}
	}
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
