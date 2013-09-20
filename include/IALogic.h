#pragma once
#include "AvatarLogic.h"
#include "Core.h"

class IALogic : public AvatarLogic
{
public:

	IALogic();
	 virtual ~IALogic();

public:
	virtual void computeNextAction(const float elapsedTime, AvatarEntity* ,AvatarLogicInfo );
private:
	int m_commonThresholds[4][4];
	float m_timeout;
	ActionManager::actions m_last_actions;
	bool m_approach;
};
