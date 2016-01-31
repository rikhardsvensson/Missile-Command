#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include "SettingsParser.h"

class Score
{
public:
	Score();
	Score(Settings* settings, sf::Vector2f position, sf::Color color);
	~Score();

	void render(sf::RenderWindow* window);

	int getScore() const;
	int getHighScore() const;
	void updateHighScore();
	void offsetScore(int val);
	void resetScore();
	void setCharacterSize(int val);
	void setFont(const sf::Font& val);
	void setPosition(const sf::Vector2f& val);
	void setColor(const sf::Color& val);

private:
	Settings* settings;
	int score;
	int currentHighScore;
	int currentScorePosition;
	sf::Text scoreText;
	std::string scoreName;
	std::string highScoreName;
	std::string scorePath = "";
	void updateScoreText();
};