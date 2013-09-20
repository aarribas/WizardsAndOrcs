#pragma once
#include "EnemyController.h"
#include "EnemyStaticModel.h"
#include "EnemyLogicCalculator.h"
#include "EnemyStaticView.h"
#include "Vector4.h"
#include "LevelModel.h"
#include "LevelView.h"

class EnemyFactory
{
public:
	enum PatrollingType
	{
		ENEMY_PATROLLING_HORIZONTAL,
		ENEMY_PATROLLING_VERTICAL,
		ENEMY_PATROLLING_STATIC
	};
public:
	static EnemyController* create(LevelModel* levelModel,LevelView* levelView,int id,std::string name, const Vector4& position); 
private:
	static EnemyController* createGrunt(LevelModel* levelModel, LevelView* levelView, int id, const Vector4& position, PatrollingType patrolling); 
	static EnemyController* createPeon(LevelModel* levelModel, LevelView* levelView, int id, const Vector4& position, PatrollingType patrolling); 
};