#include "PlayerLogicCalculator.h"
#include "Core.h"
#include "MapSearchNode.h" // See header for copyright and usage information

PlayerLogicCalculator::PlayerLogicCalculator():
m_toggleTime(0),
m_visitedNodes(0),
m_walkingFoundPath(false),
contador(0),
m_searchingPath(false)
{
}

PlayerLogicCalculator::~PlayerLogicCalculator()
{
	//not responsible to free any element 
	//there is some tight coupling in this class though. TO IMPROVE
}

void PlayerLogicCalculator::init(LevelModel* levelModel, AvatarModel* avatarModel)
{
	m_avatarModel = avatarModel;
	m_levelModel = levelModel;
}

void PlayerLogicCalculator::computeLogic()
{
	//check if dead - if so do not go any further
	if(m_avatarModel->getLifePoints()<1)
	{
		m_avatarModel->setAction(AvatarModel::AVATAR_ACTION_DIE);
		return;
	}

	interactWithEnemies();
	processInput();
	if(m_walkingFoundPath)keepWalkingPath();
	correctStepsDueToWallCollisions();
	correctStepsDueToEnemyCollisions();	
}

void PlayerLogicCalculator::processInput()
{
	
	OIS::Mouse* mouse = Core::singleton().inputManager().getMouse();
	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();

	int ntime = glutGet(GLUT_ELAPSED_TIME);

	if( (ntime - m_toggleTime) > 90)
	{

		if(mouse->getMouseState().buttonDown(OIS::MB_Left))
		{
			
			//stop walking path
			if(m_walkingFoundPath) endWalkingPath();

			int tileClickedX = (mouse->getMouseState().X.abs)/m_levelModel->getTileSetTileWidth();
			int tileClickedY = (glutGet(GLUT_WINDOW_HEIGHT) - (mouse->getMouseState().Y.abs))/m_levelModel->getTileSetTileHeight();
			

			if(checkIfValidMoveRequest(tileClickedX,tileClickedY))
			{
				
				//check for a path and start walking
				if(searchPath(tileClickedX,tileClickedY))
				{
					startWalkingPath();
				}
				m_toggleTime=ntime;
				return;
			}
			else
			{
				//nothing to do
				
			}
			//could play a sound if the request is not valid TO_DO
			
		}
		
		if(mouse->getMouseState().buttonDown(OIS::MB_Right))
		{
			//stop walking path
			if(m_walkingFoundPath) endWalkingPath();

			//get direction
			computeAndSetDirection(mouse->getMouseState().X.abs/PIXELS_PER_METER, (glutGet(GLUT_WINDOW_HEIGHT) - (mouse->getMouseState().Y.abs))/PIXELS_PER_METER);
			
			//attack
			setAttackAction();
			m_toggleTime=ntime;
			return;
		}
	}

	m_avatarModel->setAction(AvatarModel::AvatarAction::AVATAR_ACTION_IDLE);
	
}

bool PlayerLogicCalculator::checkIfValidMoveRequest(int tileClickedX, int tileClickedY)
{
	
	//check for solidity of clicked tile
	std::vector<LevelModel::LayerInfo>::const_iterator layerIt = m_levelModel->getLayers().begin();

	while( layerIt != m_levelModel->getLayers().end())
	{
			if(layerIt->solidityMap[ tileClickedX + ((tileClickedY)* (int)layerIt->width) ] == 9)	return false;
			layerIt++;
	}
	
	return true;
}


bool PlayerLogicCalculator::searchPath(int finalDestinationX, int finalDestinationY)
{
	//delete the possible destinations from a previous search
	if(m_destinations.begin()!=m_destinations.end())m_destinations.clear();

	AStarSearch<MapSearchNode> astarsearch;

	int avatarTileX = m_avatarModel->getTerrainPosition()[0]*PIXELS_PER_METER/m_levelModel->getTileSetTileWidth();
	int avatarTileY = m_avatarModel->getTerrainPosition()[1]*PIXELS_PER_METER/m_levelModel->getTileSetTileHeight();

	std::vector<LevelModel::LayerInfo>::const_iterator layerIt = m_levelModel->getLayers().begin();

	// Create a start state
	MapSearchNode nodeStart;
	nodeStart.SetMap(layerIt->solidityMap,(int)layerIt->width,(int)layerIt->height);
	// Define the goal state
	MapSearchNode nodeEnd;
	nodeEnd.SetMap(layerIt->solidityMap,(int)layerIt->width,(int)layerIt->height);

	nodeStart.x = avatarTileX;
	nodeStart.y = avatarTileY;				
	nodeEnd.x = finalDestinationX;						
	nodeEnd.y = finalDestinationY; 

		
	// Set Start and goal states	
	astarsearch.SetStartAndGoalStates( nodeStart, nodeEnd );


	unsigned int SearchState;
	
		do
		{
			SearchState = astarsearch.SearchStep();
		}
		while( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SEARCHING );
		int steps = 0;

		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_SUCCEEDED )
		{
			//cout << "Search found goal state\n";

				MapSearchNode *node = astarsearch.GetSolutionStart();

	#if DISPLAY_SOLUTION
				cout << "Displaying solution\n";
	#endif

			//	node->PrintNodeInfo();
				for( ;; )
				{
					node = astarsearch.GetSolutionNext();
					//add all destinations
				
					
					
					if( !node )
					{
						break;
					}
					
				
					m_destinations.push_back(std::pair<int,int>(node->x,node->y));

				//	node->PrintNodeInfo();
					steps ++;
				
				};

				//cout << "Solution steps " << steps << endl;

				// Once you're done with the solution you can free the nodes up
				astarsearch.FreeSolutionNodes();
	
		}
		
		astarsearch.EnsureMemoryFreed();
		
		if( SearchState == AStarSearch<MapSearchNode>::SEARCH_STATE_FAILED ) 
		{
			std::cout<<"Search Failed!!!" << std::endl;
			
			return false;
		}
		else
		{
			if(steps == 0) //we are at the destination already
			{
				return false;
			}
			else
			{
				return true;
			}
			
		}

}

