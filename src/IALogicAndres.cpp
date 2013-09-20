#include "IALogicAndres.h"
#include <time.h>

int IALogicAndres::m_commonThresholds[4][4]={
	{60,30,20,10}, //70% attack, 30 % defense/movement where movement is 20% 
	{70,40,20,10},//60% attack, 40 % defense/movement where movement is 20% 
	{75,50,20,10},//40% attack, 60 % defense/movement where movement is 20%
	{80,60,20,10},//30% attack, 70 % defense/movement where movement is 20%
};

int IALogicAndres::m_fullThresholds[4][7]={
	{30,15,10,8,6,2,0}, 
	{35,20,15,8,6,2,0}, 
	{40,25,20,8,6,2,0}, 
	{45,30,25,8,6,2,0} 
};

IALogicAndres::IALogicAndres()
{
}
IALogicAndres::~IALogicAndres()
{
}

void  IALogicAndres::Init(int PlayerId, bool CommonMovesOnly, int Difficulty, const Vector4 &Position, InterfaceLogicInfo* LogicInfo)
{
	m_commonMovesOnly = CommonMovesOnly;
	m_playerId = PlayerId;
	m_difficulty = Difficulty;
	m_position = Position;
	m_logicInfo = LogicInfo;

	//compute the player Id of the enemy
	if(m_playerId == 0)
	{
		m_enemyId = 1;
	}
	else
	{
		m_enemyId = 0;
	}



	m_timeout = 0;
	m_approach = true;
	m_currentRound = -1;
	m_defensiveness = 0;
	m_previous_player_life = m_logicInfo->GetPlayerLife(m_playerId);

	srand ( time(NULL) );
}

void  IALogicAndres::Update(float timeElapsed)
{
	//idle by default
	m_actions.deathray = false;
	m_actions.defense = false;
	m_actions.down = false;
	m_actions.kick = false;
	m_actions.left = false;
	m_actions.megapunch = false;
	m_actions.punch = false;
	m_actions.right = false;
	m_actions.up = false;

	if(!moveCloserToEnemyWhenRequired())
	{
		adaptDefensivenessToPlayersLife();
		adaptDefensivenessToRoundTime();
		computeNextActions(timeElapsed);
	}


}

void IALogicAndres::computeNextActions(float timeElapsed)
{
	//if a timeout has been set we probably have to keep executing the same actions
	if(m_timeout > 0)
	{
		m_timeout-= timeElapsed;
		if (m_logicInfo->GetDistanceBetweenPlayers()<= 0 && m_logicInfo->GetCollision())
		{
			//stop moving regardless of the timeout if there is a collision when walking towards the player
			//make sure we go idle
			m_actions.deathray = false;
			m_actions.defense = false;
			m_actions.down = false;
			m_actions.kick = false;
			m_actions.left = false;
			m_actions.megapunch = false;
			m_actions.punch = false;
			m_actions.right = false;
			m_actions.up = false;
			Core::singleton().actionManager().setplayeractions(m_playerId,m_actions);
			m_last_actions = m_actions;
			m_timeout = 0;
		}
		else
		{
			//otherwise keep executing the last actions (equivalent to keeping the avatar in one state)
			Core::singleton().actionManager().setplayeractions(m_playerId,m_last_actions);
		}
	}
	else
	{
		//if we lose life too fast then defend for long time! - only for medium-high difficulty
		if(((m_previous_player_life - m_logicInfo->GetPlayerLife(m_playerId))/timeElapsed >25)&& m_difficulty > 0)
		{
			
			m_actions.defense = true;
			m_timeout = 0.30;
			m_last_actions = m_actions; 
			Core::singleton().actionManager().setplayeractions(m_playerId,m_actions);
		}
		else
		{

			if(m_commonMovesOnly)
			{
				computeRandomActions_commonOnly();
			}
			else
			{
				computeRandomActions_full();
			}
		}

		m_previous_player_life = m_logicInfo->GetPlayerLife(m_playerId);
	}
}

