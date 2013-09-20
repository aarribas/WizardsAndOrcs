#include "EnemyPatrollingVerticallyLogicCalculator.h"

EnemyPatrollingVerticallyLogicCalculator::EnemyPatrollingVerticallyLogicCalculator():
m_patrolling(false),
m_movingUp(false),
m_attackCountDown(10)
{
}
EnemyPatrollingVerticallyLogicCalculator::~EnemyPatrollingVerticallyLogicCalculator()
{
}

void EnemyPatrollingVerticallyLogicCalculator::computeLogic()
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
			m_patrolling = false;
			computeAndSetDirection(m_levelModel->getPlayerModel()->getTerrainPosition()[0],m_levelModel->getPlayerModel()->getTerrainPosition()[1]);
			setMoveAction();

		}
		else
		{
			//do nothing
			if(m_patrolling == false)
			{
				m_patrolling = true;
				//set current position as reference
				m_referencePosX =  m_avatarModel->getTerrainPosition()[0];
				m_referencePosY =  m_avatarModel->getTerrainPosition()[1];

				//start patrolling in a random direction
				srand((int)this);
				int i = rand()%10;
				if(i<5)
				{
					m_movingUp = true;
					m_avatarModel->setStep(0,1);
				}
				else
				{
					m_movingUp = false;
					m_avatarModel->setStep(0,-1);
				}
				setMoveAction();
			}
			else
			{
				float stepX, stepY;
				m_avatarModel->getStep(&stepX,&stepY);
				
				//compute the distance to the reference position
				float distanceToReference = std::sqrtf(
		(m_referencePosX - m_avatarModel->getTerrainPosition()[0])*(m_referencePosX - m_avatarModel->getTerrainPosition()[0]) 
		+
		(m_referencePosY - m_avatarModel->getTerrainPosition()[1])*(m_referencePosY - m_avatarModel->getTerrainPosition()[1]) 
		);

				//in case we are far away from the reference position or we collided in the direction of movement 
				//invert the patrolling => start moving in the opposite direction
				
				if(distanceToReference >= 32 || stepY == 0)
				{
					if(m_movingUp)
					{
						m_movingUp = false;
						m_avatarModel->setStep(0,-1);
					}
					else
					{
						m_movingUp = true;
						m_avatarModel->setStep(0,1);
					}
					setMoveAction();
				}
				else
				{
					//otherwise keep moving in the same direction
					m_avatarModel->setStep(0,stepY);
					setMoveAction();
				}
			}

			//m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_IDLE);
		}
	}
	else
	{
		if(m_attackCountDown > 0) 
		{
				m_attackCountDown--;
		}
		else
		{
			//we are colliding hence orient towards player and attack
			m_patrolling = false;
			computeAndSetDirection(m_levelModel->getPlayerModel()->getTerrainPosition()[0],m_levelModel->getPlayerModel()->getTerrainPosition()[1]);
			setAttackAction();
		}
	}

	correctStepsDueToWallCollisions();
}
