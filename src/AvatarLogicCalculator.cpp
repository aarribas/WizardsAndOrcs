#include "AvatarLogicCalculator.h"

AvatarLogicCalculator::AvatarLogicCalculator()
{
}

AvatarLogicCalculator::~AvatarLogicCalculator()
{
}



void AvatarLogicCalculator::correctStepsDueToWallCollisions()
{
	//in case of collision we stop the movement in that direction
	float stepX,stepY;
	m_avatarModel->getStep(&stepX,&stepY);
	if(collidesOnRight() == true && stepX > 0) {stepX = 0;}
	if(collidesOnLeft() == true && stepX < 0) {stepX = 0;}
	if(collidesOnCeiling() == true && stepY > 0 ) {stepY = 0;}
	if(collidesOnFloor() == true && stepY < 0 ) {stepY = 0;}
	m_avatarModel->setStep(stepX,stepY);
}

std::pair<float,float>  AvatarLogicCalculator::computeDirection(float destinationX, float destinationY)
{

	
	float avatarX = m_avatarModel->getTerrainPosition()[0];
	float avatarY = m_avatarModel->getTerrainPosition()[1];

	float hypo = std::sqrtf( (avatarX-destinationX)* (avatarX-destinationX) + (avatarY-destinationY)* (avatarY-destinationY) );

	float stepX = (destinationX-avatarX)/hypo;
	float stepY = (destinationY-avatarY)/hypo;

	return std::make_pair(stepX,stepY);

}

void AvatarLogicCalculator::computeAndSetDirection(float destinationX, float destinationY)
{
	std::pair<float,float> directions = computeDirection(destinationX, destinationY);
	m_avatarModel->setStep(directions.first,directions.second);
}

void AvatarLogicCalculator::setAttackAction()
{
	float stepX;
	float stepY;
	
	m_avatarModel->getStep(&stepX,&stepY);
	

	//the following sets the action according to the angle between the avatar and the click
	//for this we devide 2pi radians into pi/4 rad slices starting at +pi/8 rads.
	//We compare stepX to the cos of the angle and we look at the sign of stepY to find out if 
	//The click took part over the avatar or under it.

	if(stepX > 0.92387953251)
	{
		m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_RIGHT);
	}
	else if(stepX > 0.38268343236 && stepX<= 0.92387953251)
	{
		if(stepY > 0)
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_UP_RIGHT);
		}
		else
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_DOWN_RIGHT);
		}
		
	}
	else if( stepX > -0.38268343236 && stepX <= 0.38268343236)
	{
		if(stepY > 0)
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_UP);
		}
		else
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_DOWN);
		}

	
	}
	else if(stepX > -0.92387953251 && stepX<= -0.38268343236)
	{
		if(stepY > 0)
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_UP_LEFT);
		}
		else
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_DOWN_LEFT);
		}
	}
	else if (stepX <= -0.92387953251)
	{
		m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_ATTACK_LEFT);
	}
}

void AvatarLogicCalculator::setMoveAction()
{
	
	float stepX;
	float stepY;
	
	m_avatarModel->getStep(&stepX,&stepY);

	//the following sets the action according to the angle between the avatar and the click
	//for this we devide 2pi radians into pi/4 rad slices starting at +pi/8 rads.
	//We compare stepX to the cos of the angle and we look at the sign of stepY to find out if 
	//The click took part over the avatar or under it.
	if(stepX > 0.92387953251)
	{
		m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_RIGHT);
	}
	else if(stepX > 0.38268343236 && stepX<= 0.92387953251)
	{
		if(stepY > 0)
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_UP_RIGHT);
		}
		else
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_DOWN_RIGHT);
		}
		
	}
	else if( stepX > -0.38268343236 && stepX <= 0.38268343236)
	{
		if(stepY > 0)
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_UP);
		}
		else
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_DOWN);
		}

	
	}
	else if(stepX > -0.92387953251 && stepX<= -0.38268343236)
	{
		if(stepY > 0)
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_UP_LEFT);
		}
		else
		{
			m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_DOWN_LEFT);
		}
	}
	else if (stepX <= -0.92387953251)
	{
		m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_MOVE_LEFT);
	}
}

bool AvatarLogicCalculator::collidesOnRight()
{
	
	//get avatar logical location
	int avatarX = m_avatarModel->getTerrainPosition()[0];
	int avatarY = m_avatarModel->getTerrainPosition()[1];
	
	//get the right position of the sprite in logical position
	int xRightWall = m_avatarModel->getTerrainPosition()[0] + (m_avatarModel->getPixelWidth()/PIXELS_PER_METER)/2;	
	
	//get reference tile x and y
	int tile_x = (xRightWall) / (m_levelModel->getTileSetTileWidth()/ PIXELS_PER_METER);
	int tile_y = avatarY / (m_levelModel->getTileSetTileHeight()/ PIXELS_PER_METER);


	//get number of vertical tiles in which the avatar can be divided
	int numVerticalTiles = (m_avatarModel->getPixelHeight()/m_levelModel->getTileSetTileHeight()) ;

	for(int verticalTile = 0 ; verticalTile < numVerticalTiles ; verticalTile++)
	{
		//check for solidity of tile matching right border
		if(m_levelModel->getTileSolidity(tile_x ,tile_y + verticalTile) == 9) {return true;} 
	}
	
	return false;
}

