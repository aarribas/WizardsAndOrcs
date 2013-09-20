#include "LevelController.h"
#include <iostream>
#include "Vector4.h"
#include "EnemyController.h"
#include "EnemyFactory.h"
#include "StaticObjectFactory.h"
#include "DynamicObjectFactory.h"
#include "gl/glut.h"
#include "Core.h"
//the following is not obtained from the map file, it is just hardcoded in the code but it is very important.
const float LevelController::m_TileSizeInMeters = 8;


LevelController::LevelController():
m_nextNewEnemyId(0),
m_nextNewStaticObjectId(0),
m_toggleTime(0)
{
}


LevelController::~LevelController()
{
	delete m_playerController;
	
	//clean up of static objects
	std::map<int, StaticObjectController* >::iterator staticObjectControllerIt = m_staticObjectControllers.begin();
	while(staticObjectControllerIt != m_staticObjectControllers.end())
	{
		delete staticObjectControllerIt->second;
		m_staticObjectControllers.erase(staticObjectControllerIt++);
	}

	//clean up of dynamic objects
	std::map<int, DynamicObjectController* >::iterator dynamicObjectControllerIt = m_dynamicObjectControllers.begin();
	while(dynamicObjectControllerIt != m_dynamicObjectControllers.end())
	{
		delete dynamicObjectControllerIt->second;
		m_dynamicObjectControllers.erase(dynamicObjectControllerIt++);
	}

	//clean up of enemies
	std::map<int, AvatarController*>::iterator enemyControllerIt = m_enemyControllers.begin();
	while(enemyControllerIt != m_enemyControllers.end())
	{
		delete enemyControllerIt->second;
		m_enemyControllers.erase(enemyControllerIt++);
	}
}


void LevelController::loadNewLevel(Tmx::Map* map)
{
	loadMap(map);
	m_levelView.init(m_levelModel);
	m_hudView.init(m_levelModel.getPlayerModel());



}

void LevelController::draw()
{
	m_levelView.draw();
	m_hudView.draw();
}

