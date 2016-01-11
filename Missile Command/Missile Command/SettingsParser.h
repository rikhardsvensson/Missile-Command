#pragma once
#include <SFML\Graphics.hpp>
#include <fstream>
#include <cereal\archives\json.hpp>

struct Settings
{
	std::string fontPath = "arial.ttf";
	sf::Font font;
	sf::Vector2i resolution = sf::Vector2i(1280, 720);
	bool fullscreen = false;
	float missileSpeed = 5;
	float initialMeteorSpeed = 0.4f;
	float meteorSpeedIncreasePerLevel = 0.2f;
	float explosionMaximumRadius = 50;
	float explosionPropagationSpeed = 0.75f;
	int ammunitionPerLevel = 30;
	int initialNrOfMeteors = 12;
	int increaseOfMeteorsPerLevel = 3;
	int baseHitAmmunitionOffset = -10;
	int maxNrOfMeteorsPerLevel = 20;
	int maxNrOfMeteorsInWave = 5;
	int maxNrOfSpawnersInWave = 1;
	int scoreForMeteor = 25;
	int scoreForCity = 100;
	int scoreForRemainingMissile = 5;
	int highScore = 0;
	std::string scoreName = "SCORE: ";
	std::string highScoreName = "HIGH SCORE: ";
	std::string gameOverText = "GAME OVER";
	std::string restartButtonText = "RESTART";
	int ammunitionTextCharacterSize = 20;
	int scoreTextCharacterSize = 20;
	int restartButtonTextCharacterSize = 20;
	int restartButtonTextPadding = 5;
	int gameOverTextCharacterSize = 60;
	sf::Color groundColor = sf::Color(100, 50, 0);
	sf::Color missileColor = sf::Color::Magenta;
	sf::Color missileExplosionColor = sf::Color::Magenta;
	sf::Color meteorExplosionColor = sf::Color::Green;
	sf::Color meteorColor = sf::Color::Green;
	sf::Color restartButtonColor = sf::Color(70, 70, 70);
	sf::Color restartButtonHoverColor = sf::Color(100, 100, 100);

	template<class Archive>	void serialize(Archive& archive) //Gives the serialization library information on how and what to serialize.
	{
		archive(
			CEREAL_NVP(fontPath),
			CEREAL_NVP(resolution.x), CEREAL_NVP(resolution.y),
			CEREAL_NVP(fullscreen),
			CEREAL_NVP(missileSpeed),
			CEREAL_NVP(initialMeteorSpeed),
			CEREAL_NVP(meteorSpeedIncreasePerLevel),
			CEREAL_NVP(explosionMaximumRadius),
			CEREAL_NVP(explosionPropagationSpeed),
			CEREAL_NVP(ammunitionPerLevel),
			CEREAL_NVP(initialNrOfMeteors),
			CEREAL_NVP(increaseOfMeteorsPerLevel),
			CEREAL_NVP(baseHitAmmunitionOffset),
			CEREAL_NVP(maxNrOfMeteorsPerLevel),
			CEREAL_NVP(maxNrOfMeteorsInWave),
			CEREAL_NVP(maxNrOfSpawnersInWave),
			CEREAL_NVP(scoreForMeteor),
			CEREAL_NVP(scoreForCity),
			CEREAL_NVP(scoreForRemainingMissile),
			CEREAL_NVP(highScore),
			CEREAL_NVP(scoreName),
			CEREAL_NVP(highScoreName),
			CEREAL_NVP(gameOverText),
			CEREAL_NVP(restartButtonText),
			CEREAL_NVP(ammunitionTextCharacterSize),
			CEREAL_NVP(scoreTextCharacterSize),
			CEREAL_NVP(restartButtonTextCharacterSize),
			CEREAL_NVP(restartButtonTextPadding),
			CEREAL_NVP(gameOverTextCharacterSize),
			CEREAL_NVP(groundColor.r), CEREAL_NVP(groundColor.g), CEREAL_NVP(groundColor.b),
			CEREAL_NVP(missileColor.r),	CEREAL_NVP(missileColor.g),	CEREAL_NVP(missileColor.b),
			CEREAL_NVP(missileExplosionColor.r), CEREAL_NVP(missileExplosionColor.g), CEREAL_NVP(missileExplosionColor.b),
			CEREAL_NVP(meteorExplosionColor.r),	CEREAL_NVP(meteorExplosionColor.g),	CEREAL_NVP(meteorExplosionColor.b),
			CEREAL_NVP(meteorColor.r), CEREAL_NVP(meteorColor.g), CEREAL_NVP(meteorColor.b),
			CEREAL_NVP(restartButtonColor.r), CEREAL_NVP(restartButtonColor.g), CEREAL_NVP(restartButtonColor.b),
			CEREAL_NVP(restartButtonHoverColor.r), CEREAL_NVP(restartButtonHoverColor.g), CEREAL_NVP(restartButtonHoverColor.b)
			);
	}
};

//A file parser that automatically tries to load a settings file on construction and writes to it on destruction.
//If no file is found when reading it creates a file with the default settings found in the Settings stuct.
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