#pragma once
#include "Game.h"
#include "Menu.h"
#include "SettingsParser.h"
#include "Util.h"

class Application
{
public:
	Application(std::mt19937* mt);
	~Application();

	int run();

private:
	int currentState;
	int lastState;

	Game game;
	Menu menu;
	SettingsParser settingsParser;
	sf::RenderWindow* window;
	Settings* settings;
	sf::Color backgroundColor;

	sf::Event handleInput();
	void createWindow(bool fullscreen);
};