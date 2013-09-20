#pragma once
#include "StaticObjectController.h"
#include "StaticObjectModel.h"
#include "StaticObjectLogicCalculator.h"
#include "StaticObjectView.h"
#include "Vector4.h"
#include "LevelModel.h"
#include "LevelView.h"

class StaticObjectFactory
{
public:

	static StaticObjectController* create(LevelModel* levelModel,LevelView* levelView,int id,std::string name, const Vector4& position); 
};