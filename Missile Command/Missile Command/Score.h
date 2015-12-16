#pragma once
#include "SFML/Graphics.hpp"

class Score
{
public:
	Score();
	Score(sf::Font* font, sf::Vector2f position, sf::Color color, int characterSize);
	~Score();

	void render(sf::RenderWindow* window);

	int getScore() const;
	void offsetScore(int val);
	void resetScore();
	void setCharacterSize(int val);
	void setFont(sf::Font val);
	void setPosition(sf::Vector2f val);
	void setColor(sf::Color val);
private:
	int score;
	sf::Text scoreText;
};