#pragma once
#include "EnemyLogicCalculator.h"

class EnemyPatrollingHorizontallyLogicCalculator : public EnemyLogicCalculator
{
public:
	EnemyPatrollingHorizontallyLogicCalculator();
	~EnemyPatrollingHorizontallyLogicCalculator();
public:
	void computeLogic();
private:
	bool m_patrolling;
	float m_referencePosX;
	float m_referencePosY;
	bool m_movingRight;
	int m_attackCountDown;
	
};