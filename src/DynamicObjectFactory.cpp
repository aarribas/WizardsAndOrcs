#include "DynamicObjectFactory.h"
#include "DynamicObjectMagicRayModel.h"
#include "DynamicObjectMagicRayView.h"
#include "DynamicObjectMagicRayLogicCalculator.h"
#include "DynamicObjectMagicRayController.h"

//08/09/12the creation is simplistic at the moment because I only create magic rays. More magic TO_DO
DynamicObjectController* DynamicObjectFactory::create(LevelModel* levelModel, LevelView* levelView, int id) 
{

	DynamicObjectMagicRayController* dynamicObjectController = new DynamicObjectMagicRayController();

	//create a new magic ray model
	DynamicObjectMagicRayModel* dynamicObjectModel = new DynamicObjectMagicRayModel();
	
	//initialise position to the position of the player.
	dynamicObjectModel->setTerrainPosition(levelModel->getPlayerModel()->getTerrainPosition());

	//set damage points TO_DO define this somewhere else depending on type of ray.
	dynamicObjectModel->setDamagePoints(15);
	
	//adjust direction of the ray to the direction the player is heading to
	float stepX,stepY;

	levelModel->getPlayerModel()->getStep(&stepX,&stepY);
	//if the player is not steady then in case a step is 0 we assume he is colliding in that direction
	//and we still shoot
	if(!(stepX == 0 && stepY ==0))
	{
		if(stepX == 0) stepX = 1;
		if(stepY == 0) stepX = 1;
	}
	dynamicObjectModel->setStep(stepX,stepY);

	//adjust the state to the 

	switch(levelModel->getPlayerModel()->getState())
	{
		case PlayerModel::AVATAR_STATE_ATTACK_DOWN:
		dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN);
		break;
		case PlayerModel::AVATAR_STATE_ATTACK_UP:
		dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP);
		break;
		case PlayerModel::AVATAR_STATE_ATTACK_DOWN_LEFT:
		dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT);
		break;
		case PlayerModel::AVATAR_STATE_ATTACK_DOWN_RIGHT:
		dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT);
		break;
		case PlayerModel::AVATAR_STATE_ATTACK_UP_LEFT:
		dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT);
		break;
		case PlayerModel::AVATAR_STATE_ATTACK_UP_RIGHT:
		dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT);
		break;
		case PlayerModel::AVATAR_STATE_ATTACK_LEFT:
		dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_LEFT);
		break;
		case PlayerModel::AVATAR_STATE_ATTACK_RIGHT:
		dynamicObjectModel->setState(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_RIGHT);
		break;
	};

	levelModel->addDynamicObjectModel(dynamicObjectModel, id);
	
	//create a new player view
	DynamicObjectMagicRayView* dynamicObjectView = new DynamicObjectMagicRayView();
	levelView->addDynamicObjectView(dynamicObjectView, id);
	
	//create and initialize the logic calculator
	DynamicObjectMagicRayLogicCalculator* dynamicObjectLogicCalculator = new DynamicObjectMagicRayLogicCalculator();
	dynamicObjectLogicCalculator->init(levelModel, dynamicObjectModel);
		
	//finally initialize the controller
	dynamicObjectController->init(levelModel, dynamicObjectView, dynamicObjectLogicCalculator, id);

	return dynamicObjectController;
}