void IALogicAndres::computeRandomActions_full()
{


	//generate random number and compare to thresholds 

	int rnd_seed = (int) (rand()% 100);

	if(m_fullThresholds[m_defensiveness][0]< rnd_seed )
	{
		//KICK
		m_actions.kick = true;
	}
	else if (m_fullThresholds[m_defensiveness][1]< rnd_seed  && rnd_seed<= m_fullThresholds[m_defensiveness][0])
	{
		//PUNCH
		m_actions.punch = true;
	}
	else if (m_fullThresholds[m_defensiveness][2]< rnd_seed  && rnd_seed<= m_fullThresholds[m_defensiveness][1])
	{
		//JAB
		m_actions.megapunch = true;
	}
	else if (m_fullThresholds[m_defensiveness ][3]< rnd_seed  && rnd_seed<= m_fullThresholds[m_defensiveness][2])
	{
		//DEFENSE
		m_actions.defense = true;
		m_timeout = 0.15;
	}

	else if (m_fullThresholds[m_defensiveness ][4]< rnd_seed  && rnd_seed<= m_fullThresholds[m_defensiveness][3])
	{
		//LOWER
		m_actions.down = true;
		m_timeout = 0.15;
	}
	else if (m_fullThresholds[m_defensiveness][5]< rnd_seed  && rnd_seed<= m_fullThresholds[m_defensiveness][4])
	{
		if(m_logicInfo->GetCollision() == false)
		{
			//MOVE RIGHT
			m_actions.right = true;
			m_timeout = 0.25;
		}
		else
		{
			if(m_playerId == 0)
			{
				//if coming from the left side and colliding => do not move to the right further

			}
			else
			{  
				//MOVE RIGHT
				m_actions.right = true;
				m_timeout = 0.25;
			}
		}

	}
	else if (m_fullThresholds[m_defensiveness][6]< rnd_seed  && rnd_seed<= m_fullThresholds[m_defensiveness][5])
	{
		//MOVE_LEFT
		if(m_logicInfo->GetCollision()== false)
		{
			m_actions.left = true;
			m_timeout = 0.25;

		}
		else
		{
			if(m_playerId == 1)
			{
				//if coming from the right side and colliding => do not move to the left further

			}
			else
			{
				//MOVE_LEFT
				m_actions.left = true;
				m_timeout = 0.25;
			}
		}
	}
	else if (rnd_seed<= m_fullThresholds[m_defensiveness][6])
	{
		if(m_playerId == 1)
		{
			if(m_logicInfo->GetCollision() == false)
			{
				//JUMP RIGHT
				m_actions.right = true;
				m_actions.up = true;
				m_timeout = 0.75;
			}
			else
			{
				if(m_playerId == 0)
				{
					//if coming from the left side and colliding => do not move to the right further

				}
				else
				{  
					//JUMP RIGHT
					m_actions.right = true;
					m_actions.up = true;
					m_timeout = 0.75;
				}
			}

		}
		else
		{
			//JUMP_LEFT
			if(m_logicInfo->GetCollision()== false)
			{
				m_actions.left = true;
				m_actions.up = true;
				m_timeout = 0.75;
			}
			else
			{
				if(m_playerId == 1)
				{
					//if coming from the right side and colliding => do not move to the left further

				}
				else
				{
					//JUMP_LEFT
					m_actions.left = true;
					m_actions.up = true;
					m_timeout = 0.75;
				}
			}
		}
		
	}
	m_last_actions = m_actions; 
	Core::singleton().actionManager().setplayeractions(m_playerId,m_actions);

}
void IALogicAndres::computeRandomActions_commonOnly()
{

	//generate random number and compare to thresholds 


	int rnd_seed = (int) (rand()% 100);

	if(m_commonThresholds[m_defensiveness][0]< rnd_seed )
	{
		//KICK
		m_actions.kick = true;
	}
	else if (m_commonThresholds[m_defensiveness][1]< rnd_seed  && rnd_seed<= m_commonThresholds[m_defensiveness][0])
	{
		//PUNCH
		m_actions.punch = true;
	}
	else if (m_commonThresholds[m_defensiveness ][2]< rnd_seed  && rnd_seed<= m_commonThresholds[m_defensiveness][1])
	{
		//DEFENSE
		m_actions.defense = true;
		m_timeout = 0.15;

	}
	else if (m_commonThresholds[m_defensiveness][3]< rnd_seed  && rnd_seed<= m_commonThresholds[m_defensiveness][2])
	{
		if(m_logicInfo->GetCollision() == false)
		{
			//MOVE RIGHT
			m_actions.right = true;
			m_timeout = 0.25;
		}
		else
		{
			if(m_playerId == 0)
			{
				//if coming from the left side and colliding => do not move to the right further

			}
			else
			{  
				//MOVE RIGHT
				m_actions.right = true;
				m_timeout = 0.25;
			}
		}

	}
	else if (rnd_seed <= m_commonThresholds[m_defensiveness][3] )
	{
		//MOVE_LEFT
		if(m_logicInfo->GetCollision()== false)
		{
			m_actions.left = true;
			m_timeout = 0.25;
		}
		else
		{
			if(m_playerId == 1)
			{
				//if coming from the right side and colliding => do not move to the left further

			}
			else
			{
				//MOVE_LEFT
				m_actions.left = true;
				m_timeout = 0.25;
			}
		}
	}
	m_last_actions = m_actions; 
	Core::singleton().actionManager().setplayeractions(m_playerId,m_actions);
}

