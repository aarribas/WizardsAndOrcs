#include "LevelModel.h"
#include <iostream>


LevelModel::LevelModel()
{
}


LevelModel::~LevelModel()
{
	//clean up of static objects
	std::map<int, StaticObjectModel* >::iterator staticObjectModelIt = m_staticObjectModels.begin();
	while(staticObjectModelIt != m_staticObjectModels.end())
	{
		delete staticObjectModelIt->second;
		m_staticObjectModels.erase(staticObjectModelIt++);
	}
	//clean up of dynamacic objects
	std::map<int, DynamicObjectModel* >::iterator dynamicObjectModelIt = m_dynamicObjectModels.begin();
	while(dynamicObjectModelIt != m_dynamicObjectModels.end())
	{
		delete dynamicObjectModelIt->second;
		m_dynamicObjectModels.erase(dynamicObjectModelIt++);
	}
	//clean up of enemies
	std::map<int, AvatarModel*>::iterator enemyModelIt = m_enemyModels.begin();
	while(enemyModelIt != m_enemyModels.end())
	{
		delete enemyModelIt->second;
		m_enemyModels.erase(enemyModelIt++);
	}

	//clean up of player
	delete m_playerModel;

	//clean of of the scene info
	std::vector<LevelModel::LayerInfo>::iterator layerIt = sceneLayers.begin();
	while(layerIt != sceneLayers.end())
	{
		delete[] layerIt->solidityMap;

		std::vector<LevelModel::TileInfo>::iterator tileInfoIt = layerIt->layerTiles.begin();
		while(tileInfoIt != layerIt->layerTiles.end())
		{
			tileInfoIt = layerIt->layerTiles.erase(tileInfoIt);

		}
		layerIt = sceneLayers.erase(layerIt);
	}

	//clean up of tile info
	std::vector<int>::iterator tileSetInfoIt = m_sourceTileSetInfo.solidity.begin();
	while(tileSetInfoIt != m_sourceTileSetInfo.solidity.end())
	{
		tileSetInfoIt = m_sourceTileSetInfo.solidity.erase(tileSetInfoIt);
	}

}

void LevelModel::setPlayerModel(PlayerModel* playerModel)
{
	m_playerModel = playerModel;
}

void LevelModel::addEnemyModel(AvatarModel* enemyModel, int key)
{	

	m_enemyModels.insert(std::make_pair(key,enemyModel));

}

void LevelModel::removeEnemyModel(int key)
{
	//erase the enemy and erase by key
	delete m_enemyModels[key];
	m_enemyModels.erase(key);
}

void LevelModel::addStaticObjectModel(StaticObjectModel* staticObjectModel, int key)
{	

	m_staticObjectModels.insert(std::make_pair(key,staticObjectModel));

}

void LevelModel::removeStaticObjectModel(int key)
{
	//erase the enemy and erase by key
	delete m_staticObjectModels[key];
	m_staticObjectModels.erase(key);
}

void LevelModel::addDynamicObjectModel(DynamicObjectModel* dynamicObjectModel, int key)
{	

	m_dynamicObjectModels.insert(std::make_pair(key,dynamicObjectModel));

}

void LevelModel::removeDynamicObjectModel(int key)
{
	//erase the enemy and erase by key
	delete m_staticObjectModels[key];
	m_staticObjectModels.erase(key);
}

int LevelModel::getTileSolidity(int tileX, int tileY)
{
	
	int tileSolidity = 0;
	
	std::vector<LayerInfo>::const_iterator layerIt = sceneLayers.begin();

	while(layerIt!=sceneLayers.end())
	{
		//return maximum solidity if we are out of boundaries of the map
		if(tileX < 0  || tileX > (int)layerIt->width) {return 9;}
		if(tileY < 0  || tileY > (int)layerIt->height) {return 9;}

		if(layerIt->solidityMap[tileY* (int)layerIt->width + tileX] > tileSolidity)
		{
			tileSolidity = layerIt->solidityMap[tileY* (int)layerIt->width + tileX];
		}
		layerIt++;
	}

	return tileSolidity;
}