#include "IAAvatarEntity.h"

#include "MyGL.h"
#include "Core.h"
#include "RectangleMesh.h"

#include <iostream>

IAAvatarEntity::IAAvatarEntity(int (*func_playSfxSound)(std::string, Vector4), void (*func_stopSfxSound)(int), bool isOnLeft, bool isExternal, bool isStandAlone, bool automatic)
{
	startIdle();

	playSfxSound=func_playSfxSound;
	stopSfxSound=func_stopSfxSound;
	m_isOnLeft = isOnLeft;
	m_isExternal = isExternal;
	m_isStandAlone  = isStandAlone;
	m_automatic = automatic;

	if (isOnLeft)
	{
		
		keys[0]=OIS::KC_LSHIFT; //jab
		keys[1]=OIS::KC_LCONTROL; //punch
		keys[2]=OIS::KC_SPACE; //jump
		keys[3]=OIS::KC_RSHIFT; //kick
		keys[4]=OIS::KC_LEFT; //left
		keys[5]=OIS::KC_UP; //up
		keys[6]=OIS::KC_RIGHT; //right
		keys[7]=OIS::KC_DOWN; //lower

	}
	else
	{
		keys[0]=OIS::KC_Z;
		keys[1]=OIS::KC_X;
		keys[2]=OIS::KC_V;
		keys[3]=OIS::KC_M;
		keys[4]=OIS::KC_G;
		keys[5]=OIS::KC_Y;
		keys[6]=OIS::KC_J;
		keys[7]=OIS::KC_H;
	}
}

IAAvatarEntity::~IAAvatarEntity()
{
}

