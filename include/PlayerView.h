#pragma once
#include "AvatarView.h"
#include "PlayerModel.h" 

class PlayerView : public AvatarView
{	
public:
	void initView(AvatarModel* avatarModel);
};