bool AvatarLogicCalculator::collidesOnLeft()
{
	
	//get avatar logical location
	int avatarX = m_avatarModel->getTerrainPosition()[0];
	int avatarY = m_avatarModel->getTerrainPosition()[1];

	
	
	//get the right position of the sprite in logical position
	int xLeftWall = m_avatarModel->getTerrainPosition()[0] - (m_avatarModel->getPixelWidth()/PIXELS_PER_METER)/2;	

	//get reference tile x and y
	int tile_x = (xLeftWall) / (m_levelModel->getTileSetTileWidth()/ PIXELS_PER_METER);
	int tile_y = avatarY / (m_levelModel->getTileSetTileHeight()/ PIXELS_PER_METER);


	//get number of vertical tiles in which the avatar can be divided
	int numVerticalTiles = (m_avatarModel->getPixelHeight()/m_levelModel->getTileSetTileHeight()) ;

	for(int verticalTile = 0 ; verticalTile < numVerticalTiles ; verticalTile++)
	{
		if(m_levelModel->getTileSolidity(tile_x ,tile_y + verticalTile) == 9) {return true;} 
	}
	
	return false;
}


bool AvatarLogicCalculator::collidesOnCeiling()
{
	

	int avatarX = m_avatarModel->getTerrainPosition()[0];
	float yCeiling= m_avatarModel->getTerrainPosition()[1] + (m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)/2;

	//get reference tile x and y
	int tile_x = avatarX / (m_levelModel->getTileSetTileWidth()/ PIXELS_PER_METER);
	int tile_y = yCeiling / (m_levelModel->getTileSetTileHeight()/ PIXELS_PER_METER);

	//get number of horizontal tiles in which the avatar can be divided
	int numHorizontalTiles = (m_avatarModel->getPixelWidth()/m_levelModel->getTileSetTileWidth()) ;

	if( (avatarX % ((int)(m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)) ) != 0) numHorizontalTiles++;

	//check using only central tiles
	int i=0;
	if(numHorizontalTiles >2)
	{
		i =1;
		numHorizontalTiles--;
	}
	else
	{
		numHorizontalTiles = 1;
	}

	while( (i<numHorizontalTiles))
	{
		
		if(m_levelModel->getTileSolidity(tile_x + i,tile_y) == 9) {return true;} 
		i++;
	}

	return false;
}


bool AvatarLogicCalculator::collidesOnFloor()
{
	

	float  avatarX = m_avatarModel->getTerrainPosition()[0];
	//we use tileset tile width to correct the collision on purpose. Otherwise the player might get stuck when path-walking
	//This probably should be done differently for the other avatars.
	float yFloor= m_avatarModel->getTerrainPosition()[1] - (m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER)/2;


	//get reference tile x and y conversion to int intended
	int tile_x = avatarX / (m_levelModel->getTileSetTileWidth()/ PIXELS_PER_METER);
	int tile_y = yFloor / (m_levelModel->getTileSetTileHeight()/ PIXELS_PER_METER);

	//get number of horizontal tiles in which the avatar can be divided
	int numHorizontalTiles = (m_avatarModel->getPixelWidth()/m_levelModel->getTileSetTileWidth()) ;
	if( ((int)avatarX % ((int)(m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)) ) != 0) numHorizontalTiles++;
	
	//check using only central tiles
	int i=0;
	if(numHorizontalTiles >2)
	{
		i =1;
		numHorizontalTiles--;
	}
	else
	{
		numHorizontalTiles = 1;
	}
	
	while( (i<numHorizontalTiles))
	{
		
		if(m_levelModel->getTileSolidity(tile_x + i,tile_y) == 9) {return true;} 
		i++;
	}
	return false;
}

bool AvatarLogicCalculator::collides(const AvatarModel::Rect& rect)
{
	return (((m_avatarModel->getRect().left>=rect.left) && (m_avatarModel->getRect().left<=rect.right) && (m_avatarModel->getRect().bottom<=rect.bottom) && (m_avatarModel->getRect().top>=rect.bottom)) ||
		((m_avatarModel->getRect().left<=rect.left) && (m_avatarModel->getRect().right>=rect.left) && (m_avatarModel->getRect().bottom<=rect.bottom) && (m_avatarModel->getRect().top>=rect.bottom)) ||
		((m_avatarModel->getRect().left>=rect.left) && (m_avatarModel->getRect().left<=rect.right) && (m_avatarModel->getRect().bottom>=rect.bottom) && (m_avatarModel->getRect().bottom<=rect.top))||
		((m_avatarModel->getRect().left<=rect.left) && (m_avatarModel->getRect().right>=rect.left) && (m_avatarModel->getRect().bottom>=rect.bottom) && (m_avatarModel->getRect().bottom<=rect.top)) );

}
