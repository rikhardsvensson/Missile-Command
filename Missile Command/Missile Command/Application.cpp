#include "Application.h"

Application::Application(std::mt19937* mt)
{
	currentState = State::MENU;

	window = new sf::RenderWindow();
	settings = settingsParser.getSettings();

	backgroundColor = sf::Color(0, 0, 0);
	menu.init(window, settings);
	game = Game(mt);
	game.init(window, settings);
}

Application::~Application()
{
	settingsParser.setSettings(settings);
	delete window;
}

int Application::run()
{
	createWindow(settings->fullscreen);
	sf::Event event;
	lastState = currentState;

	while (window->isOpen())
	{
		event = handleInput();

		window->clear(backgroundColor);

		if (currentState == State::GAME)
		{
			lastState = currentState;
			currentState = game.update(&event);
			game.render();
		}
		else if (currentState == State::MENU)
		{
			if (lastState != State::MENU)
			{
				menu.initState(currentState);
			}

			lastState = currentState;
			currentState = menu.update(&event, currentState);
			menu.render();
		}
		else if (currentState == State::GAME_OVER)
		{
			if (lastState != State::GAME_OVER)
			{
				menu.initState(currentState);
			}

			lastState = currentState;
			currentState = menu.update(&event, currentState);
			menu.render();

			if (currentState == State::GAME)
			{
				game.resetGame();
			}
		}

		window->display();
	}
	return 0;
}

sf::Event Application::handleInput()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;
		case sf::Event::KeyPressed:
			if ((sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) || sf::Keyboard::isKeyPressed(sf::Keyboard::RAlt)) && event.key.code == sf::Keyboard::Return)
			{
				settings->fullscreen = !settings->fullscreen;
				createWindow(settings->fullscreen);
			}
			return event;
			break;
		default:
			break;
		}
	}
	return event;
}

void Application::createWindow(bool fullscreen)
{
	sf::VideoMode videoMode = sf::VideoMode(settings->resolution.x, settings->resolution.y, 32);
	if (fullscreen)
	{
		window->create(videoMode, settings->title, sf::Style::Fullscreen);
	}
	else
	{
		window->create(videoMode, settings->title, sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
	}
	window->setVerticalSyncEnabled(true);
}
