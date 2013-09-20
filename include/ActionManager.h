#pragma once
#include <iostream>
#include <OIS/OISKeyboard.h>


//El autor de ActionManager es David Jimenez!

class Core;

class ActionManager
{
public:
	struct actions
	{
		bool up, down,left, right;
		bool punch,kick;
		bool defense;
		bool megapunch;
		bool deathray;
	};
	
	enum typeplayercontrol
	{
		keyboardcontrol,
		networkcontrol,
		IAcontrol
	};
private:
    friend class Core;
    ActionManager();
    virtual ~ActionManager();
public:
	void init(typeplayercontrol control[2]);
	void update(float timeElapsed);
	actions getplayeractions(int index) {return playeractions[index];}
	void setplayeractions(int index, actions inputplayeractions);
private:
	void readkeyinput(float timeElapsed, int index);
	void readnetinput(float timeElapsed, int index);
	void setfirstkeys();
	void setsecondkeys();
private:
	actions playeractions[2];
	typeplayercontrol playertype[2];
	OIS::KeyCode up_KC;
	OIS::KeyCode down_KC;
	OIS::KeyCode left_KC;
	OIS::KeyCode right_KC;
	OIS::KeyCode punch_KC;
	OIS::KeyCode kick_KC;
	OIS::KeyCode defense_KC;
	OIS::KeyCode megapunch_KC;
	OIS::KeyCode deathray_KC;
	int keylimit;
};