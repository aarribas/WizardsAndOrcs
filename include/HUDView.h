#pragma once
#include "PlayerModel.h"
#include "FreeType.h"

class HUDView
{
public:

	HUDView();
	~HUDView();
	void init(PlayerModel* playerModel);
	void draw();
	void switchVisibility(){m_visibility = !m_visibility;}

private:
	PlayerModel* m_playerModel;
	bool m_visibility;

};