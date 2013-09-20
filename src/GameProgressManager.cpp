#include "GameProgressManager.h"	

GameProgressManager::GameProgressManager():
m_gameProgressState(NOT_STARTED),
m_level(0),
m_gameName("default")
{
}

GameProgressManager::~GameProgressManager()
{
}

void GameProgressManager::init()
{
	m_gameProgressState = NOT_STARTED;
	m_level = 0;
}
