#pragma once
#include "StaticObjectModel.h"
#include "LevelModel.h"
#include "AvatarModel.h" 

class StaticObjectLogicCalculator
{
public:
	StaticObjectLogicCalculator();
	~StaticObjectLogicCalculator();
public:
	void init(LevelModel* levelModel, StaticObjectModel* staticObjectModel);
	void computeLogic();

private:
	bool collides(const AvatarModel::Rect &rect);

private:
	StaticObjectModel* m_staticObjectModel;
	LevelModel* m_levelModel;
};