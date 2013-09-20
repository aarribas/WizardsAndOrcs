#include "StaticObjectController.h"

StaticObjectController::StaticObjectController()
{
}
StaticObjectController::~StaticObjectController()
{
}


void StaticObjectController::init(LevelModel* levelModel, StaticObjectView* staticObjectView, StaticObjectLogicCalculator* staticObjectLogicCalculator, int key)
{
	m_staticObjectModel = levelModel->getStaticObjectModel(key);
	m_staticObjectLogicCalculator = staticObjectLogicCalculator; 
	m_staticObjectView = staticObjectView;
	m_staticObjectView->initView(m_staticObjectModel);

}
void StaticObjectController::update(const float elapsedTime)
{
	updateBasicObjectMeasurements();
	m_staticObjectLogicCalculator->computeLogic();
}

void StaticObjectController::updateBasicObjectMeasurements()
{
	//set rect
	float pixelWidth = m_staticObjectView->getPixelWidth();
	float pixelHeight = m_staticObjectView->getPixelHeight();
	StaticObjectModel::Rect rect;
	rect.top = m_staticObjectModel->getTerrainPosition()[1] + pixelHeight/PIXELS_PER_METER/2.0f;
	rect.bottom = m_staticObjectModel->getTerrainPosition()[1] - pixelHeight/PIXELS_PER_METER/2.0f;
	rect.left =m_staticObjectModel->getTerrainPosition()[0] - pixelWidth /PIXELS_PER_METER/2.0f ;
	rect.right = m_staticObjectModel->getTerrainPosition()[0] + pixelWidth /PIXELS_PER_METER/2.0f;
	
	m_staticObjectModel->setRect(rect);
	m_staticObjectModel->setPixelWidth(pixelWidth);
	m_staticObjectModel->setPixelHeight(pixelHeight);

}