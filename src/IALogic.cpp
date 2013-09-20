#include "IALogic.h"


IALogic::IALogic():	m_timeout(0)

{
	int P[4][4]={
		{60,30,20,10}, //70% attach, 30 % defense/movement where movement is 20% 
		{70,40,20,10},//60% attach, 40 % defense/movement where movement is 20% 
		{75,50,20,10},//40% attach, 60 % defense/movement where movement is 20%
		{80,60,20,10},//30% attach, 70 % defense/movement where movement is 20%
	};



	memcpy(m_commonThresholds, P, 20);

	m_timeout = 0;
	m_approach = true;


}
IALogic::~IALogic()
{
}
void IALogic::computeNextAction(const float elapsedTime, AvatarEntity* avatar ,AvatarLogicInfo avatarLogicInfo)
{

	ActionManager::actions actions;
	actions.deathray = false;
	actions.defense = false;
	actions.down = false;
	actions.kick = false;
	actions.left = false;
	actions.megapunch = false;
	actions.punch = false;
	actions.right = false;
	actions.up = false;


	//approach if enemy is far away
	if(m_approach == true && avatarLogicInfo.distance <= 5)
	{
		m_approach = false;
	}
	else if (m_approach == true && avatarLogicInfo.distance > 5)
	{
		if(avatar->isOnLeft())
		{
			//avatar->setAction(MOVE_RIGHT_ACT);
			actions.right =true;
		}
		else
		{
			//avatar->setAction(MOVE_LEFT_ACT);
			actions.left =true;
		}
		Core::singleton().actionManager().setplayeractions(1,actions);
		return;
	}


	if(avatarLogicInfo.distance > 50) //too simple - improve
	{
		m_approach = true;
		return;
	}


	int iavatar_state ;
	int  enemy_state;

	float iavatar_hitPoints ;
	float  enemy_hitPoints;

	//encode the states and the hitPoints depending on the side of our ia avatar
	if(avatar->isOnLeft() && avatarLogicInfo.avatar1_isOnLeft)
	{
		iavatar_state = avatarLogicInfo.avatar1_state;
		enemy_state = avatarLogicInfo.avatar2_state;
		iavatar_hitPoints = avatarLogicInfo.avatar1_hitPoints;
		enemy_hitPoints = avatarLogicInfo.avatar2_hitPoints;
	}
	else
	{
		iavatar_state = avatarLogicInfo.avatar2_state;
		enemy_state = avatarLogicInfo.avatar1_state;
		iavatar_hitPoints = avatarLogicInfo.avatar2_hitPoints;
		enemy_hitPoints = avatarLogicInfo.avatar1_hitPoints;
	}

	int ThresholdRow = 0;

	//compute the row applicable //the higher the row the more defensive and less agressive
	if ( iavatar_hitPoints >75)
	{
		//nothing to do <-> apply the most aggresive Pset
	}
	else if (iavatar_hitPoints > 50 && iavatar_hitPoints <= 75)
	{
		ThresholdRow = 1;

		if(enemy_hitPoints <75)
		{
			ThresholdRow = 0; // we get more aggresive if the enemy is weak
		}
	}
	else if (iavatar_hitPoints > 25 && iavatar_hitPoints <= 50)
	{
		ThresholdRow  = 2;

		if(enemy_hitPoints <75)
		{
			ThresholdRow  = 1; // we get more aggresive if the enemy is weak
		}
		else if(enemy_hitPoints <= 50)
		{
			ThresholdRow  = 0; //much more aggresive
		}
	}
	else
	{
		ThresholdRow  = 3;
		if(enemy_hitPoints <75)
		{
			ThresholdRow  = 2; // we get more aggresive if the enemy is weak
		}
		else if(enemy_hitPoints > 25 && enemy_hitPoints <= 50)
		{
			ThresholdRow  = 1; //much more aggresive
		}
		else
		{
			ThresholdRow  = 0;
		}
	}


	//if a timeout has been set we keep executing the same action (for move and DEFENSE)
	if(m_timeout > 0)
	{
		m_timeout-=elapsedTime;
		if (avatarLogicInfo.distance <= 0 && avatarLogicInfo.colliding == true)
		{
			//stop moving regardless of the timeout if there is a collision when walking towards the player 
			//avatar->setAction(IDLE_ACT);
			actions.deathray = false;
			actions.defense = false;
			actions.down = false;
			actions.kick = false;
			actions.left = false;
			actions.megapunch = false;
			actions.punch = false;
			actions.right = false;
			actions.up = false;
			Core::singleton().actionManager().setplayeractions(1,actions);
			m_last_actions = actions;
			m_timeout = 0;
		}
		else
		{
			//otherwise keep executing the same actions (equivalent to keeping the avatar in one state)
			//avatar->setAction(m_last_action); 
			Core::singleton().actionManager().setplayeractions(1,m_last_actions);
		}
	}
	else
	{

		//generate random number and compare to probability boundaries
		int rnd_seed = (int) (rand()% 100);
		if(m_commonThresholds[ThresholdRow ][0]< rnd_seed )
		{
			//KICK
			//if(iavatar_state  == AvatarEntity::IDLE)newAction = KICK_ACT;
			actions.kick = true;
			Core::singleton().actionManager().setplayeractions(1,actions);
		}
		else if (m_commonThresholds[ThresholdRow ][1]< rnd_seed  && rnd_seed<= m_commonThresholds[ThresholdRow ][0])
		{
			//PUNCH
			//if(iavatar_state  == AvatarEntity::IDLE)newAction =PUNCH_ACT;
			actions.punch = true;
			Core::singleton().actionManager().setplayeractions(1,actions);
		}
		/*else if (Probs[Pset][2]< rnd_seed  && rnd_seed<= Probs[Pset][1])
		{
		//JAB
		if(iavatar_state  == AvatarEntity::IDLE)newAction = JAB_ACT;
		}*/
		else if (m_commonThresholds[ThresholdRow ][2]< rnd_seed  && rnd_seed<= m_commonThresholds[ThresholdRow ][1])
		{
			//JAB
			/*if(iavatar_state  == AvatarEntity::IDLE )
			{
			newAction = DEFENSE_ACT;
			m_timeout = 0.15;
			}*/
			actions.defense = true;
			m_timeout = 0.15;
			Core::singleton().actionManager().setplayeractions(1,actions);
		}
		else if (m_commonThresholds[ThresholdRow ][3]< rnd_seed  && rnd_seed<= m_commonThresholds[ThresholdRow ][2])
		{
			if(avatarLogicInfo.colliding == false)
			{
				//if not colliding simply move in the expected direction
				//newAction = MOVE_RIGHT_ACT;
				//m_timeout = 0.25;
				actions.right = true;
				m_timeout = 0.25;
				Core::singleton().actionManager().setplayeractions(1,actions);
			}
			else
			{
				if(avatar->isOnLeft())
				{
					//if coming from the left side and colliding => do not move to the right further

				}
				else
				{  //if colliding and on the right side, we DEFENSE automatically in case of attack 
					//otherwise just retreat
					//newAction = MOVE_RIGHT_ACT;
					//m_timeout = 0.25;
					actions.right = true;
					m_timeout = 0.25;
					Core::singleton().actionManager().setplayeractions(1,actions);
				}
			}

		}
		else if (rnd_seed <= m_commonThresholds[ThresholdRow ][3] )
		{
			//MOVE_LEFT
			if(avatarLogicInfo.colliding == false)
			{
				//if not colliding simply move in the expected direction
				//newAction = MOVE_LEFT_ACT;
				//m_timeout = 0.25;
				actions.left = true;
				m_timeout = 0.25;
				Core::singleton().actionManager().setplayeractions(1,actions);
			}
			else
			{
				if(!avatar->isOnLeft())
				{
					//if coming from the right side and colliding => do not move to the left further

				}
				else
				{
					//otherwise just retreat
					//newAction = MOVE_LEFT_ACT;
					//m_timeout = 0.25;
					actions.left = true;
					m_timeout = 0.25;
					Core::singleton().actionManager().setplayeractions(1,actions);
				}
			}


		}
		m_last_actions = actions; 
		//avatar->setAction(newAction);
		Core::singleton().actionManager().setplayeractions(1,actions);
	}

}
