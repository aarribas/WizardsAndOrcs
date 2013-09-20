#include "DynamicObjectController.h"


DynamicObjectController::DynamicObjectController()
{
}

DynamicObjectController::~DynamicObjectController()
{

}

void DynamicObjectController::update(const float elapsedTime)
{
	m_dynamicObjectLogicCalculator->computeLogic();

	updateState();

	switch(m_dynamicObjectModel->getState()) {

		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP:
			updateMove(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN:
			updateMove(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT:
			updateMove(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT:
			updateMove(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT:
			updateMove(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT:
			updateMove(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_LEFT:
			updateMove(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_RIGHT:
			updateMove(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHING:
			updateVanish(elapsedTime);
			break;
		case DynamicObjectModel::DYNAMIC_OBJECT_STATE_IMPACTING:
			updateVanish(elapsedTime);
			break;
		default:
			//nothing 
			break;
	}
	updateBasicDynamicObjectMeasurements();
}

void DynamicObjectController::updateState()
{
	DynamicObjectModel::DynamicObjectAction action = m_dynamicObjectModel->getAction();
	
	if (action == DynamicObjectModel::DYNAMIC_OBJECT_ACTION_IDLE )
	{
		//nothing to do
	}
	else
	{
		if(action ==  DynamicObjectModel::DYNAMIC_OBJECT_ACTION_VANISH
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHING)
		{
			startVanish();
		}

		if(action ==  DynamicObjectModel::DYNAMIC_OBJECT_ACTION_IMPACT
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_IMPACTING)
		{
			startImpact();
		}

		if(action == DynamicObjectModel::DynamicObjectAction::DYNAMIC_OBJECT_ACTION_MOVE_UP 
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP)
		{
			startMove(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP);
		
		}
		if(action == DynamicObjectModel::DynamicObjectAction::DYNAMIC_OBJECT_ACTION_MOVE_DOWN 
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN)
		{
			startMove(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN);
		}
		if(action == DynamicObjectModel::DynamicObjectAction::DYNAMIC_OBJECT_ACTION_MOVE_LEFT 
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_LEFT)
		{
			startMove(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_LEFT);
		}
		if(action == DynamicObjectModel::DynamicObjectAction::DYNAMIC_OBJECT_ACTION_MOVE_RIGHT 
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_RIGHT)
		{
			startMove(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_RIGHT);
		}
		if(action == DynamicObjectModel::DynamicObjectAction::DYNAMIC_OBJECT_ACTION_MOVE_UP_LEFT 
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT)
		{
			startMove(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT);
		}
		if(action == DynamicObjectModel::DynamicObjectAction::DYNAMIC_OBJECT_ACTION_MOVE_UP_RIGHT 
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT)
		{
			startMove(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT);
		}
		if(action == DynamicObjectModel::DynamicObjectAction::DYNAMIC_OBJECT_ACTION_MOVE_DOWN_LEFT 
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT)
		{
			startMove(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT);
		}
		if(action == DynamicObjectModel::DynamicObjectAction::DYNAMIC_OBJECT_ACTION_MOVE_DOWN_RIGHT 
			&& m_dynamicObjectModel->getState()!= DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT)
		{
			startMove(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT);
		}
	}
}


void DynamicObjectController::updateVanish(const float elapsedTime)
{
	float timeout = m_dynamicObjectModel->getTimeout();
	timeout-=elapsedTime;
	m_dynamicObjectModel->setTimeout(timeout);
	
	if(timeout > 0)
	{
		m_dynamicObjectView->setNextAnim(); 
	}
	else
	{
		//once it is done vanishing it just moves to vanished. Normally it will be cleaned up.
		m_dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHED);

	}
}

void DynamicObjectController::updateMove(const float elapsedTime)
{
	float timeout = m_dynamicObjectModel->getTimeout();
	timeout-=elapsedTime;
	m_dynamicObjectModel->setTimeout(timeout);

	float stepX,stepY;
	Vector4 terrainPosition =  m_dynamicObjectModel->getTerrainPosition();
	m_dynamicObjectModel->getStep(&stepX,&stepY);
	terrainPosition[0]+= stepX*m_dynamicObjectModel->getCelerity()*elapsedTime;
	terrainPosition[1]+= stepY*m_dynamicObjectModel->getCelerity()*elapsedTime;

	if(timeout > 0)
	{

		m_dynamicObjectModel->setTerrainPosition(terrainPosition);
		m_dynamicObjectView->setNextAnim(); 
	}
	else
	{
		//keep moving
		startMove(m_dynamicObjectModel->getState());
	}
}

void DynamicObjectController::updateImpact(const float elapsedTime)
{
	float timeout = m_dynamicObjectModel->getTimeout();
	timeout-=elapsedTime;
	m_dynamicObjectModel->setTimeout(timeout);
	
	if(timeout > 0)
	{
		m_dynamicObjectView->setNextAnim(); 
	}
	else
	{
		//keep impacting
		startVanish();
	}
}

void DynamicObjectController::updateBasicDynamicObjectMeasurements()
{
	//set rect
	float pixelWidth = m_dynamicObjectView->getPixelWidth();
	float pixelHeight = m_dynamicObjectView->getPixelHeight();
	DynamicObjectModel::Rect rect;
	rect.top = m_dynamicObjectModel->getTerrainPosition()[1] + pixelHeight/PIXELS_PER_METER/2.0f;
	rect.bottom = m_dynamicObjectModel->getTerrainPosition()[1] - pixelHeight/PIXELS_PER_METER/2.0f;
	rect.left = m_dynamicObjectModel->getTerrainPosition()[0] - pixelWidth /PIXELS_PER_METER/2.0f ;
	rect.right = m_dynamicObjectModel->getTerrainPosition()[0] + pixelWidth /PIXELS_PER_METER/2.0f;
	
	m_dynamicObjectModel->setRect(rect);
	m_dynamicObjectModel->setPixelWidth(pixelWidth);
	m_dynamicObjectModel->setPixelHeight(pixelHeight);

}

