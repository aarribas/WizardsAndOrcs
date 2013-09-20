#pragma once 
#include "BBoxAtlas.h"
#include "AvatarEntity.h"
#include "LogicInfo.h"
#include "IALogicAndres.h"
#include "IADavid.h"

struct GameInfo
{
	float av1_hitPoints;
	float av2_hitPoints;
	unsigned char round;
	float timeleft;
	int av1_victories;
};


class LogicHelper
{
public:
	LogicHelper();
	~LogicHelper();
public:
	void init(AvatarEntity* avatar1, AvatarEntity* avatar2, BBoxAtlas* bboxAtlas, int difficulty, bool commonOnly, GameInfo* gameInfo);
	void updateAvatarLogic(const float elapsedTime);
private:
	void computeBBoxCollision();
	void computeHitPoints();
	void setPlayerState(AvatarEntity* avatar);
	void populateLogicInfo();
	void computeNextActions();
	void correctPositions();
private:
	IALogicAndres m_ia_logic_andres;
	IA m_ia_logic_david;
	LogicInfo m_logicInfo;
	bool m_collision;
	AvatarEntity* m_avatar1;
	AvatarEntity* m_avatar2;
	float m_elapsedTime;
	BBoxAtlas* m_bboxAtlas;
	GameInfo* m_gameInfo;
};