#include "StaticObjectLogicCalculator.h"

StaticObjectLogicCalculator::StaticObjectLogicCalculator()
{
}

StaticObjectLogicCalculator::~StaticObjectLogicCalculator()
{
}

void StaticObjectLogicCalculator::init(LevelModel* levelModel, StaticObjectModel* staticObjectModel)
{
	m_staticObjectModel = staticObjectModel;
	m_levelModel = levelModel;
}

void StaticObjectLogicCalculator::computeLogic()
{
	if(collides(m_levelModel->getPlayerModel()->getRect()))
	{
		switch(m_staticObjectModel->getStaticObjectType()) {

		case StaticObjectModel::STATIC_OBJECT_TYPE_COINS:
			m_levelModel->getPlayerModel()->getInventory()->addCoins();
			m_staticObjectModel->setStaticObjectState(StaticObjectModel::STATIC_OBJECT_COLLECTED);
			break;
		case StaticObjectModel::STATIC_OBJECT_TYPE_GEM:
			m_levelModel->getPlayerModel()->getInventory()->addGems();
			m_staticObjectModel->setStaticObjectState(StaticObjectModel::STATIC_OBJECT_COLLECTED);
			break;
		case StaticObjectModel::STATIC_OBJECT_TYPE_SHIELD:
			m_levelModel->getPlayerModel()->getInventory()->addProtection();
			m_staticObjectModel->setStaticObjectState(StaticObjectModel::STATIC_OBJECT_COLLECTED);
			
			break;
		case StaticObjectModel::STATIC_OBJECT_TYPE_LIFE_POTION:
			//define somewhere this increment of 10 life points TO_DO
				m_levelModel->getPlayerModel()->getInventory()->addPotions();
			m_staticObjectModel->setStaticObjectState(StaticObjectModel::STATIC_OBJECT_COLLECTED);
			break;
		case StaticObjectModel::STATIC_OBJECT_TYPE_BOOTS:
			m_levelModel->getPlayerModel()->getInventory()->addBoots();
			m_staticObjectModel->setStaticObjectState(StaticObjectModel::STATIC_OBJECT_COLLECTED);break;
		default:
			//nothing to do
			break;
		}
	}
}


bool StaticObjectLogicCalculator::collides(const AvatarModel::Rect& rect)
{
	return (((m_staticObjectModel->getRect().left>=rect.left) && (m_staticObjectModel->getRect().left<=rect.right) && (m_staticObjectModel->getRect().bottom<=rect.bottom) && (m_staticObjectModel->getRect().top>=rect.bottom)) ||
		((m_staticObjectModel->getRect().left<=rect.left) && (m_staticObjectModel->getRect().right>=rect.left) && (m_staticObjectModel->getRect().bottom<=rect.bottom) && (m_staticObjectModel->getRect().top>=rect.bottom)) ||
		((m_staticObjectModel->getRect().left>=rect.left) && (m_staticObjectModel->getRect().left<=rect.right) && (m_staticObjectModel->getRect().bottom>=rect.bottom) && (m_staticObjectModel->getRect().bottom<=rect.top))||
		((m_staticObjectModel->getRect().left<=rect.left) && (m_staticObjectModel->getRect().right>=rect.left) && (m_staticObjectModel->getRect().bottom>=rect.bottom) && (m_staticObjectModel->getRect().bottom<=rect.top)) );

}

