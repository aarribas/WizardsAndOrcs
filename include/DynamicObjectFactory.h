#pragma once
#include "DynamicObjectController.h"
#include "DynamicObjectModel.h"
#include "DynamicObjectLogicCalculator.h"
#include "DynamicObjectView.h"
#include "Vector4.h"
#include "LevelModel.h"
#include "LevelView.h"

class DynamicObjectFactory
{
public:
	static DynamicObjectController* create(LevelModel* levelModel,LevelView* levelView,int id); 
};