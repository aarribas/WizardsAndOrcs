#pragma once
#include "EnemyLogicCalculator.h"

class EnemyPatrollingVerticallyLogicCalculator : public EnemyLogicCalculator
{
public:
	EnemyPatrollingVerticallyLogicCalculator();
	~EnemyPatrollingVerticallyLogicCalculator();
public:
	void computeLogic();
private:
	bool m_patrolling;
	float m_referencePosX;
	float m_referencePosY;
	bool m_movingUp;
	int m_attackCountDown;
	
};