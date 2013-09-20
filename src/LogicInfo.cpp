#include "LogicInfo.h"

LogicInfo::LogicInfo()
{

}

LogicInfo::~LogicInfo()
{
}

void LogicInfo::Init(bool CommonMovesOnly)
{
	m_commonMovesOnly = CommonMovesOnly;
}

const Vector4& LogicInfo::GetPosition(int PlayerId)
{
	return m_avatarPosition[PlayerId];
}

void LogicInfo::SetPosition(int PlayerId, const Vector4& Position)
{
	m_avatarPosition[PlayerId] = Position;
}

float LogicInfo::GetPlayerLife(int PlayerId)
{
	return m_avatarLife[PlayerId];
}

void LogicInfo::SetPlayerLife(int PlayerId, float PlayerLife)
{
	m_avatarLife[PlayerId] = PlayerLife;
}

int LogicInfo::GetRound()
{
	return m_round;
}

void LogicInfo::SetRound(int Round)
{
	m_round = Round;
}


float LogicInfo::GetRoundTime()
{
	return m_roundTime;
}

void LogicInfo::SetRoundTime(float RoundTime)
{
	m_roundTime  = RoundTime;
}

LogicInfo::State LogicInfo::GetPlayerState(int PlayerId)
{
	return m_avatarState[PlayerId];
}

void LogicInfo::SetPlayerState(int PlayerId, State PlayerState)
{
	m_avatarState[PlayerId] = PlayerState;

}

bool LogicInfo::GetCollision()
{
	return m_collision;
}

void LogicInfo::SetCollision(bool Collides)
{
	m_collision = Collides;
}

float LogicInfo::GetDistanceBetweenPlayers()
{
	return m_distanceBetweenPlayers;
}

void LogicInfo::SetDistanceBetweenPlayers(float Distance)
{
	m_distanceBetweenPlayers = Distance;
}

void LogicInfo::SetMaxXPos(float MaxXPos)
{
	m_maxPos = MaxXPos;
}
float LogicInfo::GetMaxXPos()
{
	return m_maxPos;
}
		
void LogicInfo::SetMinXPos(float MinXPos)
{
	m_minPos = MinXPos;
}
float LogicInfo::GetMinXPos()
{
	return m_minPos;
}