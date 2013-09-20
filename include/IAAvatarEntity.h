
#pragma once

#include "AvatarEntity.h"

class IAAvatarEntity
	: public AvatarEntity
{
public:
	
	IAAvatarEntity(int (*func_playSfxSound)(std::string, Vector4), void (*stopSfxsound)(int), bool isOnleft, bool isExternal, bool isStandAlone, bool automatic);
	virtual ~IAAvatarEntity();
	
};