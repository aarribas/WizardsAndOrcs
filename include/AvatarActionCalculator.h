#pragma once
#include "AvatarModel.h"
class AvatarActionCalculator
{
public:
	virtual void computeNextAction(AvatarModel* avatarModel)=0;
};