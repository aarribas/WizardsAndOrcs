#include "DynamicObjectLogicCalculator.h"

DynamicObjectLogicCalculator::DynamicObjectLogicCalculator()
{
}

DynamicObjectLogicCalculator::~DynamicObjectLogicCalculator()
{
}


void DynamicObjectLogicCalculator::correctStepsDueToWallCollisions()
{
	//in case of collision we stop the movement in that direction
	float stepX,stepY;
	m_dynamicObjectModel->getStep(&stepX,&stepY);
	if(collidesOnRight() == true && stepX > 0) {stepX = 0;}
	if(collidesOnLeft() == true && stepX < 0) {stepX = 0;}
	if(collidesOnCeiling() == true && stepY > 0 ) {stepY = 0;}
	if(collidesOnFloor() == true && stepY < 0 ) {stepY = 0;}
	m_dynamicObjectModel->setStep(stepX,stepY);
}

std::pair<float,float>  DynamicObjectLogicCalculator::computeDirection(float destinationX, float destinationY)
{

	
	float dynamicObjectX = m_dynamicObjectModel->getTerrainPosition()[0];
	float dynamicObjectY = m_dynamicObjectModel->getTerrainPosition()[1];

	float hypo = std::sqrtf( (dynamicObjectX-destinationX)* (dynamicObjectX-destinationX) + (dynamicObjectY-destinationY)* (dynamicObjectY-destinationY) );

	float stepX = (destinationX-dynamicObjectX)/hypo;
	float stepY = (destinationY-dynamicObjectY)/hypo;

	return std::make_pair(stepX,stepY);

}

void DynamicObjectLogicCalculator::computeAndSetDirection(float destinationX, float destinationY)
{
	std::pair<float,float> directions = computeDirection(destinationX, destinationY);
	m_dynamicObjectModel->setStep(directions.first,directions.second);
}
void DynamicObjectLogicCalculator::setMoveAction()
{
	
	float stepX;
	float stepY;
	
	m_dynamicObjectModel->getStep(&stepX,&stepY);

	//the following sets the action according to the angle between the dynamicObject and the steps direction
	//for this we devide 2pi radians into pi/4 rad slices starting at +pi/8 rads.
	//We compare stepX to the cos of the angle and we look at the sign of stepY to find out if 
	//The click took part over the dynamicObject or under it.

	if(stepX > 0.92387953251)
	{
		m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_MOVE_RIGHT);
	}
	else if(stepX > 0.38268343236 && stepX<= 0.92387953251)
	{
		if(stepY > 0)
		{
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_MOVE_UP_RIGHT);
		}
		else
		{
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_MOVE_DOWN_RIGHT);
		}
		
	}
	else if( stepX > -0.38268343236 && stepX <= 0.38268343236)
	{
		if(stepY > 0)
		{
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_MOVE_UP);
		}
		else
		{
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_MOVE_DOWN);
		}

	
	}
	else if(stepX > -0.92387953251 && stepX<= -0.38268343236)
	{
		if(stepY > 0)
		{
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_MOVE_UP_LEFT);
		}
		else
		{
			m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_MOVE_DOWN_LEFT);
		}
	}
	else if (stepX <= -0.92387953251)
	{
		m_dynamicObjectModel->setAction(DynamicObjectModel::DYNAMIC_OBJECT_ACTION_MOVE_LEFT);
	}
}

bool DynamicObjectLogicCalculator::collidesOnRight()
{
	
	//get dynamicObject logical location
	int dynamicObjectX = m_dynamicObjectModel->getTerrainPosition()[0];
	int dynamicObjectY = m_dynamicObjectModel->getTerrainPosition()[1];
	
	//get the right position of the sprite in logical position
	int xRightWall = m_dynamicObjectModel->getTerrainPosition()[0] + (m_dynamicObjectModel->getPixelWidth()/PIXELS_PER_METER)/2;	
	
	//get reference tile x and y
	int tile_x = (xRightWall) / (m_levelModel->getTileSetTileWidth()/ PIXELS_PER_METER);
	int tile_y = dynamicObjectY / (m_levelModel->getTileSetTileHeight()/ PIXELS_PER_METER);


	//get number of vertical tiles in which the dynamicObject can be divided
	int numVerticalTiles = (m_dynamicObjectModel->getPixelHeight()/m_levelModel->getTileSetTileHeight()) ;

	for(int verticalTile = 0 ; verticalTile < numVerticalTiles ; verticalTile++)
	{
		//check for solidity of tile matching right border
		if(m_levelModel->getTileSolidity(tile_x ,tile_y + verticalTile) == 9) {return true;} 
	}
	
	return false;
}