void LevelController::loadMap(Tmx::Map* map)
{
	//we expect only one tileset
	if(map->GetNumTilesets()>1)
	{
		std::cerr<<"More than one tileset in map."<<std::endl;
		std::cin.get();
		exit(-1);
	}

	//extract the Tileset
	const Tmx::Tileset *tileset = map->GetTileset(0);

	//Amongst the information we could extract from the tileset we do not we assume Margin 0, Spacing 0, 
	//and default transparent color. 
	//As a consequence we do not read these properties. 

	//Save width, height, tileWidth, tileHeight and name of the tileset
	m_levelModel.m_sourceTileSetInfo.width = (float)tileset->GetImage()->GetWidth();
	m_levelModel.m_sourceTileSetInfo.height = (float)tileset->GetImage()->GetHeight();

	m_levelModel.m_sourceTileSetInfo.tileWidth = (float)tileset->GetTileWidth();
	m_levelModel.m_sourceTileSetInfo.tileHeight = (float)tileset->GetTileHeight();

	m_levelModel.m_sourceTileSetInfo.name = tileset->GetName(); // name will be used to look up the texture


	//We look only for the solidity property per tile and save it as part of the tileset info
	m_levelModel.m_sourceTileSetInfo.solidity.clear();
	//for all tiles default solidity is 1
	m_levelModel.m_sourceTileSetInfo.solidity.assign((tileset->GetImage()->GetWidth()/tileset->GetTileWidth())*(tileset->GetImage()->GetHeight()/tileset->GetTileHeight()),0);

	std::vector< Tmx::Tile *>::const_iterator tileIt = tileset->GetTiles().begin();


	//if any tile is refered separately I assume it is so because it is solid and do not even read the properties
	//THIS IS A BIG SIMPLIFICATION
	while(tileIt != tileset->GetTiles().end())
	{
		const Tmx::Tile *tile = *(tileIt);

		//the value of 9 is chosen for compatibility with the A* code from Justin Heyes-Jones
		//should be defined somewhere as a static const TO_DO
		m_levelModel.m_sourceTileSetInfo.solidity[tile->GetId()] = 9;

		// Process the properties of a tile. = > NOT IMPLEMENTED
		//std::map< std::string, std::string > list = tile->GetProperties().GetList();

		tileIt++;
	}

	// Iterate through the layers and save the basic tile info
	m_levelModel.sceneLayers.clear();

	for (int i = 0; i < map->GetNumLayers(); ++i) {
		//I do not extract the layer name
		// Get layer.
		const Tmx::Layer *layer = map->GetLayer(i);
		LevelModel::LayerInfo layerInfo;
		//extract basic size info
		layerInfo.width = (float)layer->GetWidth();
		layerInfo.height = (float)layer->GetHeight();

		//prepare the solidity map
		layerInfo.solidityMap = new int[layer->GetWidth()*layer->GetHeight()];

		for (int y = 0; y < layer->GetHeight(); ++y) {
			for (int x = 0; x < layer->GetWidth(); ++x) 
			{
				LevelModel::TileInfo tileInfo;


				// Find a tileset for that id.
				const Tmx::Tileset *tileset = map->FindTileset(layer->GetTileId(x, y));
				//check if horizontally flipped
				if (layer->IsTileFlippedHorizontally(x, y))
				{
					tileInfo.flippedHorizontally = true;
				}
				else
				{
					tileInfo.flippedHorizontally = false;
				}
				//check if vertically flipped
				if (layer->IsTileFlippedVertically(x, y))
				{
					tileInfo.flippedVertically = true;
				}
				else
				{
					tileInfo.flippedVertically = false;
				}

				//save the id taking into account the transformations
				if(tileInfo.flippedHorizontally ||tileInfo.flippedVertically )
				{
					//subtract 1 in case of transformation -- this is required to correct the odd behaviour of tmx editor
					tileInfo.tileId = layer->GetTileId(x, y)-1;
				}
				else
				{
					tileInfo.tileId = layer->GetTileId(x, y);
				}

				//save tileInfo in the layer
				layerInfo.layerTiles.push_back(tileInfo);
				layerInfo.solidityMap[(-y+layer->GetHeight()-1)*layer->GetWidth()+ x] = 	m_levelModel.m_sourceTileSetInfo.solidity[tileInfo.tileId];

			}			
		}
		//save layerInfo
		m_levelModel.sceneLayers.push_back(layerInfo);
	}

	/*addPlayer(Vector4(32,32,0));
	addEnemy(Vector4(200,400,0),"peonV");
	addEnemy(Vector4(500,400,0),"peonH");
	addStaticObject(Vector4(400,100,0),"shield");
	addStaticObject(Vector4(400,200,0),"potion");
	addStaticObject(Vector4(400,300,0),"boots");
	addStaticObject(Vector4(400,400,0),"coins");
	addStaticObject(Vector4(400,500,0),"gem");*/
	// Iterate through all of the object groups.
	for (int i = 0; i < map->GetNumObjectGroups(); ++i) {
		// Get an object group.
		const Tmx::ObjectGroup *objectGroup = map->GetObjectGroup(i);

		// Iterate through all objects in the object group.
		for (int j = 0; j < objectGroup->GetNumObjects(); ++j) {
			// Get an object.
			const Tmx::Object *object = objectGroup->GetObject(j);

			// Print information about the object.
			//printf("Object Name: %s\n", object->GetName().c_str());

			float logicalX = object->GetX();
			//change the 1024 for a better calculation TO_DO
			float logicalY = 768-object->GetY();

			if(object->GetName() == "boots" )
			{
				addStaticObject(Vector4(logicalX,logicalY,0),"boots");
			}
			else if(object->GetName() == "gem" )
			{
				addStaticObject(Vector4(logicalX,logicalY,0),"gem");
			}
			else if(object->GetName() == "coins" )
			{
				addStaticObject(Vector4(logicalX,logicalY,0),"coins");
			}
			else if(object->GetName() == "potion" )
			{
				addStaticObject(Vector4(logicalX,logicalY,0),"potion");
			}
			else if(object->GetName()== "shield" )
			{
				addStaticObject(Vector4(logicalX,logicalY,0),"shield");
			}
			else if(object->GetName()== "peonV" )
			{
				addEnemy(Vector4(logicalX,logicalY,0),"peonV");
			}
			else if(object->GetName()== "peonH" )
			{
				addEnemy(Vector4(logicalX,logicalY,0),"peonH");
			}
			else if(object->GetName() == "peonS" )
			{
				addEnemy(Vector4(logicalX,logicalY,0),"peonS");
			}
			else if(object->GetName() == "gruntV" )
			{
				addEnemy(Vector4(logicalX,logicalY,0),"gruntV");
			}
			else if(object->GetName() == "gruntH" )
			{
				addEnemy(Vector4(logicalX,logicalY,0),"gruntH");
			}
			else if(object->GetName() == "gruntS" )
			{
				addEnemy(Vector4(logicalX,logicalY,0),"gruntS");
			}
			else if(object->GetName() == "player" )
			{
				addPlayer(Vector4(logicalX,logicalY,0));
			}

			printf("Object Position: (%03d, %03d)\n", object->GetX(), object->GetY());
			printf("Object Size: (%03d, %03d)\n", object->GetWidth(), object->GetHeight());
		}
	}

	// Process polylines = > NOT IMPLEMENTED



}

