#pragma once
#include "TmxParser/Tmx.h"
#include "PlayerModel.h"
#include <vector>
#include <map>
#include <string>
#include "Vector4.h"
#include "StaticObjectModel.h"
#include "DynamicObjectModel.h"

class LevelModel
{
public:
	//simplistic struct to store tileSetInfo. If the complexity of tileSet grows we should create a Class.
	struct TileSetInfo
	{
		std::string name;
		float width;
		float height;
		float tileWidth;
		float tileHeight;
		std::vector<int> solidity; //basic solidity vector to be used when checking for collisions
	};

	//simplistic struct to store tile info. If the complexity of tile grows we should create a Class.
	struct TileInfo
	{
		int tileId;
		bool flippedHorizontally;
		bool flippedVertically;
	};

	//simplistic struct to store layer info (contains the actual tiles). 
	//If the complexity of layer grows we should create a Class.
	struct LayerInfo
	{
		float width;
		float height;
		std::vector<TileInfo> layerTiles;
		int* solidityMap;
	};

public:
	friend class LevelController;

	LevelModel();
	~LevelModel();
	
	//tileset management	
	const float getTileSetWidth(){return m_sourceTileSetInfo.width; };

	const float getTileSetHeight(){return m_sourceTileSetInfo.height; };

	const float getTileSetTileWidth(){return m_sourceTileSetInfo.tileWidth; };

	const float getTileSetTileHeight(){return m_sourceTileSetInfo.tileHeight; };

	const std::string getTileSetName(){return m_sourceTileSetInfo.name; };
	
	//layer management - includes the solidity management
	std::vector<int>& getTileSetSolidity(){return m_sourceTileSetInfo.solidity;};
	
	int getTileSolidity(int tileX, int tileY);

	const std::vector<LayerInfo>& getLayers(){return sceneLayers; };
	
	//player management
	void setPlayerModel(PlayerModel*);

	PlayerModel* getPlayerModel(){ return m_playerModel; }
	
	//enemy management
	void addEnemyModel(AvatarModel*, int key);

	AvatarModel* getEnemyModel(int key) {return m_enemyModels[key];} 
	
	std::map<int, AvatarModel*>&  getEnemyModels() {return m_enemyModels;} 

	void removeEnemyModel(int key);
	
	//static object management	
	void addStaticObjectModel(StaticObjectModel*, int key);

	StaticObjectModel* getStaticObjectModel(int key) {return m_staticObjectModels[key];} 
	
	std::map<int, StaticObjectModel*>&  getStaticObjectModels() {return m_staticObjectModels;} 

	void removeStaticObjectModel(int key);


	
	//dynamic object management	
	void addDynamicObjectModel(DynamicObjectModel*, int key);

	DynamicObjectModel* getDynamicObjectModel(int key) {return m_dynamicObjectModels[key];} 
	
	std::map<int, DynamicObjectModel*>&  getDynamicObjectModels() {return m_dynamicObjectModels;} 

	void removeDynamicObjectModel(int key);

private:

	TileSetInfo m_sourceTileSetInfo;
	std::vector<LayerInfo> sceneLayers;
	std::map<int, AvatarModel*> m_enemyModels;
	std::map<int, StaticObjectModel*> m_staticObjectModels;
	std::map<int, DynamicObjectModel*> m_dynamicObjectModels;
	PlayerModel* m_playerModel;
	int m_nextNewEnemyId;
	
};