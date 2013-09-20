#include "ActionManager.h"
#include "Core.h"

ActionManager::ActionManager(void)
{
}

ActionManager::~ActionManager(void)
{
}

void ActionManager::init(typeplayercontrol control[2])
{
	playertype[0]=control[0];
	playertype[1]=control[1];
	keylimit=2;
	setfirstkeys();
	for (int i=0;i<keylimit;i++)
	{
		playeractions[i].up=false;
		playeractions[i].down=false;
		playeractions[i].left=false;
		playeractions[i].right=false;
	
		playeractions[i].punch=false;
		playeractions[i].kick=false;
		playeractions[i].defense=false;

		playeractions[i].megapunch=false;
		playeractions[i].deathray=false;
	}
}

void ActionManager::update(float timeElapsed)
{
	for (int i=0;i<keylimit;i++)
	{
		if (playertype[i]==keyboardcontrol)
		{
			readkeyinput(timeElapsed,i);
		}
		else if (playertype[i]==networkcontrol)
		{
			readnetinput(timeElapsed,i);
		}
	}
}

void ActionManager::readkeyinput(float timeElapsed,int index)
{
	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();

	if (index==0)
	{
		setfirstkeys();
	}
	else 
	{
		setsecondkeys();
	}
	
	playeractions[index].up=keyboard->isKeyDown(up_KC);
	playeractions[index].down=keyboard->isKeyDown(down_KC);
	playeractions[index].left=keyboard->isKeyDown(left_KC);
	playeractions[index].right=keyboard->isKeyDown(right_KC);
	
	playeractions[index].punch=keyboard->isKeyDown(punch_KC);
	playeractions[index].kick=keyboard->isKeyDown(kick_KC);
	playeractions[index].defense=keyboard->isKeyDown(defense_KC);

	playeractions[index].megapunch=keyboard->isKeyDown(megapunch_KC);
	playeractions[index].deathray=keyboard->isKeyDown(deathray_KC);	
}

void ActionManager::readnetinput(float timeElapsed, int index)
{
	//TODO
}

void ActionManager::setplayeractions(int index, actions inputplayeractions)
{
		playeractions[index].up=inputplayeractions.up;
		playeractions[index].down=inputplayeractions.down;
		playeractions[index].left=inputplayeractions.left;
		playeractions[index].right=inputplayeractions.right;
	
		playeractions[index].punch=inputplayeractions.punch;
		playeractions[index].kick=inputplayeractions.kick;
		playeractions[index].defense=inputplayeractions.defense;

		playeractions[index].megapunch=inputplayeractions.megapunch;
		playeractions[index].deathray=inputplayeractions.deathray;
}

void ActionManager::setfirstkeys()
{
	megapunch_KC=OIS::KC_LSHIFT; 
	punch_KC=OIS::KC_LCONTROL;
	up_KC=OIS::KC_SPACE;
	kick_KC=OIS::KC_RSHIFT;
	left_KC=OIS::KC_LEFT;
	defense_KC=OIS::KC_UP; 
	right_KC=OIS::KC_RIGHT;
	down_KC=OIS::KC_DOWN;
	//no defino deathray porque no tengo

	/*
	up_KC=OIS::KC_I;
	down_KC=OIS::KC_K;
	left_KC=OIS::KC_J;
	right_KC=OIS::KC_L;

	punch_KC=OIS::KC_D;
	kick_KC=OIS::KC_S;

	megapunch_KC=OIS::KC_E;
	deathray_KC=OIS::KC_W;
	
	defense_KC=OIS::KC_A;
	*/
}

void ActionManager::setsecondkeys()
{

	megapunch_KC=OIS::KC_Z;
	punch_KC=OIS::KC_X;
	up_KC=OIS::KC_V;
	kick_KC=OIS::KC_M;
	left_KC=OIS::KC_G;
	defense_KC=OIS::KC_Y;
	right_KC=OIS::KC_J;
	down_KC=OIS::KC_H;
	
	/*
	up_KC=OIS::KC_UP;
	down_KC=OIS::KC_DOWN;
	left_KC=OIS::KC_LEFT;
	right_KC=OIS::KC_RIGHT;
	
	punch_KC=OIS::KC_NUMPAD1;
	kick_KC=OIS::KC_NUMPAD2;

	megapunch_KC=OIS::KC_NUMPAD4;
	deathray_KC=OIS::KC_NUMPAD5;
	
	defense_KC=OIS::KC_NUMPAD3;
	*/
}

