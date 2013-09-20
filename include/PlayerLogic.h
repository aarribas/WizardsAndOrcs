#pragma once

#include "AvatarLogic.h"

class PlayerLogic : 
public AvatarLogic
{
public:

	PlayerLogic();
	 virtual ~PlayerLogic();

public:
	void computeNextAction(const float elapsedTime, AvatarEntity* player, AvatarLogicInfo);
private:
	OIS::KeyCode keysLeftPlayer[8];
	OIS::KeyCode keysRightPlayer[8];
};
