#include "StaticObjectFactory.h"
#include "StaticObjectShieldView.h"
#include "StaticObjectCoinsView.h"
#include "StaticObjectPotionView.h"
#include "StaticObjectBootsView.h"
#include "StaticObjectGemView.h"
#include "StaticObjectLogicCalculator.h"

StaticObjectController* StaticObjectFactory::create(LevelModel* levelModel,LevelView* levelView,int id,std::string name, const Vector4& position)
{
	StaticObjectController* staticObjectController = new StaticObjectController();
	

	if(name == "shield")
	{
		
		//create a new player model in the appropriate position
		StaticObjectModel* staticObjectModel = new StaticObjectModel(StaticObjectModel::STATIC_OBJECT_TYPE_SHIELD);
		staticObjectModel->setScreenPosition(position);
		levelModel->addStaticObjectModel(staticObjectModel, id);
		
		//create and initialize the logic calculator
		StaticObjectLogicCalculator* staticObjectLogicCalculator = new StaticObjectLogicCalculator();
		staticObjectLogicCalculator->init(levelModel, staticObjectModel);
	
		StaticObjectShieldView* staticObjectView = new StaticObjectShieldView();
		staticObjectView->initView(staticObjectModel);
		levelView->addStaticObjectView(staticObjectView, id);
		
		//finally initialize the controller
		staticObjectController->init(levelModel, staticObjectView,staticObjectLogicCalculator, id);
	
	}
	else if(name == "potion")
	{
			//create a new player model in the appropriate position
		StaticObjectModel* staticObjectModel = new StaticObjectModel(StaticObjectModel::STATIC_OBJECT_TYPE_LIFE_POTION);
		staticObjectModel->setScreenPosition(position);
		levelModel->addStaticObjectModel(staticObjectModel, id);
		
		//create and initialize the logic calculator
		StaticObjectLogicCalculator* staticObjectLogicCalculator = new StaticObjectLogicCalculator();
		staticObjectLogicCalculator->init(levelModel, staticObjectModel);
	
	
		StaticObjectPotionView* staticObjectView = new StaticObjectPotionView();
		staticObjectView->initView(staticObjectModel);
		levelView->addStaticObjectView(staticObjectView, id);
		
		//finally initialize the controller
		staticObjectController->init(levelModel, staticObjectView,staticObjectLogicCalculator, id);
	}
	else if(name == "coins")
	{
			//create a new player model in the appropriate position
		StaticObjectModel* staticObjectModel = new StaticObjectModel(StaticObjectModel::STATIC_OBJECT_TYPE_COINS);
		staticObjectModel->setScreenPosition(position);
		levelModel->addStaticObjectModel(staticObjectModel, id);
		
		//create and initialize the logic calculator
		StaticObjectLogicCalculator* staticObjectLogicCalculator = new StaticObjectLogicCalculator();
		staticObjectLogicCalculator->init(levelModel, staticObjectModel);
	

		StaticObjectCoinsView* staticObjectView = new StaticObjectCoinsView();
		staticObjectView->initView(staticObjectModel);
		levelView->addStaticObjectView(staticObjectView, id);
		
		//finally initialize the controller
		staticObjectController->init(levelModel, staticObjectView,staticObjectLogicCalculator, id);
	}
	else if(name == "gem")
	{
			//create a new player model in the appropriate position
		StaticObjectModel* staticObjectModel = new StaticObjectModel(StaticObjectModel::STATIC_OBJECT_TYPE_GEM);
		staticObjectModel->setScreenPosition(position);
		levelModel->addStaticObjectModel(staticObjectModel, id);
		
		//create and initialize the logic calculator
		StaticObjectLogicCalculator* staticObjectLogicCalculator = new StaticObjectLogicCalculator();
		staticObjectLogicCalculator->init(levelModel, staticObjectModel);
	

		StaticObjectGemView* staticObjectView = new StaticObjectGemView();
		staticObjectView->initView(staticObjectModel);
		levelView->addStaticObjectView(staticObjectView, id);
		
		//finally initialize the controller
		staticObjectController->init(levelModel, staticObjectView,staticObjectLogicCalculator, id);
	}
		else if(name == "boots")
	{
			//create a new player model in the appropriate position
		StaticObjectModel* staticObjectModel = new StaticObjectModel(StaticObjectModel::STATIC_OBJECT_TYPE_BOOTS);
		staticObjectModel->setScreenPosition(position);
		levelModel->addStaticObjectModel(staticObjectModel, id);
		
		//create and initialize the logic calculator
		StaticObjectLogicCalculator* staticObjectLogicCalculator = new StaticObjectLogicCalculator();
		staticObjectLogicCalculator->init(levelModel, staticObjectModel);
	

		StaticObjectBootsView* staticObjectView = new StaticObjectBootsView();
		staticObjectView->initView(staticObjectModel);
		levelView->addStaticObjectView(staticObjectView, id);
		
		//finally initialize the controller
		staticObjectController->init(levelModel, staticObjectView,staticObjectLogicCalculator, id);
	}

	//buildings to be added TO_DO

	return staticObjectController;
}