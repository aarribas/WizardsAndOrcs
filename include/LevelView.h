#pragma once
#include "LevelModel.h"
#include "AvatarView.h"
#include "StaticObjectView.h"
#include "DynamicObjectView.h"

class LevelView
{
public:

	LevelView();
	~LevelView();
	void init(const LevelModel& levelModel);
	void initScene();
	void draw();
	void setPlayerView(AvatarView* playerView) {m_playerView = playerView;} 
	void addEnemyView(AvatarView*, int key);
	std::map<int, AvatarView*>&  getEnemyViews() {return m_enemyViews;} 
	void removeEnemyView(int key);

	void addStaticObjectView(StaticObjectView*, int key);
	std::map<int, StaticObjectView*>&  getStaticObjectViews() {return m_staticObjectViews;} 
	void removeStaticObjectView(int key);

	void addDynamicObjectView(DynamicObjectView*, int key);
	std::map<int, DynamicObjectView*>&  getDynamicObjectViews() {return m_dynamicObjectViews;} 
	void removeDynamicObjectView(int key);

private:
	LevelModel m_levelModel;
	std::vector<int> m_sceneGlIds;
	std::map<int, AvatarView*> m_enemyViews;
	std::map<int, StaticObjectView*> m_staticObjectViews;
	std::map<int, DynamicObjectView*> m_dynamicObjectViews;
	AvatarView* m_playerView;
};