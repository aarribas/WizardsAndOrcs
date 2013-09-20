#include "PlayerLogic.h"
#include "Core.h"

PlayerLogic::PlayerLogic()
{
	//define keys for left player
	keysLeftPlayer[0]=OIS::KC_LSHIFT; //jab
	keysLeftPlayer[1]=OIS::KC_LCONTROL; //punch
	keysLeftPlayer[2]=OIS::KC_SPACE; //jump
	keysLeftPlayer[3]=OIS::KC_RSHIFT; //kick
	keysLeftPlayer[4]=OIS::KC_LEFT; //left
	keysLeftPlayer[5]=OIS::KC_UP; 
	keysLeftPlayer[6]=OIS::KC_RIGHT; //right
	keysLeftPlayer[7]=OIS::KC_DOWN; //lower

	//define keys for right player
	keysRightPlayer[0]=OIS::KC_Z;
	keysRightPlayer[1]=OIS::KC_X;
	keysRightPlayer[2]=OIS::KC_V;
	keysRightPlayer[3]=OIS::KC_M;
	keysRightPlayer[4]=OIS::KC_G;
	keysRightPlayer[5]=OIS::KC_Y;
	keysRightPlayer[6]=OIS::KC_J;
	keysRightPlayer[7]=OIS::KC_H;


}

PlayerLogic::~PlayerLogic()
{
}

void PlayerLogic::computeNextAction(const float elapsedTime, AvatarEntity* player , AvatarLogicInfo avatarLogicInfo)
{


	/*OIS::KeyCode *keys;
	//choose the right key set
	if(player->isOnLeft())
	{

		keys=keysLeftPlayer;
	}
	else
	{
		keys=keysRightPlayer;
	}

	int player_state;
	int enemy_state;

	//encode the states
	if(player->isOnLeft() && avatarLogicInfo.avatar1_isOnLeft == true)
	{
		player_state = avatarLogicInfo.avatar1_state;
		enemy_state = avatarLogicInfo.avatar2_state;
	}
	else
	{
		player_state = avatarLogicInfo.avatar2_state;
		enemy_state = avatarLogicInfo.avatar1_state;
	}

	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();
	if(player_state == AvatarEntity::DEFENSE && !keyboard->isKeyDown(keys[5]))	
	{
		player->setAction(IDLE_ACT);
		return;
	}
	if (keyboard->isKeyDown(keys[1])) {
		if(player_state == AvatarEntity::IDLE) player->setAction(PUNCH_ACT);
		return;
	}
	if (keyboard->isKeyDown(keys[0])) {
		if(player_state == AvatarEntity::IDLE) player->setAction(JAB_ACT);
		return;
	}
	if (keyboard->isKeyDown(keys[3])) {
		if(player_state == AvatarEntity::IDLE) player->setAction(KICK_ACT);
		return;
	}
	if  (keyboard->isKeyDown(keys[2]) && keyboard->isKeyDown(keys[6]) )
	{
		if(player->isOnLeft() && avatarLogicInfo.colliding == true)
		{
			//if coming from the left side and colliding => do not move to the right further
		}
		else
		{
			if(player_state == AvatarEntity::IDLE) player->setAction(JUMP_RIGHT_ACT);
		}
		return;
	}
	if  (keyboard->isKeyDown(keys[2]) && keyboard->isKeyDown(keys[4]) )
	{
		if(!player->isOnLeft() && avatarLogicInfo.colliding == true)
		{
			//if coming from the right side and colliding => do not move to the left further
		}
		else
		{
			if(player_state == AvatarEntity::IDLE) player->setAction(JUMP_LEFT_ACT);
		}
		return;
	}
	if (keyboard->isKeyDown(keys[2])) {
		if(player_state == AvatarEntity::IDLE) player->setAction(JUMP_ACT);
		return;
	}
	if (keyboard->isKeyDown(keys[7])) {
		if(player_state == AvatarEntity::IDLE || player_state == AvatarEntity::LOWER) player->setAction(LOWER_ACT);
		return;
	}
	if (keyboard->isKeyDown(keys[5])) {
		if(player_state == AvatarEntity::IDLE || player_state == AvatarEntity::DEFENSE) player->setAction(DEFENSE_ACT);
		return;
	}
	if (keyboard->isKeyDown(keys[4]))
	{
		if(avatarLogicInfo.colliding == false)
		{
			//if not colliding simply move in the expected direction
			player->setAction(MOVE_LEFT_ACT);
		}
		else
		{
			if(!player->isOnLeft())
			{
				//if coming from the right side and colliding => do not move to the left further

			}
			else
			{  

				player->setAction(MOVE_LEFT_ACT);

			}
			return;
		}
	}
	else if (keyboard->isKeyDown(keys[6]))
	{
		if(avatarLogicInfo.colliding == false)
		{
			//if not colliding simply move in the expected direction
			player->setAction(MOVE_RIGHT_ACT);
		}
		else
		{
			if(player->isOnLeft())
			{
				//if coming from the left side and colliding => do not move to the right further

			}
			else
			{  //if colliding and on the right side, we cover automatically in case of attack 

				//otherwise just retreat
				player->setAction(MOVE_RIGHT_ACT);

			}
			return;
		}
	}*/
	
//Core::singleton().actionManager().update(elapsedTime);
	

}