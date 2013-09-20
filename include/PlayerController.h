#pragma once
#include "AvatarController.h"
#include "PlayerModel.h"
#include "PlayerView.h"
#include "PlayerLogicCalculator.h"
#include "LevelModel.h"

class PlayerController : public AvatarController
{

public:
	PlayerController();
	~PlayerController();

public:
	void init(LevelModel* levelModel, AvatarView* playerView);
private:
	void startIdle();
	void startMove(AvatarModel::AvatarState);
	void startAttack(AvatarModel::AvatarState);
	void startDie();
};
