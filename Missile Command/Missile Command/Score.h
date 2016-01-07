#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>

class Score
{
public:
	Score();
	Score(sf::Font* font, sf::Vector2f position, sf::Color color, int characterSize, std::string scorePath);
	~Score();

	void render(sf::RenderWindow* window);

	int getScore() const;
	int getHighScore() const;
	void offsetScore(int val);
	void resetScore();
	void setCharacterSize(int val);
	void setFont(sf::Font val);
	void setPosition(sf::Vector2f val);
	void setColor(sf::Color val);
	void writeHighScore(std::string path);

private:
	int score;
	int highScore;
	sf::Text scoreText;
	std::string scoreName = "Score: ";
	std::string highScoreName = "High score: ";
	std::string scorePath = "";
	void loadHighscore(std::string path);
	void updateScoreText();
};