bool DynamicObjectLogicCalculator::collidesOnLeft()
{
	
	//get dynamicObject logical location
	int dynamicObjectX = m_dynamicObjectModel->getTerrainPosition()[0];
	int dynamicObjectY = m_dynamicObjectModel->getTerrainPosition()[1];

	
	
	//get the right position of the sprite in logical position
	int xLeftWall = m_dynamicObjectModel->getTerrainPosition()[0] - (m_dynamicObjectModel->getPixelWidth()/PIXELS_PER_METER)/2;	

	//get reference tile x and y
	int tile_x = (xLeftWall) / (m_levelModel->getTileSetTileWidth()/ PIXELS_PER_METER);
	int tile_y = dynamicObjectY / (m_levelModel->getTileSetTileHeight()/ PIXELS_PER_METER);


	//get number of vertical tiles in which the dynamicObject can be divided
	int numVerticalTiles = (m_dynamicObjectModel->getPixelHeight()/m_levelModel->getTileSetTileHeight()) ;

	for(int verticalTile = 0 ; verticalTile < numVerticalTiles ; verticalTile++)
	{
		if(m_levelModel->getTileSolidity(tile_x ,tile_y + verticalTile) == 9) {return true;} 
	}
	
	return false;
}


bool DynamicObjectLogicCalculator::collidesOnCeiling()
{
	

	int dynamicObjectX = m_dynamicObjectModel->getTerrainPosition()[0];
	float yCeiling= m_dynamicObjectModel->getTerrainPosition()[1] + (m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)/2;

	//get reference tile x and y
	int tile_x = dynamicObjectX / (m_levelModel->getTileSetTileWidth()/ PIXELS_PER_METER);
	int tile_y = yCeiling / (m_levelModel->getTileSetTileHeight()/ PIXELS_PER_METER);

	//get number of horizontal tiles in which the dynamicObject can be divided
	int numHorizontalTiles = (m_dynamicObjectModel->getPixelWidth()/m_levelModel->getTileSetTileWidth()) ;

	if( (dynamicObjectX % ((int)(m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)) ) != 0) numHorizontalTiles++;

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


bool DynamicObjectLogicCalculator::collidesOnFloor()
{
	

	float  dynamicObjectX = m_dynamicObjectModel->getTerrainPosition()[0];
	//we use tileset tile width to correct the collision on purpose. Otherwise the player might get stuck when path-walking
	//This probably should be done differently for the other dynamicObjects.
	float yFloor= m_dynamicObjectModel->getTerrainPosition()[1] - (m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER)/2;


	//get reference tile x and y
	int tile_x = dynamicObjectX / (m_levelModel->getTileSetTileWidth()/ PIXELS_PER_METER);
	int tile_y = yFloor / (m_levelModel->getTileSetTileHeight()/ PIXELS_PER_METER);

	//get number of horizontal tiles in which the dynamicObject can be divided
	int numHorizontalTiles = (m_dynamicObjectModel->getPixelWidth()/m_levelModel->getTileSetTileWidth()) ;
	if( ((int)dynamicObjectX % ((int)(m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)) ) != 0) numHorizontalTiles++;
	
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

bool DynamicObjectLogicCalculator::collides(const AvatarModel::Rect& rect)
{
	return (((m_dynamicObjectModel->getRect().left>=rect.left) && (m_dynamicObjectModel->getRect().left<=rect.right) && (m_dynamicObjectModel->getRect().bottom<=rect.bottom) && (m_dynamicObjectModel->getRect().top>=rect.bottom)) ||
		((m_dynamicObjectModel->getRect().left<=rect.left) && (m_dynamicObjectModel->getRect().right>=rect.left) && (m_dynamicObjectModel->getRect().bottom<=rect.bottom) && (m_dynamicObjectModel->getRect().top>=rect.bottom)) ||
		((m_dynamicObjectModel->getRect().left>=rect.left) && (m_dynamicObjectModel->getRect().left<=rect.right) && (m_dynamicObjectModel->getRect().bottom>=rect.bottom) && (m_dynamicObjectModel->getRect().bottom<=rect.top))||
		((m_dynamicObjectModel->getRect().left<=rect.left) && (m_dynamicObjectModel->getRect().right>=rect.left) && (m_dynamicObjectModel->getRect().bottom>=rect.bottom) && (m_dynamicObjectModel->getRect().bottom<=rect.top)) );

}
