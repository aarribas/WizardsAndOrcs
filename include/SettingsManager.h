#pragma once

#include <string>
#include "Settings.h"

class SettingsManager
{
private:
	static Settings* m_settings;

public:
	friend class Core;
	SettingsManager();
	~SettingsManager();

	void init();

	Settings* getSettings();

};