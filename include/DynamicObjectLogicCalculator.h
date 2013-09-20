#pragma once
#include "DynamicObjectModel.h"
#include "LevelModel.h"


class DynamicObjectLogicCalculator
{
public:
	DynamicObjectLogicCalculator();
	virtual ~DynamicObjectLogicCalculator();
public:
	virtual void init(LevelModel* levelModel, DynamicObjectModel* DynamicObjectModel) = 0;
	virtual void computeLogic()= 0;
	virtual bool collides(const AvatarModel::Rect &rect);
	virtual void computeAndSetDirection(float, float);
	virtual std::pair<float,float> computeDirection(float, float);
	virtual void setMoveAction();
	virtual void correctStepsDueToWallCollisions();
	virtual bool collidesOnRight();
	virtual bool collidesOnLeft();
	virtual bool collidesOnCeiling();
	virtual bool collidesOnFloor();
protected:
	DynamicObjectModel* m_dynamicObjectModel;
	LevelModel* m_levelModel;
};