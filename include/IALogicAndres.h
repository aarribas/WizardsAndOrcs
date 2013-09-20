#pragma once
#include "InterfaceIA.h"
#include "InterfaceLogicInfo.h"
#include "Core.h"

class IALogicAndres : public InterfaceIA
{	
public:
	IALogicAndres();
	virtual ~IALogicAndres();

	void Init(int PlayerId, bool CommonMovesOnly, int Difficulty, const Vector4 &Position, InterfaceLogicInfo* LogicInfo); 

	void Update(float timeElapsed);

	const Vector4 &GetPosition();
	void SetPosition(const Vector4& position);
private:
	void adaptDefensivenessToRoundTime();
	void adaptDefensivenessToPlayersLife();
	bool moveCloserToEnemyWhenRequired();
	void computeNextActions(float timeElapsed);
	void computeRandomActions_full();
	void computeRandomActions_commonOnly();

private:
	Vector4 m_position;
	int m_difficulty, m_playerId, m_enemyId;
	int m_commonMovesOnly;
	InterfaceLogicInfo* m_logicInfo;
	static int m_commonThresholds[4][4];
	static int m_fullThresholds[4][7];
	float m_timeout;
	bool m_approach;
	int m_currentRound;
	int m_defensiveness;
	float m_previous_player_life;
	
	
};