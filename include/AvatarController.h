#pragma once
#include "AvatarModel.h"
#include "AvatarView.h"
#include "AvatarLogicCalculator.h"

class AvatarController
{
public:
	AvatarController();
	virtual ~AvatarController();
public:
	//the implementation of the update public and private methods is given and inherited
	virtual void update(const float elapsedTime);
protected:
	virtual void updateBasicAvatarMeasurements();
private:
	virtual void updateState();
	virtual void updateIdle(const float elapsedTime);
	virtual void updateMove(const float elapsedTime);
	virtual void updateAttack(const float elapsedTime);
	virtual void updateDie(const float elapsedTime);

	//start to be given (requires sound management)
	virtual void startIdle()= 0;
	virtual void startMove(AvatarModel::AvatarState)= 0;
	virtual void startAttack(AvatarModel::AvatarState)= 0;
	virtual void startDie()= 0;
protected:
	AvatarModel* m_avatarModel;
	AvatarView* m_avatarView;
	AvatarLogicCalculator* m_avatarLogicCalculator;

};