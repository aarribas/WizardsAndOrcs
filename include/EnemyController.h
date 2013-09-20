#pragma once
#include "AvatarController.h"
#include "EnemyStaticModel.h"
#include "EnemyStaticView.h"
#include "AvatarLogicCalculator.h"
#include "LevelModel.h"

class EnemyController : public AvatarController
{
public:
	EnemyController();
	~EnemyController();

public:
	void init(LevelModel* levelModel, AvatarView* avatarView, AvatarLogicCalculator* avatarLogicCalculator,int key);
private:
	void startIdle();
	void startMove(AvatarModel::AvatarState);
	void startAttack(AvatarModel::AvatarState);
	void startDie();
};