void IALogicAndres::adaptDefensivenessToPlayersLife()
{
	//if we are playing with low difficulty we don´t take players lifes into account
	if(m_difficulty == 0) return;

	m_defensiveness = 0;

	//the higher the defensiveness the more defensive and less agressive
	if ( m_logicInfo->GetPlayerLife(m_playerId) >75)
	{
		//nothing to do <-> apply the most aggresive / less defensive threshold set
	}
	else if ( m_logicInfo->GetPlayerLife(m_playerId) > 50 &&  m_logicInfo->GetPlayerLife(m_playerId)<= 75)
	{
		m_defensiveness = 1;

		//if playing in hard mode we take the enemy´s life into account
		if(m_difficulty == 2)
		{
			if(m_logicInfo->GetPlayerLife(m_enemyId) <75)
			{
				m_defensiveness = 0; // we get more aggresive if the enemy is weak
			}
		}
	}
	else if ( m_logicInfo->GetPlayerLife(m_playerId) > 25 &&  m_logicInfo->GetPlayerLife(m_playerId) <= 50)
	{
		m_defensiveness  = 2;

		//if playing in hard mode we take the enemy´s life into account
		if(m_difficulty == 2)
		{
			if(m_logicInfo->GetPlayerLife(m_enemyId) <75)
			{
				m_defensiveness  = 1; // we get more aggresive if the enemy is weak
			}
			else if(m_logicInfo->GetPlayerLife(m_enemyId) <= 50)
			{
				m_defensiveness  = 0; //much more aggresive
			}
		}
	}
	else
	{
		m_defensiveness  = 3;

		//if playing in hard mode we take the enemy´s life into account
		if(m_difficulty == 2)
		{
			if(m_logicInfo->GetPlayerLife(m_enemyId)  <75)
			{
				m_defensiveness  = 2; // we get more aggresive if the enemy is weak
			}
			else if(m_logicInfo->GetPlayerLife(m_enemyId)  > 25 && m_logicInfo->GetPlayerLife(m_enemyId)<= 50)
			{
				m_defensiveness  = 1; //much more aggresive
			}
			else
			{
				m_defensiveness  = 0;
			}
		}
	}

}
bool IALogicAndres::moveCloserToEnemyWhenRequired()
{
	//certainly need to approach if we are this far
	if(m_logicInfo->GetDistanceBetweenPlayers() > 50) m_approach = true;

	//approach if enemy is far away
	if(m_approach == true && m_logicInfo->GetDistanceBetweenPlayers()<= 5)
	{
		m_approach = false;
	}
	else if (m_approach == true && m_logicInfo->GetDistanceBetweenPlayers() > 5)
	{
		if(m_playerId == 0)
		{
			//approach moving right because we are the left player
			m_actions.right =true;
		}
		else
		{
			//approach moving left because we are the right player
			m_actions.left =true;
		}
		Core::singleton().actionManager().setplayeractions(m_playerId,m_actions);
		return true;
	}
	return false;

}

void IALogicAndres::adaptDefensivenessToRoundTime()
{
	if(m_defensiveness <2 && m_difficulty > 0) //for medium and high difficulty and when not too defensive
	{
		//in the last 10 seconds get defensive if we are winning
		if(m_logicInfo->GetRoundTime() < 10)
		{
			if(m_logicInfo->GetPlayerLife(m_enemyId) < m_logicInfo->GetPlayerLife(m_playerId))
			{
				m_defensiveness = 2;
			}
		}
		if(m_difficulty == 2) //in high get VERY defensive for the last 5 seconds
		{	
			if(m_logicInfo->GetRoundTime() < 5)
			{
				if(m_logicInfo->GetPlayerLife(m_enemyId) < m_logicInfo->GetPlayerLife(m_playerId))
				{
					m_defensiveness = 3;
				}
			}
		}
	}
}

const Vector4 &  IALogicAndres::GetPosition()
{
	return m_position;
}
void  IALogicAndres::SetPosition(const Vector4& position)
{
	m_position = position;
}