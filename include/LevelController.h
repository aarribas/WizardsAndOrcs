#pragma once
#include "HUDView.h"
#include "LevelModel.h"
#include "LevelView.h"
#include "PlayerController.h" 
#include "StaticObjectController.h"
#include "DynamicObjectController.h" 
#include "TmxParser/Tmx.h"


class LevelController
{
public:
	enum LevelProgressState
	{
		LEVEL_IN_PROGRESS,
		LEVEL_FINISHED,
		LEVEL_GAME_OVER
	};
	static const float m_TileSizeInMeters;
public:

	LevelController();
	~LevelController();

	void loadNewLevel(Tmx::Map* map);
	void draw();
	void update(const float elapsedTime);
	LevelProgressState getState(){return m_state;}

private:
	void loadMap(Tmx::Map* map);
	void computeLevelLogic();
	void addPlayer(const Vector4& playerInitialPosition);

	int  addEnemy(const Vector4& enemyPosition, std::string enemyName);
	void removeEnemy(int key);

	int  addStaticObject(const Vector4& position, std::string name);
	void removeStaticObject(int key);

	int  addDynamicObject();
	void removeDynamicObject(int key);

private:
	HUDView m_hudView;
	LevelModel m_levelModel;
	LevelView m_levelView;
	LevelProgressState m_state;
	PlayerController* m_playerController;
	std::map<int, AvatarController*> m_enemyControllers;
	int m_nextNewEnemyId;
	std::map<int, StaticObjectController*> m_staticObjectControllers;
	std::map<int, DynamicObjectController*> m_dynamicObjectControllers;
	int m_nextNewStaticObjectId;
	int m_nextNewDynamicObjectId;
	int m_toggleTime;
};