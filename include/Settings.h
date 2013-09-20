#pragma once


#include <string>
//probably too simplistic. We expect Settings to be directly accessed.
class Settings
{
public:
	enum Difficulty
	{
		LOW,
		MEDIUM,
		HIGH
	};

	Settings();
	~Settings();

	std::string difficultyToString();
	std::string sfxOnToString();
	std::string musicOnToString();

	Difficulty getDifficulty(){return m_difficulty; };
	bool isSfxOn(){return m_sfxOn;};
	bool isMusicOn(){return m_musicOn;};

	float getSfxVolume(){return m_sfxVolume;};
	float getMusicVolume(){return m_musicVolume;};

	void difficultyIncrease();
	void switchMusicOnOff();
	void switchSfxOnOff();

private:
	Difficulty m_difficulty;
	bool m_sfxOn;
	bool m_musicOn;
	float m_sfxVolume;
	float m_musicVolume;
};