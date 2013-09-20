#include "DynamicObjectMagicRayLogicCalculator.h"

void DynamicObjectMagicRayLogicCalculator::init(LevelModel* levelModel, DynamicObjectModel* dynamicObjectModel)
{
	m_dynamicObjectModel = dynamicObjectModel;
	m_levelModel = levelModel;
	m_referencePosition = Vector4(0,0,0);
}

void DynamicObjectMagicRayLogicCalculator::computeLogic()
{


	if(m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHING)
	{
		
		if(m_dynamicObjectModel->getState()== DynamicObjectModel::DYNAMIC_OBJECT_STATE_IMPACTING)
		{
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_IMPACT);
			return;
		}

		else if(rayHasTravelledTooFar())
		{	
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_VANISH);
			return;
		}
		else if(checkIfMagicRayCollidesWithWalls() || checkIfMagicRayCollidesWithEnemiesAndUpdateEnemies()) 
		{
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_IMPACT);
			return;
		}
		else
		{
			//nothing
		}

	}
}

bool  DynamicObjectMagicRayLogicCalculator::checkIfMagicRayCollidesWithWalls()
{
	return (collidesOnLeft() || collidesOnRight() || collidesOnCeiling() ||collidesOnFloor());
}

bool DynamicObjectMagicRayLogicCalculator::checkIfMagicRayCollidesWithEnemiesAndUpdateEnemies()
{
	bool isColliding = false;

	std::map<int, AvatarModel*>::iterator enemiesIt = m_levelModel->getEnemyModels().begin();

	while(enemiesIt != m_levelModel->getEnemyModels().end())
	{
		if(collides(enemiesIt->second->getRect()))
		{
			if(!isColliding) isColliding = true;
			
			enemiesIt->second->setLifePoints(enemiesIt->second->getLifePoints()- m_dynamicObjectModel->getDamagePoints());

		}
		enemiesIt++;
	}
	return isColliding;

}

bool DynamicObjectMagicRayLogicCalculator::rayHasTravelledTooFar()
{
	if(m_referencePosition[0] == 0 && m_referencePosition[1] == 0)
	{
		//we just started flying set current position as reference position
		m_referencePosition[0] = m_dynamicObjectModel->getTerrainPosition()[0];
		m_referencePosition[1] = m_dynamicObjectModel->getTerrainPosition()[1];
		return false;
	}
	else
	{
		//TO_DO define the distance of 40 somewhere
		return ( std::sqrtf( (m_referencePosition[0] - m_dynamicObjectModel->getTerrainPosition()[0]) *
			(m_referencePosition[0] - m_dynamicObjectModel->getTerrainPosition()[0])+
			(m_referencePosition[1] - m_dynamicObjectModel->getTerrainPosition()[1])*
			(m_referencePosition[1] - m_dynamicObjectModel->getTerrainPosition()[1])
			) > 40  );
	}
}