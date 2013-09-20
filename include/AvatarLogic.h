#pragma once

#include "AvatarEntity.h"

struct AvatarLogicInfo
{
	AvatarEntity::State avatar1_state;
	AvatarEntity::State avatar2_state;
	float avatar1_hitPoints;
	float avatar2_hitPoints;
	bool avatar1_isOnLeft;
	bool colliding;
	float distance;
};

class AvatarLogic
{
public:
	
	AvatarLogic();
	 virtual ~AvatarLogic();
public:
	virtual void computeNextAction(const float elapsedTime, AvatarEntity* avatar ,AvatarLogicInfo avatarInfo);
};
