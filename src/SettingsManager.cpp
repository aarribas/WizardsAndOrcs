#include "SettingsManager.h"
#include "Settings.h"

Settings* SettingsManager::m_settings = new Settings();

SettingsManager::SettingsManager()
{
	
}
SettingsManager::~SettingsManager()
{
}

void SettingsManager::init()
{
	
}

Settings* SettingsManager::getSettings()
{
	return this->m_settings;
}