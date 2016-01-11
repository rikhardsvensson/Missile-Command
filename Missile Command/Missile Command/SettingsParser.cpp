#include "SettingsParser.h"

SettingsParser::SettingsParser()
{
	settings = new Settings();
	readSettings();
	if (!settings->font.loadFromFile(settings->fontPath))
	{
		//TODO: error handling
	}
}

SettingsParser::~SettingsParser()
{
	writeSettings();
	delete settings;
}

Settings* SettingsParser::getSettings() const
{
	return settings;
}

void SettingsParser::setSettings(Settings* val)
{
	settings = val;
}

void SettingsParser::writeSettings()
{
	std::ofstream outStream("settings.json");
	cereal::JSONOutputArchive outArchive(outStream);
	outArchive.setNextName("Settings");
	outArchive(*settings);
}

void SettingsParser::readSettings()
{
	std::ifstream inStream("settings.json");
	if (inStream.is_open())
	{
		cereal::JSONInputArchive inArchive(inStream);
		inArchive(*settings);
	}
}
