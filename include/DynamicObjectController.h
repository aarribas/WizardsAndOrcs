#pragma once
#include "DynamicObjectModel.h"
#include "DynamicObjectView.h"
#include "DynamicObjectLogicCalculator.h"

class DynamicObjectController
{
public:
	DynamicObjectController();
	virtual ~DynamicObjectController();
public:
	//the implementation of the update public and private methods is given and inherited
	virtual void update(const float elapsedTime);
protected:
	virtual void updateBasicDynamicObjectMeasurements();
private:
	virtual void updateState();
	virtual void updateMove(const float elapsedTime);
	virtual void updateImpact(const float elapsedTime);
	virtual void updateVanish(const float elapsedTime);

	//start to be given (requires sound management)
	virtual void startMove(DynamicObjectModel::DynamicObjectState)= 0;
	virtual void startImpact()= 0;
	virtual void startVanish()= 0;

protected:
	DynamicObjectModel* m_dynamicObjectModel;
	DynamicObjectView* m_dynamicObjectView;
	DynamicObjectLogicCalculator* m_dynamicObjectLogicCalculator;

};