void LevelController::addPlayer(const Vector4& playerPosition)
{
	
	//create the player controller
	m_playerController = new PlayerController();

	//create a new player model in the appropriate position
	PlayerModel* playerModel = new PlayerModel();
	playerModel->setScreenPosition(playerPosition);
	m_levelModel.setPlayerModel(playerModel);

	//create a new player view
	PlayerView* playerView = new PlayerView();
	m_levelView.setPlayerView(playerView);

	//finally initialize the controller
	m_playerController->init(&m_levelModel, playerView);

}

void LevelController::update(const float elapsedTime)
{
	int ntime = glutGet(GLUT_ELAPSED_TIME);

	OIS::Mouse* mouse = Core::singleton().inputManager().getMouse();
	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();

	if( (ntime - m_toggleTime) > 300)
	{
		if (keyboard->isKeyDown(OIS::KC_H))
		{
			m_toggleTime = ntime;
			m_hudView.switchVisibility();
		}
	}

	computeLevelLogic();

	//update player
	m_playerController->update(elapsedTime);

	//update enemies
	std::map<int, AvatarController*>::iterator enemyIt = m_enemyControllers.begin();
	while(enemyIt != m_enemyControllers.end())
	{
		enemyIt->second->update(elapsedTime);
		enemyIt++;
	}
	//update static objects
	std::map<int, StaticObjectController*>::iterator staticObjectIt = m_staticObjectControllers.begin();
	while(staticObjectIt != m_staticObjectControllers.end())
	{
		staticObjectIt->second->update(elapsedTime);
		staticObjectIt++;
	}

	//update dynamic objects
	std::map<int, DynamicObjectController*>::iterator dynamicObjectIt = m_dynamicObjectControllers.begin();
	while(dynamicObjectIt != m_dynamicObjectControllers.end())
	{
		dynamicObjectIt->second->update(elapsedTime);
		dynamicObjectIt++;
	}

	//create any dynamic objects if required
	if(m_levelModel.getPlayerModel()->getAction() == PlayerModel::AVATAR_STATE_ATTACK_DOWN ||
		m_levelModel.getPlayerModel()->getAction() == PlayerModel::AVATAR_STATE_ATTACK_UP ||
		m_levelModel.getPlayerModel()->getAction() == PlayerModel::AVATAR_STATE_ATTACK_LEFT ||
		m_levelModel.getPlayerModel()->getAction() == PlayerModel::AVATAR_STATE_ATTACK_RIGHT ||
		m_levelModel.getPlayerModel()->getAction() == PlayerModel::AVATAR_STATE_ATTACK_UP_LEFT ||
		m_levelModel.getPlayerModel()->getAction() == PlayerModel::AVATAR_STATE_ATTACK_UP_RIGHT ||
		m_levelModel.getPlayerModel()->getAction() == PlayerModel::AVATAR_STATE_ATTACK_DOWN_LEFT ||
		m_levelModel.getPlayerModel()->getAction() == PlayerModel::AVATAR_STATE_ATTACK_DOWN_RIGHT)
	{

		if( (ntime - m_toggleTime) > 100)
		{
			addDynamicObject();
			m_toggleTime=ntime;
		}

	}

}

