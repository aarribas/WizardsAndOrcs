#pragma once
#include "AvatarModel.h"

class EnemyStaticModel: public AvatarModel
{
public:
	static const float CELERITY;
	static const float MOVE_TIMEOUT;
	static const float ATTACK_TIMEOUT;
	static const float DIE_TIMEOUT;
	static const float IDLE_TIMEOUT;

public:
	float getCelerity(){return CELERITY;}
};