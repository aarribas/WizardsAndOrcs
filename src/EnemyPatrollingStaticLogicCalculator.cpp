#include "EnemyPatrollingStaticLogicCalculator.h"

EnemyPatrollingStaticLogicCalculator::EnemyPatrollingStaticLogicCalculator():
m_attackCountDown(10)
{
}
EnemyPatrollingStaticLogicCalculator::~EnemyPatrollingStaticLogicCalculator()
{
}

void EnemyPatrollingStaticLogicCalculator::computeLogic()
{
		
	//check if dead - if so do not go any further
	if(m_avatarModel->getLifePoints()<0)
	{
		m_avatarModel->setAction(AvatarModel::AVATAR_ACTION_DIE);
		return;
	}

	//otherwise normal behaviour applies
	if(!collides(m_levelModel->getPlayerModel()->getRect()))
	{
		m_attackCountDown = 10;
		//not colliding therefore apply default logic

		if(isPlayerCloseAndVisible())
		{
			//move towards player
			computeAndSetDirection(m_levelModel->getPlayerModel()->getTerrainPosition()[0],m_levelModel->getPlayerModel()->getTerrainPosition()[1]);
			setMoveAction();

		}
		else
		{
			//do nothing

			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_IDLE);
		}
	}
	else
	{
		if(m_attackCountDown >0) 
		{
				m_attackCountDown--;
		}
		else
		{
			//we are colliding hence orient towards player and attack
			computeAndSetDirection(m_levelModel->getPlayerModel()->getTerrainPosition()[0],m_levelModel->getPlayerModel()->getTerrainPosition()[1]);
			setAttackAction();
		}
	}

	correctStepsDueToWallCollisions();
}
