#include "DynamicObjectMagicRayController.h"

DynamicObjectMagicRayController::DynamicObjectMagicRayController()
{
}

DynamicObjectMagicRayController::~DynamicObjectMagicRayController()
{
}

void DynamicObjectMagicRayController::init(LevelModel* levelModel, DynamicObjectView* dynamicObjectView, DynamicObjectLogicCalculator* dynamicObjectLogicCalculator, int key)
{

	m_dynamicObjectModel = levelModel->getDynamicObjectModel(key);
	m_dynamicObjectLogicCalculator = dynamicObjectLogicCalculator; 
	m_dynamicObjectView = dynamicObjectView;
	m_dynamicObjectView->initView(m_dynamicObjectModel);
	updateBasicDynamicObjectMeasurements();
}
void DynamicObjectMagicRayController::startVanish()
{
	m_dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHING);
	m_dynamicObjectModel->setTimeout(DynamicObjectMagicRayModel::VANISH_TIMEOUT);
	m_dynamicObjectView->prepareNewAnim();
}

void DynamicObjectMagicRayController::startMove(DynamicObjectModel::DynamicObjectState state)
{
	m_dynamicObjectModel->setState(state);
	m_dynamicObjectModel->setTimeout(DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	m_dynamicObjectView->prepareNewAnim();
}

void DynamicObjectMagicRayController::startImpact()
{
	m_dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_IMPACTING);
	m_dynamicObjectModel->setTimeout(DynamicObjectMagicRayModel::IMPACT_TIMEOUT);
	m_dynamicObjectView->prepareNewAnim();
}