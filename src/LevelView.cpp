#include "LevelView.h"
#include "MyGL.h"
#include "Core.h"
#include <iostream>

LevelView::LevelView()
{
}


LevelView::~LevelView()
{
	//clean up of static objects
	std::map<int, StaticObjectView*>::iterator staticObjectViewIt = m_staticObjectViews.begin();
	while(staticObjectViewIt != m_staticObjectViews.end())
	{
		delete staticObjectViewIt->second;
		m_staticObjectViews.erase(staticObjectViewIt++);
	}

	//clean up of dynamic objects
	std::map<int, DynamicObjectView*>::iterator dynamicObjectViewIt = m_dynamicObjectViews.begin();
	while(dynamicObjectViewIt != m_dynamicObjectViews.end())
	{
		delete dynamicObjectViewIt->second;
		m_dynamicObjectViews.erase(dynamicObjectViewIt++);
	}

	//clean up of enemies
	std::map<int, AvatarView*>::iterator enemyViewIt = m_enemyViews.begin();
	while(enemyViewIt != m_enemyViews.end())
	{
		delete enemyViewIt->second;
		m_enemyViews.erase(enemyViewIt++);
	}

	//clean up the player view
	delete m_playerView;

	//clean up the scene view
	std::vector<int>::const_iterator sceneIt = m_sceneGlIds.begin();
	while(sceneIt != m_sceneGlIds.end())
	{
		sceneIt = m_sceneGlIds.erase(sceneIt);
	}
}

void LevelView::init(const LevelModel& levelModel)
{
	m_levelModel = levelModel;
	initScene();

}

void LevelView::initScene()
{
	//get layers
	std::vector<LevelModel::LayerInfo> layers = m_levelModel.getLayers();

	//create a list per layer
	std::vector<LevelModel::LayerInfo>::const_iterator layerIt = layers.begin();
	while(layerIt != layers.end())
	{	
		int glId = glGenLists(1);
		glNewList(glId,GL_COMPILE);
		m_sceneGlIds.push_back(glId); //store the glId
		glBegin(GL_QUADS);
		
		//reset indexes 
		int tileIndex = 0;
		
		float tilePosX = 0;
		float tilePosY = layerIt->height;
		
		float texturePosX = 0;
		float texturePosY = 0;


		for(int h = 0; h < layerIt->height; h++)
		{
			for(int w=0; w < layerIt->width ; w++)
			{				
				//base vertex coordinates
				tilePosX = w * m_levelModel.getTileSetTileWidth();
				tilePosY = (layerIt->height - 1)* m_levelModel.getTileSetTileHeight() - h*m_levelModel.getTileSetTileHeight();

				//base texture coordinates - they are not absolute position coordinates but are rather based on the ratio tilesize/tilesetsize
				texturePosX = (float)(m_levelModel.getTileSetTileWidth()/m_levelModel.getTileSetWidth()) * 
					(float)(layerIt->layerTiles[tileIndex].tileId % (int)(m_levelModel.getTileSetWidth()/m_levelModel.getTileSetTileWidth()));
				texturePosY =  
					(m_levelModel.getTileSetTileHeight()/m_levelModel.getTileSetHeight())*
					(float)(layerIt->layerTiles[tileIndex].tileId / (int)(m_levelModel.getTileSetHeight()/m_levelModel.getTileSetTileHeight())); 
			
				//assign coordinates
				glTexCoord2f(texturePosX        ,texturePosY + m_levelModel.getTileSetTileHeight()/m_levelModel.getTileSetHeight());	
				glVertex2i(tilePosX           ,tilePosY           );
				glTexCoord2f(texturePosX + m_levelModel.getTileSetTileWidth()/m_levelModel.getTileSetWidth(),texturePosY + m_levelModel.getTileSetTileHeight()/m_levelModel.getTileSetHeight());	
				glVertex2i(tilePosX + m_levelModel.getTileSetTileWidth(),tilePosY);
				glTexCoord2f(texturePosX + m_levelModel.getTileSetTileWidth()/m_levelModel.getTileSetWidth(),texturePosY       );	
				glVertex2i(tilePosX + m_levelModel.getTileSetTileWidth(),tilePosY + m_levelModel.getTileSetTileWidth());
				glTexCoord2f(texturePosX       ,texturePosY       );	
				glVertex2i(tilePosX           ,tilePosY + m_levelModel.getTileSetTileWidth());
				
				tileIndex++;

			}//width for

		}//height for

		layerIt++;
		glEnd();
		glEndList();

	}
}

void LevelView::draw()
{
	//display gllist  -  ergo tiles
	std::vector<int>::const_iterator sceneIt = m_sceneGlIds.begin();
	while(sceneIt != m_sceneGlIds.end())
	{
		glPushMatrix();
		Core::singleton().textureManager().getTextureAtlas(m_levelModel.getTileSetName())->texture()->bind();
		glCallList(*sceneIt);
		sceneIt++;
		glPopMatrix();
	}

	//draw static objects
	std::map<int, StaticObjectView*>::const_iterator staticObjectViewIt = m_staticObjectViews.begin();
	while(staticObjectViewIt!=m_staticObjectViews.end())
	{
		staticObjectViewIt->second->draw();
		staticObjectViewIt++;
	}

	//draw enemies
	std::map<int, AvatarView*>::const_iterator enemyViewIt = m_enemyViews.begin();
	while(enemyViewIt!=m_enemyViews.end())
	{
		enemyViewIt->second->draw();
		enemyViewIt++;
	}

	//draw dynamic objects
	std::map<int, DynamicObjectView*>::const_iterator dynamicObjectViewIt = m_dynamicObjectViews.begin();
	while(dynamicObjectViewIt!=m_dynamicObjectViews.end())
	{
		dynamicObjectViewIt->second->draw();
		dynamicObjectViewIt++;
	}
	//draw player
	m_playerView->draw();

}

void LevelView::addEnemyView(AvatarView* enemyView, int key)
{	

	m_enemyViews.insert(std::make_pair(key,enemyView));

}

void LevelView::removeEnemyView(int key)
{
	//erase the enemy and erase by key
	delete m_enemyViews[key];
	m_enemyViews.erase(key);
}

void LevelView::addStaticObjectView(StaticObjectView* staticObjectView, int key)
{	

	m_staticObjectViews.insert(std::make_pair(key,staticObjectView));

}

void LevelView::removeStaticObjectView(int key)
{
	//erase the object and erase by key
	//std::map<int, StaticObjectView*>::iterator it  = m_staticObjectViews.find(key);
	delete m_staticObjectViews[key];
	m_staticObjectViews.erase(key);
}

void LevelView::addDynamicObjectView(DynamicObjectView* dynamicObjectView, int key)
{	

	m_dynamicObjectViews.insert(std::make_pair(key,dynamicObjectView));

}

void LevelView::removeDynamicObjectView(int key)
{
	//erase the object and erase by key
	//std::map<int, DynamicObjectView*>::iterator it  = m_dynamicObjectViews.find(key);
	delete m_dynamicObjectViews[key];
	m_dynamicObjectViews.erase(key);
}