#pragma once
#include <string>

class GameProgressManager
{
public:
	enum GameProgressState
	{
		NOT_STARTED,
		LOADING_LEVEL,
		LOADING_SAVED_GAME,
		IN_PROGRESS,
		PAUSED,
		FINISHED,
		GAME_OVER
	};

public:
	friend class Core;
	GameProgressManager();
	~GameProgressManager();

	void init();
	GameProgressState getGameProgressState(){return m_gameProgressState;};
	void setGameProgressState(GameProgressState state){m_gameProgressState = state;};
	int getLevel(){return m_level;};
	void setLevel(int x){m_level = x;};
	std::string getGameName( ){return m_gameName;};
	void setGameName( std::string name ){m_gameName = name;};
private:
	GameProgressState m_gameProgressState;
	int m_level;
	std::string m_gameName;

};