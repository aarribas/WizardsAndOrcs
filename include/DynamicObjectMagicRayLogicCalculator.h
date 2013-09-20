#pragma once
#include "DynamicObjectLogicCalculator.h"

class DynamicObjectMagicRayLogicCalculator:public DynamicObjectLogicCalculator
{
	public:
	virtual void init(LevelModel* levelModel, DynamicObjectModel* dynamicObjectModel);
	virtual void computeLogic();
private:
	bool checkIfMagicRayCollidesWithWalls();
	bool checkIfMagicRayCollidesWithEnemiesAndUpdateEnemies();
	bool rayHasTravelledTooFar();
private:
	Vector4 m_referencePosition;
};