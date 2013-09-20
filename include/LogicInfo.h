#pragma once

#include "InterfaceLogicInfo.h"

class LogicInfo : public InterfaceLogicInfo
{
public:
	LogicInfo();
	 virtual ~LogicInfo();
	void Init(bool CommonMovesOnly);

	const Vector4& GetPosition(int PlayerId);
	void SetPosition(int PlayerId, const Vector4& Position);

	float GetPlayerLife(int PlayerId);
	void SetPlayerLife(int PlayerId, float PlayerLife);

	int GetRound(); //Round 0, 1 o 2
	void SetRound(int Round);

	float GetRoundTime();
	void SetRoundTime(float RoundTime);

	State GetPlayerState(int PlayerId);
	void SetPlayerState(int PlayerId, State PlayerState);

	bool GetCollision();
	virtual void SetCollision(bool Collides);

	float GetDistanceBetweenPlayers(); 
	void SetDistanceBetweenPlayers(float Distance);

	void SetMaxXPos(float MaxXPos);
	float GetMaxXPos();

	void SetMinXPos(float MinXPos);
	float GetMinXPos();

private:

	float m_maxPos, m_minPos;
	float m_distanceBetweenPlayers;
	bool m_collision;
	float  m_roundTime;
	int m_round;
	float m_avatarLife[2];
	Vector4 m_avatarPosition[2];
	State  m_avatarState[2];
	bool m_commonMovesOnly;
};