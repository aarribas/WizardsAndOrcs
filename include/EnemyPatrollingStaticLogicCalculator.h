#pragma once
#include "EnemyLogicCalculator.h"

class EnemyPatrollingStaticLogicCalculator : public EnemyLogicCalculator
{
public:
	EnemyPatrollingStaticLogicCalculator();
	~EnemyPatrollingStaticLogicCalculator();
public:
	void computeLogic();
	int m_attackCountDown;
};