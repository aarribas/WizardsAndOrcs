#include "LogicHelper.h"
#include "BBox.h"

LogicHelper::LogicHelper()
{	
}

void LogicHelper::init(AvatarEntity* avatar1, AvatarEntity* avatar2, BBoxAtlas* bboxAtlas, int difficulty, bool commonOnly, GameInfo* gameInfo)
{
	m_logicInfo.Init(true);
	m_logicInfo.SetMaxXPos(550);
	m_logicInfo.SetMinXPos(0);
	m_avatar1 = avatar1;
	m_avatar2 = avatar2;
	m_bboxAtlas = bboxAtlas;
	m_gameInfo = gameInfo;

	if(commonOnly)
	{
		m_ia_logic_andres.Init(avatar1->getIndex(), true, difficulty, avatar1->terrainPosition(),&m_logicInfo);
		m_ia_logic_david.Init(avatar2->getIndex(), true, difficulty, avatar2->terrainPosition(),&m_logicInfo);
	}
	else
	{
		if(avatar1->isArtificial())
		{
			m_ia_logic_andres.Init(avatar1->getIndex(), false, difficulty, avatar1->terrainPosition(),&m_logicInfo);
		}
		if(avatar2->isArtificial())
		{
			m_ia_logic_andres.Init(avatar2->getIndex(), false, difficulty, avatar2->terrainPosition(),&m_logicInfo);
		}

	}
}

LogicHelper::~LogicHelper()
{
}

void LogicHelper::updateAvatarLogic(const float elapsedTime)
{
	m_elapsedTime = elapsedTime;
	m_collision = false;

	//compute collisions
	computeBBoxCollision();

	//compute hitpoints
	if(m_collision)
	{
		computeHitPoints();
	}

	//populate logic
	populateLogicInfo();

	//update the logic for avatar depending on whether it is IA controlled or not
	computeNextActions();

	//correct positions if overlap and moving
	correctPositions();

}

void LogicHelper::correctPositions()
{
	//correction to avoid overlap
	if(m_collision && 
		(m_avatar1->getState() == AvatarEntity::MOVE 
		|| m_avatar1->getState() == AvatarEntity::JUMP ))
	{
		m_avatar1->goBackDelta();
	}

	if(m_collision && 
		(m_avatar2->getState() == AvatarEntity::MOVE 
		|| m_avatar2->getState() == AvatarEntity::JUMP ))
	{
		m_avatar2->goBackDelta();
	}
}

void LogicHelper::computeNextActions()
{
	//update actions for human controlled players
	Core::singleton().actionManager().update(m_elapsedTime);


	//update actions for AI
	if(m_avatar1->isArtificial() && m_avatar2->isArtificial())
	{
		m_ia_logic_andres.Update(m_elapsedTime);
		m_ia_logic_david.Update(m_elapsedTime);
	}
	else
	{

		if(m_avatar1->isArtificial() || m_avatar2->isArtificial())
		{
			m_ia_logic_andres.Update(m_elapsedTime);
		}
	}
}
void LogicHelper::computeHitPoints()
{
	float avatar1_hitPoints = m_avatar1->getHitPoints();
	float avatar2_hitPoints = m_avatar2->getHitPoints();

	//udpate hitpoints for avatar1 
	if(m_avatar2->getState() == AvatarEntity::KICK 
		|| m_avatar2->getState() == AvatarEntity::JAB 
		|| m_avatar2->getState()  == AvatarEntity::PUNCH)
	{
		if(m_avatar1->getState() == AvatarEntity::DEFENSE)
		{
			//no damage
		}

		else
		{
			if(m_avatar2->getState()== AvatarEntity::KICK)
			{
				avatar1_hitPoints-=1;
			}
			if(m_avatar2->getState() == AvatarEntity::PUNCH)
			{
				avatar1_hitPoints-=0.8;
			}
			if(m_avatar2->getState() == AvatarEntity::JAB)
			{
				avatar1_hitPoints-=0.5;
			}
		}
	}

	//udpate hitpoints for avatar2
	if(m_avatar1->getState() == AvatarEntity::KICK 
		|| m_avatar1->getState() == AvatarEntity::JAB 
		|| m_avatar1->getState()  == AvatarEntity::PUNCH)
	{
		if(m_avatar2->getState()== AvatarEntity::DEFENSE)
		{
			//no damage
		}

		else
		{
			if(m_avatar1->getState()== AvatarEntity::KICK)
			{
				avatar2_hitPoints-=1;
			}
			if(m_avatar1->getState()== AvatarEntity::PUNCH)
			{
				avatar2_hitPoints-=0.8;
			}
			if(m_avatar1->getState() == AvatarEntity::JAB)
			{
				avatar2_hitPoints-=0.5;
			}
		}
	}

	m_avatar1->setHitpoints(avatar1_hitPoints);
	m_avatar2->setHitpoints(avatar2_hitPoints);
}

