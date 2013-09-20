#pragma once
#include "AvatarModel.h"
#include "PlayerModelInventory.h"

class PlayerModel:public AvatarModel
{

public:
//speed
	static const float CELERITY;
	static const float MOVE_TIMEOUT;
	static const float ATTACK_TIMEOUT;
	static const float DIE_TIMEOUT;
	static const float IDLE_TIMEOUT;
public:
	PlayerModelInventory* getInventory(){return &m_inventory;}
	float getCelerity(){return CELERITY;}

public:
	PlayerModelInventory m_inventory;
};