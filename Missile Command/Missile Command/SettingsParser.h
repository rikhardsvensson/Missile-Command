#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>
#include <cereal\archives\json.hpp>

struct Settings
{
	std::string fontPath = "arial.ttf";
	std::string scorePath = "data.txt";
	std::string scoreName = "Score: ";
	std::string highScoreName = "High score: ";
	sf::Vector2i windowSize = sf::Vector2i(1280, 720);
	sf::Color groundColor = sf::Color(100, 50, 0);
	sf::Color missileColor = sf::Color::Magenta;
	sf::Color missileExplosionColor = sf::Color::Magenta;
	sf::Color meteorExplosionColor = sf::Color::Green;
	sf::Color meteorColor = sf::Color::Green;
	int ammunitionTextCharacterSize = 20;
	int scoreTextCharacterSize = 20;
	float missileSpeed = 5;
	float initialMeteorSpeed = 0.4f;
	float meteorSpeedIncreasePerLevel = 0.2f;
	float explosionMaximumRadius = 50;
	float explosionPropagationSpeed = 0.75f;
	int ammunitionPerLevel = 30;
	int initialNrOfMeteors = 12;
	int increaseOfMeteorsPerLevel = 3;
	int baseHitAmmunitionOffset = -10;
	int missilesTilCooldown = 3;
	int missileBaseCooldownTime = 3;
	int maxNrOfMeteorsPerLevel = 20;
	int maxNrOfMeteorsInWave = 5;
	int maxNrOfSpawnersInWave = 1;
	int scoreForMeteor = 25;
	int scoreForCity = 100;
	int scoreForRemainingMissile = 5;
	int highScore = 0;

	template<class Archive>
	void serialize(Archive& archive)
	{
		archive(
			CEREAL_NVP(fontPath),
			CEREAL_NVP(scorePath),
			CEREAL_NVP(scoreName),
			CEREAL_NVP(highScoreName),
			CEREAL_NVP(windowSize.x),
			CEREAL_NVP(windowSize.y),
			CEREAL_NVP(groundColor.r),
			CEREAL_NVP(groundColor.g),
			CEREAL_NVP(groundColor.b),
			CEREAL_NVP(missileColor.r),
			CEREAL_NVP(missileColor.g),
			CEREAL_NVP(missileColor.b),
			CEREAL_NVP(missileExplosionColor.r),
			CEREAL_NVP(missileExplosionColor.g),
			CEREAL_NVP(missileExplosionColor.b),
			CEREAL_NVP(meteorExplosionColor.r),
			CEREAL_NVP(meteorExplosionColor.g),
			CEREAL_NVP(meteorExplosionColor.b),
			CEREAL_NVP(meteorColor.r),
			CEREAL_NVP(meteorColor.g),
			CEREAL_NVP(meteorColor.b),
			CEREAL_NVP(ammunitionTextCharacterSize),
			CEREAL_NVP(scoreTextCharacterSize),
			CEREAL_NVP(missileSpeed),
			CEREAL_NVP(initialMeteorSpeed),
			CEREAL_NVP(meteorSpeedIncreasePerLevel),
			CEREAL_NVP(explosionMaximumRadius),
			CEREAL_NVP(explosionPropagationSpeed),
			CEREAL_NVP(ammunitionPerLevel),
			CEREAL_NVP(initialNrOfMeteors),
			CEREAL_NVP(increaseOfMeteorsPerLevel),
			CEREAL_NVP(baseHitAmmunitionOffset),
			CEREAL_NVP(missilesTilCooldown),
			CEREAL_NVP(missileBaseCooldownTime),
			CEREAL_NVP(maxNrOfMeteorsPerLevel),
			CEREAL_NVP(maxNrOfMeteorsInWave),
			CEREAL_NVP(maxNrOfSpawnersInWave),
			CEREAL_NVP(scoreForMeteor),
			CEREAL_NVP(scoreForCity),
			CEREAL_NVP(scoreForRemainingMissile),
			CEREAL_NVP(highScore)
			);
	}
};

class SettingsParser
{
public:
	SettingsParser();
	~SettingsParser();

	Settings* getSettings() const;
	void setSettings(Settings* val);
private:
	Settings *settings;
	void writeSettings();
	void readSettings();
};