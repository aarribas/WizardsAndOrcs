#include "EnemyFactory.h"
#include "EnemyPatrollingHorizontallyLogicCalculator.h"
#include "EnemyPatrollingVerticallyLogicCalculator.h"
#include "EnemyPatrollingStaticLogicCalculator.h"
#include "EnemyGruntView.h"
#include "EnemyPeonView.h"

EnemyController* EnemyFactory::create(LevelModel* levelModel, LevelView* levelView, int id,std::string name, const Vector4& position) 
{

	//depending on the name we create the right avatar type with the right logic
	if(name == "gruntH")
	{
		return createGrunt(levelModel, levelView, id,position,ENEMY_PATROLLING_HORIZONTAL );
	}
	else if (name == "gruntV")
	{
		return	createGrunt(levelModel, levelView, id,position,ENEMY_PATROLLING_VERTICAL ) ;
	}
	else if( name == "gruntS")
	{
		return createGrunt(levelModel, levelView, id,position,ENEMY_PATROLLING_STATIC );
	}

	
	if(name == "peonH")
	{
		return createPeon(levelModel, levelView, id,position,ENEMY_PATROLLING_HORIZONTAL );
	}
	else if (name == "peonV")
	{
		return	createPeon(levelModel, levelView, id,position,ENEMY_PATROLLING_VERTICAL ) ;
	}
	else if( name == "peonS")
	{
		return createPeon(levelModel, levelView, id,position,ENEMY_PATROLLING_STATIC );
	}

	//if the name is not recognise we inform of the error and exit
	std::cerr<<"E: EnemyFactory failed. Enemy name not recognised:"<< name 
	<< " on position: " << position[0]<< " "<< position[1] <<std::endl;
	std::cin.ignore();
	exit(0);
	
}


EnemyController* EnemyFactory::createGrunt(LevelModel* levelModel, LevelView* levelView, int id, const Vector4& position, PatrollingType patrollingType) 
{
	EnemyController* enemyController = new EnemyController();

	//create a new player model in the appropriate position
	EnemyStaticModel* enemyStaticModel = new EnemyStaticModel();
	enemyStaticModel->setScreenPosition(position);
	levelModel->addEnemyModel(enemyStaticModel, id);
	
	//create a new player view
	EnemyGruntView* enemyStaticView = new EnemyGruntView();
	levelView->addEnemyView(enemyStaticView, id);
	
	if(patrollingType == ENEMY_PATROLLING_HORIZONTAL)
	{
		//create and initialize the logic calculator
		EnemyPatrollingHorizontallyLogicCalculator* enemyLogicCalculator = new EnemyPatrollingHorizontallyLogicCalculator();
		enemyLogicCalculator->init(levelModel, enemyStaticModel);
		
		//finally initialize the controller
		enemyController->init(levelModel, enemyStaticView,enemyLogicCalculator, id);
	}
	else if(patrollingType == ENEMY_PATROLLING_VERTICAL)
	{
		//create and initialize the logic calculator
		EnemyPatrollingVerticallyLogicCalculator* enemyLogicCalculator = new EnemyPatrollingVerticallyLogicCalculator();
		enemyLogicCalculator->init(levelModel, enemyStaticModel);
		
		//finally initialize the controller
		enemyController->init(levelModel, enemyStaticView,enemyLogicCalculator, id);
	}
	else
	{
		//create and initialize the logic calculator
		EnemyPatrollingStaticLogicCalculator* enemyLogicCalculator = new EnemyPatrollingStaticLogicCalculator();
		enemyLogicCalculator->init(levelModel, enemyStaticModel);
		
		//finally initialize the controller
		enemyController->init(levelModel, enemyStaticView,enemyLogicCalculator, id);
	}
	return enemyController;
}


EnemyController* EnemyFactory::createPeon(LevelModel* levelModel, LevelView* levelView, int id, const Vector4& position, PatrollingType patrollingType) 
{
	EnemyController* enemyController = new EnemyController();

	//create a new player model in the appropriate position
	EnemyStaticModel* enemyStaticModel = new EnemyStaticModel();
	enemyStaticModel->setScreenPosition(position);
	levelModel->addEnemyModel(enemyStaticModel, id);
	
	//create a new player view
	EnemyPeonView* enemyStaticView = new EnemyPeonView();
	levelView->addEnemyView(enemyStaticView, id);
	
	if(patrollingType == ENEMY_PATROLLING_HORIZONTAL)
	{
		//create and initialize the logic calculator
		EnemyPatrollingHorizontallyLogicCalculator* enemyLogicCalculator = new EnemyPatrollingHorizontallyLogicCalculator();
		enemyLogicCalculator->init(levelModel, enemyStaticModel);
		
		//finally initialize the controller
		enemyController->init(levelModel, enemyStaticView,enemyLogicCalculator, id);
	}
	else if(patrollingType == ENEMY_PATROLLING_VERTICAL)
	{
		//create and initialize the logic calculator
		EnemyPatrollingVerticallyLogicCalculator* enemyLogicCalculator = new EnemyPatrollingVerticallyLogicCalculator();
		enemyLogicCalculator->init(levelModel, enemyStaticModel);
		
		//finally initialize the controller
		enemyController->init(levelModel, enemyStaticView,enemyLogicCalculator, id);
	}
	else
	{
		//create and initialize the logic calculator
		EnemyPatrollingStaticLogicCalculator* enemyLogicCalculator = new EnemyPatrollingStaticLogicCalculator();
		enemyLogicCalculator->init(levelModel, enemyStaticModel);
		
		//finally initialize the controller
		enemyController->init(levelModel, enemyStaticView,enemyLogicCalculator, id);
	}
	return enemyController;
}



