#pragma once
#include "StaticObjectModel.h"
#include "StaticObjectView.h"
#include "StaticObjectLogicCalculator.h"

class StaticObjectController
{
public:
	StaticObjectController();
	virtual ~StaticObjectController();
public:
	virtual void init(LevelModel* levelModel, StaticObjectView* staticObjectView, StaticObjectLogicCalculator* staticObjectLogicCalculator, int key);
		//the implementation of the update public and private methods is given and inherited
	virtual void update(const float elapsedTime);
private:
	virtual void updateBasicObjectMeasurements();
protected:
	StaticObjectModel* m_staticObjectModel;
	StaticObjectView* m_staticObjectView;
	StaticObjectLogicCalculator* m_staticObjectLogicCalculator;

};