void LevelController::computeLevelLogic()
{
	//this could eventually become a separate class!

	//clean up of enemies
	std::map<int, AvatarModel*>::iterator enemyIt = m_levelModel.getEnemyModels().begin();
	while(enemyIt != m_levelModel.getEnemyModels().end())
	{
		if(enemyIt->second->getState()== AvatarModel::AVATAR_STATE_DEAD)
		{
			std::map<int, AvatarModel*>::iterator tempIt = enemyIt;
			
			enemyIt++;
			removeEnemy(tempIt->first);
		}
		else
		{
			enemyIt++;
		}
	}

	//clean up of static objects
	std::map<int, StaticObjectModel*>::iterator staticObjectIt = m_levelModel.getStaticObjectModels().begin();
	while(staticObjectIt != m_levelModel.getStaticObjectModels().end())
	{
		if(staticObjectIt->second->getStaticObjectState() == StaticObjectModel::STATIC_OBJECT_COLLECTED)
		{
			std::map<int, StaticObjectModel*>::iterator tempIt = staticObjectIt;
			staticObjectIt++;
			removeStaticObject(tempIt->first);
		}
		else
		{
			staticObjectIt++;
		}
	}
	
	//clean up of dynamic objects
	std::map<int, DynamicObjectModel*>::iterator dynamicObjectIt = m_levelModel.getDynamicObjectModels().begin();
	while(dynamicObjectIt != m_levelModel.getDynamicObjectModels().end())
	{
		if(dynamicObjectIt->second->getState() == DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHED)
		{
			std::map<int, DynamicObjectModel*>::iterator tempIt = dynamicObjectIt;
			dynamicObjectIt++;
			removeDynamicObject(tempIt->first);
		}
		else
		{
			dynamicObjectIt++;
		}
	}



	if(m_levelModel.getPlayerModel()->getState() == AvatarModel::AvatarState::AVATAR_STATE_DEAD)
	{
		//if the player is dead => GAME OVER!!
		m_state = LEVEL_GAME_OVER;
	}
}

int LevelController::addEnemy(const Vector4& enemyPosition, std::string enemyName)
{	
	m_enemyControllers.insert(std::make_pair(m_nextNewEnemyId,EnemyFactory::create(&m_levelModel, &m_levelView,m_nextNewEnemyId, enemyName,enemyPosition)));
	m_nextNewEnemyId++;
	//if the game grows a lot, which is unlikely we would have to make sure there is no overflow of m_nextEnemyId TO_DO
	return m_nextNewEnemyId-1;
}

void LevelController::removeEnemy(int key)
{
	m_levelView.removeEnemyView(key);
	m_levelModel.removeEnemyModel(key);
	delete m_enemyControllers[key];
	 m_enemyControllers.erase(key);
}


int LevelController::addStaticObject(const Vector4& position, std::string name)
{
	m_staticObjectControllers.insert(std::make_pair(m_nextNewStaticObjectId,StaticObjectFactory::create(&m_levelModel, &m_levelView,m_nextNewStaticObjectId, name,position)));
	m_nextNewStaticObjectId++;
	//if the game grows a lot, which is unlikely we would have to make sure there is no overflow of m_nextEnemyId TO_DO
	return m_nextNewStaticObjectId-1;
}

void LevelController::removeStaticObject(int key)
{
	m_levelView.removeStaticObjectView(key);
	m_levelModel.removeStaticObjectModel(key);
	delete m_staticObjectControllers[key];
	m_staticObjectControllers.erase(key);
}

int LevelController::addDynamicObject()
{
	m_dynamicObjectControllers.insert(std::make_pair(m_nextNewDynamicObjectId,DynamicObjectFactory::create(&m_levelModel, &m_levelView,m_nextNewDynamicObjectId)));
	m_nextNewDynamicObjectId++;
	//if the game grows a lot, which is unlikely we would have to make sure there is no overflow of m_nextEnemyId TO_DO
	return m_nextNewDynamicObjectId-1;
}

void LevelController::removeDynamicObject(int key)
{
	m_levelView.removeDynamicObjectView(key);
	m_levelModel.removeDynamicObjectModel(key);
	delete m_dynamicObjectControllers[key];
	m_dynamicObjectControllers.erase(key);
}