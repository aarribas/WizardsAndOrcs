#include "EnemyStaticView.h"
#include "Core.h"
#include "EnemyStaticModel.h"

void EnemyStaticView::initView(AvatarModel* avatarModel)

{	m_avatarModel = avatarModel;

	//Obtain the atlas key looking up where the mesh is. Could be any mesh.
	m_atlasKey = Core::singleton().textureManager().findAtlas("mage-walk-side-0");

	//MOVE

	//set anim for lateral movement
	addAnim("walk-side-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-side-0"));
	addAnim("walk-side-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-side-1"));
	addAnim("walk-side-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-side-2"));
	addAnim("walk-side-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-side-3"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT, "walk-side-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT, true);
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT, "walk-side-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT, false);

	//anim for lateral and upwards
	addAnim("walk-diago-up-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-up-0"));
	addAnim("walk-diago-up-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-up-1"));
	addAnim("walk-diago-up-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-up-2"));
	addAnim("walk-diago-up-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-up-3"));
	addAnim("walk-diago-up-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-up-4"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT, "walk-diago-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT, true);

	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT, "walk-diago-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT, false);

	//lateral and downwards
	addAnim("walk-diago-down-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-down-0"));
	addAnim("walk-diago-down-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-down-1"));
	addAnim("walk-diago-down-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-down-2"));
	addAnim("walk-diago-down-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-down-3"));
	addAnim("walk-diago-down-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-diago-down-4"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT, "walk-diago-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT, true);

	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT, "walk-diago-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT, false);

	//up
	addAnim("walk-up-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-up-0"));
	addAnim("walk-up-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-up-1"));
	addAnim("walk-up-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-up-2"));
	addAnim("walk-up-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-up-3"));
	addAnim("walk-up-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-up-4"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP, "walk-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP, false);

	//down
	addAnim("walk-down-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-down-0"));
	addAnim("walk-down-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-down-1"));
	addAnim("walk-down-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-down-2"));
	addAnim("walk-down-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-walk-down-3"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN, "walk-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN, false);

	//ATTACK

	//set anim for lateral attak
	addAnim("cast-side-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-side-0"));
	addAnim("cast-side-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-side-1"));
	addAnim("cast-side-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-side-2"));
	addAnim("cast-side-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-side-3"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT, "cast-side-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT, true);
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT, "cast-side-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT, false);

	//anim for lateral and upwards attack
	addAnim("cast-diago-up-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-diago-up-0"));
	addAnim("cast-diago-up-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-diago-up-1"));
	addAnim("cast-diago-up-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-diago-up-2"));
	addAnim("cast-diago-up-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-diago-up-3"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT, "cast-diago-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT, true);

	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT, "cast-diago-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT, false);

	//lateral and downwards attack
	addAnim("cast-diago-down-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-diago-down-0"));
	addAnim("cast-diago-down-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-diago-down-1"));
	addAnim("cast-diago-down-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-diago-down-2"));
	addAnim("cast-diago-down-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-diago-down-3"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT, "cast-diago-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT, true);

	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT, "cast-diago-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT, false);

	//upwards attack
	addAnim("cast-up-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-up-0"));
	addAnim("cast-up-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-up-1"));
	addAnim("cast-up-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-up-2"));
	addAnim("cast-up-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-up-3"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP, "cast-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP, false);

	//down
	addAnim("cast-down-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-down-0"));
	addAnim("cast-down-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-down-1"));
	addAnim("cast-down-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-down-2"));
	addAnim("cast-down-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-cast-down-3"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN, "cast-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN, false);

	//DIE
	addAnim("dead-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-dead-0"));
	addAnim("dead-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-dead-1"));
	addAnim("dead-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-dead-2"));
	addAnim("dead-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-dead-3"));
	addAnim("dead-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("mage-dead-4"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_DIE, "dead-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_DIE, EnemyStaticModel::DIE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_DIE, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_DIE, false);

	setAnim("walk-side-0");
	m_avatarModel->setPixelWidth(m_curAnim->width());
	m_avatarModel->setPixelHeight(m_curAnim->height());
	 
}