void PlayerLogicCalculator::startWalkingPath()
{
	
	m_walkingFoundPath = true;
	m_visitedNodes = 0;
	computeAndSetDirection(m_destinations[0].first*m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER + (m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)/2,m_destinations[0].second*m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER  + (m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER)/2);
	setMoveAction();
}

void PlayerLogicCalculator::keepWalkingPath()
{
	float avatarX = m_avatarModel->getTerrainPosition()[0];
	float avatarY= m_avatarModel->getTerrainPosition()[1];
	
	float nodeX = m_destinations[m_visitedNodes].first*m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER + (m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)/2;
	float nodeY = m_destinations[m_visitedNodes].second*m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER + (m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER)/2 ;
	
	float  distanceToDestination = std::sqrtf( (avatarX-nodeX)*(avatarX-nodeX) + (avatarY-nodeY)*(avatarY-nodeY) );
	
	//0.15 has been found empiracally to be a good value
	if(distanceToDestination  < 0.15)
	{
		//if arrived and in last node then end walking
		if(m_destinations[m_visitedNodes].first == m_destinations[m_destinations.size()-1].first && m_destinations[m_visitedNodes].second == m_destinations[m_destinations.size()-1].second)
		{
			endWalkingPath();
			return;
		}
		else
		{
		
			//set dir to next node
			m_visitedNodes++;
			//set course for the following node
			computeAndSetDirection(m_destinations[m_visitedNodes].first*m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER + (m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)/2,m_destinations[m_visitedNodes].second*m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER + + (m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER)/2 );
			//and move!
			setMoveAction();
		}
	}
	else
	{
		//keep moving in same direction
		computeAndSetDirection(m_destinations[m_visitedNodes].first*m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER + (m_levelModel->getTileSetTileWidth()/PIXELS_PER_METER)/2,m_destinations[m_visitedNodes].second*m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER + + (m_levelModel->getTileSetTileHeight()/PIXELS_PER_METER)/2);
		setMoveAction();
	}
}

void PlayerLogicCalculator::endWalkingPath()
{
	m_walkingFoundPath = false;
	m_visitedNodes = 0;
	m_destinations.clear();
}

void PlayerLogicCalculator::interactWithEnemies()
{
	//first we clean up the vector of forbidden directions
	m_forbiddenDirections.clear();

	//interact with Enemies
	std::map<int,AvatarModel*>::const_iterator enemyIt = m_levelModel->getEnemyModels().begin();
	while(enemyIt != m_levelModel->getEnemyModels().end())
	{
		//check collision
		if(collides(enemyIt->second->getRect()))
		{
			//compute the direction in which we cannot move
			//and add it to the vector of forbidden directions
			m_forbiddenDirections.push_back(computeDirection(enemyIt->second->getTerrainPosition()[0],enemyIt->second->getTerrainPosition()[1]));

			//diminish the life of the player by 1.
			//09/09/12 TO_DO this should depend on the type of enemy!
			m_avatarModel->setLifePoints(m_avatarModel->getLifePoints()-0.1);

		}
		enemyIt++;

	}
}

void PlayerLogicCalculator::correctStepsDueToEnemyCollisions()
{
	float stepX;
	float stepY;
	
	m_avatarModel->getStep(&stepX,&stepY);

	std::vector<std::pair<float,float>>::iterator forbiddenDirectionIt = m_forbiddenDirections.begin();
	while(forbiddenDirectionIt != m_forbiddenDirections.end() )
	{
		//correct stepX
		if(stepX > 0 && forbiddenDirectionIt->first > 0 )
		{
			stepX -= forbiddenDirectionIt->first;
			if(stepX<0) stepX = 0;
		}
		else if (stepX < 0 && forbiddenDirectionIt->first < 0 )
		{
			stepX -= forbiddenDirectionIt->first;
			if(stepX>0) stepX = 0;
		}

		//correct stepY
		if(stepY > 0 && forbiddenDirectionIt->second > 0 )
		{
			stepY -= forbiddenDirectionIt->second;
			if(stepY<0) stepY = 0;
		}
		else if (stepY < 0 && forbiddenDirectionIt->second < 0 )
		{
			stepY -= forbiddenDirectionIt->second;
			if(stepY>0) stepY = 0;
		}

		forbiddenDirectionIt++;
	}
		m_avatarModel->setStep(stepX,stepY);
}