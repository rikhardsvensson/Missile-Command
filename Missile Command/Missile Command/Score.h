#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>

class Score
{
public:
	Score();
	Score(sf::Font* font, sf::Vector2f position, sf::Color color, int characterSize, int highScore, std::string scoreName, std::string highScoreName);
	~Score();

	void render(sf::RenderWindow* window);

	int getScore() const;
	int getHighScore() const;
	void updateHighScore();
	void offsetScore(int val);
	void resetScore();
	void setCharacterSize(int val);
	void setFont(sf::Font val);
	void setPosition(sf::Vector2f val);
	void setColor(sf::Color val);

private:
	int score;
	int highScore;
	sf::Text scoreText;
	std::string scoreName;
	std::string highScoreName;
	std::string scorePath = "";
	void updateScoreText();
};