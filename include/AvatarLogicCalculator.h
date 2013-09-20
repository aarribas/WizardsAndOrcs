#pragma once
#include "AvatarModel.h"
#include "LevelModel.h"


class AvatarLogicCalculator
{
public:
	AvatarLogicCalculator();
	virtual ~AvatarLogicCalculator();
public:
	virtual void init(LevelModel* levelModel, AvatarModel* avatarModel) = 0;
	virtual void computeLogic() = 0;
	virtual bool collides(const AvatarModel::Rect &rect);
	virtual void computeAndSetDirection(float, float);
	virtual std::pair<float,float> computeDirection(float, float);
	virtual void setAttackAction();
	virtual void setMoveAction();
	virtual void correctStepsDueToWallCollisions();
	virtual bool collidesOnRight();
	virtual bool collidesOnLeft();
	virtual bool collidesOnCeiling();
	virtual bool collidesOnFloor();
protected:
	AvatarModel* m_avatarModel;
	LevelModel* m_levelModel;
};