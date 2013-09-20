
#pragma once
#include "DynamicObjectController.h"
#include "DynamicObjectMagicRayModel.h"
#include "DynamicObjectMagicRayView.h"
#include "DynamicObjectMagicRayLogicCalculator.h"
#include "LevelModel.h"

class DynamicObjectMagicRayController : public DynamicObjectController
{

public:
	DynamicObjectMagicRayController();
	~DynamicObjectMagicRayController();

public:
	void init(LevelModel* levelModel, DynamicObjectView* dynamicObjectView, DynamicObjectLogicCalculator* dynamicObjectLogicCalculator, int key);
private:
	//start to be given (requires sound management)
	void startMove(DynamicObjectModel::DynamicObjectState);
	void startImpact();
	void startVanish();
};

