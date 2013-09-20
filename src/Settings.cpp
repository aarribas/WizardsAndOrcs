#include "Settings.h"

Settings::Settings():
	m_sfxOn(true),
	m_musicOn(true),
	m_difficulty(MEDIUM),
	m_sfxVolume(1),
	m_musicVolume(1)
{
	
}
Settings::~Settings()
{
}


void Settings::switchMusicOnOff()
{
	if(m_musicOn == true)
	{
		m_musicOn = false;
	}
	else
	{
		m_musicOn = true;
	}
}

void Settings::switchSfxOnOff()
{
	if(m_sfxOn == true)
	{
		m_sfxOn = false;
	}
	else
	{
		m_sfxOn = true;
	}
}

std::string  Settings::difficultyToString()
{
	switch (m_difficulty)
	{
		case LOW :
			return "*LOW* MEDIUM HIGH";
		case MEDIUM :
			return "LOW *MEDIUM* HIGH";
		case HIGH :
			return "LOW MEDIUM *HIGH*";
		default:
			return "*LOW* MEDIUM HIGH";
	};
}
std::string  Settings::sfxOnToString()
{
	if(m_sfxOn == true)
	{
		return "*ON*";
	}
	else
	{
		return "*OFF*";
	}

}
std::string  Settings::musicOnToString()
{
	if(m_musicOn == true)
	{
		return "*ON*";
	}
	else
	{
		return "*OFF*";
	}
}


void Settings::difficultyIncrease()
{

	switch(m_difficulty)
	{
	case LOW: m_difficulty = MEDIUM; break;
	case MEDIUM: m_difficulty = HIGH; break;
	case HIGH: m_difficulty = LOW; break;
	}
}