void LogicHelper::computeBBoxCollision()
{
	//calcula colisiones
	//depende del lado?
	if((m_avatar1->terrainPosition()[0] + m_avatar1->getCurAnimWidth()/2) > (m_avatar2->terrainPosition()[0] - m_avatar2->getCurAnimWidth()/2))
	{
		for(int i = 0; i < (*m_bboxAtlas->m_bbox(m_avatar1->anim())).size(); i++)
		{
			int av1_xorigin = m_avatar1->screenPosition()[0] - m_avatar1->getCurAnimWidth()/2;
			int av1_yorigin = m_avatar1->screenPosition()[1] + m_avatar1->heightCorrection() - m_avatar1->getCurAnimHeight()/2;

			int av1_right = av1_xorigin + (*m_bboxAtlas->m_bbox(m_avatar1->anim()))[i]->m_coords.x2*m_avatar1->getCurAnimWidth();
			int av1_left = av1_xorigin + (*m_bboxAtlas->m_bbox(m_avatar1->anim()))[i]->m_coords.x1*m_avatar1->getCurAnimWidth();
			int av1_bottom = av1_yorigin + (*m_bboxAtlas->m_bbox(m_avatar1->anim()))[i]->m_coords.y1*m_avatar1->getCurAnimWidth();
			int av1_top = av1_yorigin + (*m_bboxAtlas->m_bbox(m_avatar1->anim()))[i]->m_coords.y3*m_avatar1->getCurAnimWidth();

			for(int j = 0; j < (*m_bboxAtlas->m_bbox(m_avatar2->anim())).size(); j++)
			{
				//x coords are inves
				int av2_xorigin = m_avatar2->screenPosition()[0] + m_avatar2->getCurAnimWidth()/2;
				int av2_yorigin = m_avatar2->screenPosition()[1] + m_avatar2->heightCorrection() - m_avatar2->getCurAnimHeight()/2;

				int av2_left = av2_xorigin - (*m_bboxAtlas->m_bbox(m_avatar2->anim()))[j]->m_coords.x2*m_avatar2->getCurAnimWidth();
				int av2_right = av2_xorigin - (*m_bboxAtlas->m_bbox(m_avatar2->anim()))[j]->m_coords.x1*m_avatar2->getCurAnimWidth();
				int av2_bottom = av2_yorigin + (*m_bboxAtlas->m_bbox(m_avatar2->anim()))[j]->m_coords.y1*m_avatar2->getCurAnimWidth();
				int av2_top = av2_yorigin + (*m_bboxAtlas->m_bbox(m_avatar2->anim()))[j]->m_coords.y3*m_avatar2->getCurAnimWidth();

				if (!(av2_left > av1_right 
					|| av2_right < av1_left
					|| av2_top < av1_bottom
					|| av2_bottom > av1_top))
				{

					//a collision has been detected 
					m_collision = true;
					return;
				}
			}
		}

		//after comparing all the bboxes no collision was detected
		m_collision = false;
	}
	else
	{
		//en caso de que no esten suficientemente cerca no hay collision seguro
		m_collision = false;
	}

}

void LogicHelper::setPlayerState(AvatarEntity* avatar)
{
	if(avatar->getState() == AvatarEntity::IDLE)
	{
		m_logicInfo.SetPlayerState(avatar->getIndex(),LogicInfo::State::IDLE);
	}
	else if(avatar->getState() == AvatarEntity::PUNCH)
	{
		m_logicInfo.SetPlayerState(avatar->getIndex(),LogicInfo::State::PUNCH);
	}
	else if(avatar->getState() == AvatarEntity::KICK)
	{
		m_logicInfo.SetPlayerState(avatar->getIndex(),LogicInfo::State::KICK);
	}
	else if(avatar->getState() == AvatarEntity::JAB)
	{
		m_logicInfo.SetPlayerState(avatar->getIndex(),LogicInfo::State::JAB);
	}
	else if(avatar->getState() == AvatarEntity::LOWER)
	{
		m_logicInfo.SetPlayerState(avatar->getIndex(),LogicInfo::State::LOWER);
	}
	else if(avatar->getState() == AvatarEntity::JUMP)
	{
		m_logicInfo.SetPlayerState(avatar->getIndex(),LogicInfo::State::JUMP);
	}
	else if(avatar->getState() == AvatarEntity::MOVE)
	{
		m_logicInfo.SetPlayerState(avatar->getIndex(),LogicInfo::State::MOVE);
	}
	else if(avatar->getState() == AvatarEntity::DEFENSE)
	{
		m_logicInfo.SetPlayerState(avatar->getIndex(),LogicInfo::State::DEFENSE);
	}


}

void LogicHelper::populateLogicInfo()
{

	m_logicInfo.SetCollision(m_collision);

	m_logicInfo.SetPlayerLife(m_avatar1->getIndex(),m_avatar1->getHitPoints());
	m_logicInfo.SetPlayerLife(m_avatar2->getIndex(),m_avatar2->getHitPoints());

	setPlayerState(m_avatar1);
	setPlayerState(m_avatar2);


	m_logicInfo.SetRound(m_gameInfo->round);
	m_logicInfo.SetRoundTime(m_gameInfo->timeleft);

	m_logicInfo.SetPosition(m_avatar1->getIndex(),m_avatar1->terrainPosition());
	m_logicInfo.SetPosition(m_avatar2->getIndex(),m_avatar2->terrainPosition());

	m_logicInfo.SetPlayerLife(m_avatar1->getIndex(),m_avatar1->getHitPoints());
	m_logicInfo.SetPlayerLife(m_avatar1->getIndex(),m_avatar2->getHitPoints());


	if (m_avatar1->isOnLeft())
	{
		m_logicInfo.SetDistanceBetweenPlayers((float) (m_avatar2->terrainPosition()[0]- m_avatar2->getCurAnimWidth()/2) - (m_avatar1->terrainPosition()[0] + m_avatar1->getCurAnimWidth()/2) );
	}
	else
	{
		m_logicInfo.SetDistanceBetweenPlayers((float) (m_avatar1->terrainPosition()[0] - m_avatar1->getCurAnimWidth()/2)  - (m_avatar2->terrainPosition()[0]+ m_avatar2->getCurAnimWidth()/2));
	}

}