#include "EnemyLogicCalculator.h"
#include "Core.h"

EnemyLogicCalculator::EnemyLogicCalculator():
m_collidingWithPlayer(false)
{
}

EnemyLogicCalculator::~EnemyLogicCalculator()
{
	//not responsible to free any element 
}

void EnemyLogicCalculator::init(LevelModel* levelModel, AvatarModel* avatarModel )
{
	m_avatarModel = avatarModel;
	m_levelModel = levelModel;
}


bool EnemyLogicCalculator::isPlayerCloseAndVisible()
{
	float distanceToPlayer = std::sqrtf(
		(m_levelModel->getPlayerModel()->getTerrainPosition()[0]-m_avatarModel->getTerrainPosition()[0])*(m_levelModel->getPlayerModel()->getTerrainPosition()[0]-m_avatarModel->getTerrainPosition()[0]) 
		+
		(m_levelModel->getPlayerModel()->getTerrainPosition()[1]-m_avatarModel->getTerrainPosition()[1])*(m_levelModel->getPlayerModel()->getTerrainPosition()[1]-m_avatarModel->getTerrainPosition()[1]) 
		);

	//check if distance is close enough this value should become a constant somewhere or depend on the type of enemy
	//TO_DO
	if(distanceToPlayer < 40)
	{	//if close enough check for visibility
		if(isPlayerVisible())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}

bool EnemyLogicCalculator::isPlayerVisible()
{
	float playerX = m_levelModel->getPlayerModel()->getTerrainPosition()[0]*PIXELS_PER_METER/m_levelModel->getTileSetTileWidth();
	float playerY = m_levelModel->getPlayerModel()->getTerrainPosition()[1]*PIXELS_PER_METER/m_levelModel->getTileSetTileHeight();

	float avatarX = m_avatarModel->getTerrainPosition()[0]*PIXELS_PER_METER/m_levelModel->getTileSetTileWidth();
	float avatarY = m_avatarModel->getTerrainPosition()[1]*PIXELS_PER_METER/m_levelModel->getTileSetTileHeight();

	//check solidity of tiles going from Player to Enemy/Avatar in a straight line 
	//if the x tiles of player and avatar coincide we simplify the checking and avoid an exception (the slope is inf)

	int tilePlayerX =playerX;
	int tileAvatarX = avatarX;
	int tilePlayerY =playerY;
	int tileAvatarY = avatarY;

	if( tilePlayerX != tileAvatarX)
	{
		float slope = (float)(playerY - avatarY)/(float)(playerX-avatarX);

		float y = playerY;

		if(playerX > avatarX)
		{
			//I have to assume only one solidity in the first layer. This is to be corrected in the future TO_DO
			//Even better would be to have a visibility layer
			//IMPORTANT: we visit the tiles using small steps in x otherwise we could jump tiles for very steep slopes!!!
			//We assume a solid tile is a tile the enemies cannot see through.
			for(float x = playerX; x > avatarX; x-= std::abs(playerX-avatarX)/50.0f)
			{

				//ATTENTION: the casts to int are extremely important!
				y=(slope*x + playerY-playerX*slope);
				if(m_levelModel->getTileSolidity((int)x,(int)y) == 9) {return false;} 
			}
		}
		else
		{

			for(float x = playerX; x < avatarX; x+=std::abs(playerX-avatarX)/50.0f)
			{
				y=(slope*x + playerY-playerX*slope);
				//ATTENTION:the cast to int are extremely important!
				if(m_levelModel->getTileSolidity((int)x,(int)y) == 9) {return false;} 

			}
		}
	}
	else
	{
		//move on a straight vertical line from player to avatar checking the tiles
		if(tilePlayerY> tileAvatarY)
		{
			//I have to assume only one solidity in the first layer. This is to be corrected in the future TO_DO
			//Even better would be to have a visibility layer
			for(int y = tilePlayerY; y > tileAvatarY; y--)
			{
				if(m_levelModel->getTileSolidity((int)avatarX,(int)y) == 9) {return false;} 
			}
		}
		else
		{

			for(int y = tilePlayerY; y < tileAvatarY; y++)
			{
				if(m_levelModel->getTileSolidity((int)avatarX,(int)y) == 9) {return false;} 


			}
		}
	}

	return true;

}