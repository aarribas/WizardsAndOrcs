#include "AvatarController.h"

AvatarController::AvatarController()
{
}

AvatarController::~AvatarController()
{

}

void AvatarController::update(const float elapsedTime)
{
	m_avatarLogicCalculator->computeLogic();

	updateState();

	switch(m_avatarModel->getState()) {

		case AvatarModel::AvatarState::AVATAR_STATE_IDLE:
			updateIdle(elapsedTime);
			break;

		case AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP:
			updateMove(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN:
			updateMove(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT:
			updateMove(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT:
			updateMove(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT:
			updateMove(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT:
			updateMove(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT:
			updateMove(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT:
			updateMove(elapsedTime);
			break;
		
		case AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP:
			updateAttack(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN:
			updateAttack(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT:
			updateAttack(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT:
			updateAttack(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT:
			updateAttack(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT:
			updateAttack(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT:
			updateAttack(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT:
			updateAttack(elapsedTime);
			break;
		case AvatarModel::AvatarState::AVATAR_STATE_DIE:
			updateDie(elapsedTime);
			break;
		
		default:
			updateIdle(elapsedTime);
			break;
	}
	updateBasicAvatarMeasurements();
}

void AvatarController::updateState()
{
	AvatarModel::AvatarAction action = m_avatarModel->getAction();
	
	if (action == AvatarModel::AvatarAction::AVATAR_ACTION_IDLE )
	{
		//nothing to do
	}
	else
	{
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_DIE 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_DIE)
		{
			startDie();
		}

		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_UP 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP)
		{
			startMove(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP);
		
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_DOWN 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN)
		{
			startMove(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_LEFT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT)
		{
			startMove(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_RIGHT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT)
		{
			startMove(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_UP_LEFT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT)
		{
			startMove(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_UP_RIGHT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT)
		{
			startMove(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_DOWN_LEFT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT)
		{
			startMove(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_DOWN_RIGHT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT)
		{
			startMove(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT);
		}
			if(action == AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_UP 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP)
		{
			startAttack(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_DOWN 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN)
		{
			startAttack(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_LEFT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT)
		{
			startAttack(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_RIGHT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT)
		{
			startAttack(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_UP_LEFT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT)
		{
			startAttack(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_UP_RIGHT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT)
		{
			startAttack(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_DOWN_LEFT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT)
		{
			startAttack(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT);
		}
		if(action == AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_DOWN_RIGHT 
			&& m_avatarModel->getState()!= AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT)
		{
			startAttack(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT);
		}
	}
}


void AvatarController::updateIdle(const float elapsedTime)
{
	//nothing to update
}

void AvatarController::updateDie(const float elapsedTime)
{
	float timeout = m_avatarModel->getTimeout();
	timeout-=elapsedTime;
	m_avatarModel->setTimeout(timeout);
	
	if(timeout > 0)
	{
		m_avatarView->setNextAnim(); 
	}
	else
	{
		
		m_avatarModel->setState(AvatarModel::AvatarState::AVATAR_STATE_DEAD);

	}
}

void AvatarController::updateMove(const float elapsedTime)
{
	float timeout = m_avatarModel->getTimeout();
	timeout-=elapsedTime;
	m_avatarModel->setTimeout(timeout);

	float stepX,stepY;
	Vector4 terrainPosition =  m_avatarModel->getTerrainPosition();
	m_avatarModel->getStep(&stepX,&stepY);
	terrainPosition[0]+= stepX*m_avatarModel->getCelerity()*elapsedTime;
	terrainPosition[1]+= stepY*m_avatarModel->getCelerity()*elapsedTime;

	if(timeout > 0)
	{

		m_avatarModel->setTerrainPosition(terrainPosition);
		m_avatarView->setNextAnim(); 
	}
	else
	{
		//go back to idle
		startIdle();

	}
}

void AvatarController::updateAttack(const float elapsedTime)
{
	float timeout = m_avatarModel->getTimeout();
	timeout-=elapsedTime;
	m_avatarModel->setTimeout(timeout);
	
	if(timeout > 0)
	{
		m_avatarView->setNextAnim(); 
	}
	else
	{
		//go back to idle
		startIdle();

	}
}

void AvatarController::updateBasicAvatarMeasurements()
{
	//set rect
	float pixelWidth = m_avatarView->getPixelWidth();
	float pixelHeight = m_avatarView->getPixelHeight();
	AvatarModel::Rect rect;
	rect.top = m_avatarModel->getTerrainPosition()[1] + pixelHeight/PIXELS_PER_METER/2.0f;
	rect.bottom = m_avatarModel->getTerrainPosition()[1] - pixelHeight/PIXELS_PER_METER/2.0f;
	rect.left = m_avatarModel->getTerrainPosition()[0] - pixelWidth /PIXELS_PER_METER/2.0f ;
	rect.right = m_avatarModel->getTerrainPosition()[0] + pixelWidth /PIXELS_PER_METER/2.0f;
	
	m_avatarModel->setRect(rect);
	m_avatarModel->setPixelWidth(pixelWidth);
	m_avatarModel->setPixelHeight(pixelHeight);

}