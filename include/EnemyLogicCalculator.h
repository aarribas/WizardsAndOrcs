#pragma once
#include "AvatarModel.h"
#include "LevelModel.h"
#include "AvatarLogicCalculator.h"

class EnemyLogicCalculator : public AvatarLogicCalculator
{
public:
	EnemyLogicCalculator();
	virtual ~EnemyLogicCalculator();
public:
	virtual void init(LevelModel* levelModel, AvatarModel* avatarModel);
	virtual void computeLogic() = 0;
protected:
	virtual bool isPlayerVisible();
	virtual bool isPlayerCloseAndVisible();
private:
	bool m_collidingWithPlayer;
};