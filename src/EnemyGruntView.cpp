#include "EnemyGruntView.h"
#include "Core.h"
#include "EnemyStaticModel.h"

void EnemyGruntView::initView(AvatarModel* avatarModel)

{	m_avatarModel = avatarModel;

	//Obtain the atlas key looking up where the mesh is. Could be any mesh.
	m_atlasKey = Core::singleton().textureManager().findAtlas("grunt-walk-side-0");

	//MOVE

	//set anim for lateral movement
	addAnim("walk-side-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-side-0"));
	addAnim("walk-side-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-side-1"));
	addAnim("walk-side-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-side-2"));
	addAnim("walk-side-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-side-3"));
	addAnim("walk-side-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-side-4"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT, "walk-side-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_LEFT, true);
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT, "walk-side-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_RIGHT, false);

	//anim for lateral and upwards
	addAnim("walk-diago-up-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-up-0"));
	addAnim("walk-diago-up-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-up-1"));
	addAnim("walk-diago-up-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-up-2"));
	addAnim("walk-diago-up-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-up-3"));
	addAnim("walk-diago-up-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-up-4"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT, "walk-diago-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_LEFT, true);

	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT, "walk-diago-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP_RIGHT, false);

	//lateral and downwards
	addAnim("walk-diago-down-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-down-0"));
	addAnim("walk-diago-down-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-down-1"));
	addAnim("walk-diago-down-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-down-2"));
	addAnim("walk-diago-down-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-down-3"));
	addAnim("walk-diago-down-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-diago-down-4"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT, "walk-diago-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_LEFT, true);

	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT, "walk-diago-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN_RIGHT, false);

	//up
	addAnim("walk-up-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-up-0"));
	addAnim("walk-up-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-up-1"));
	addAnim("walk-up-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-up-2"));
	addAnim("walk-up-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-up-3"));
	addAnim("walk-up-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-up-4"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP, "walk-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_UP, false);

	//down
	addAnim("walk-down-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-down-0"));
	addAnim("walk-down-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-down-1"));
	addAnim("walk-down-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-down-2"));
	addAnim("walk-down-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-down-3"));
	addAnim("walk-down-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-walk-down-4"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN, "walk-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN, EnemyStaticModel::MOVE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN, 5);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_MOVE_DOWN, false);

	//ATTACK

	//set anim for lateral attak
	addAnim("attack-side-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-side-0"));
	addAnim("attack-side-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-side-1"));
	addAnim("attack-side-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-side-2"));
	addAnim("attack-side-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-side-3"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT, "attack-side-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_LEFT, true);
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT, "attack-side-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_RIGHT, false);

	//anim for lateral and upwards attack
	addAnim("attack-diago-up-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-diago-up-0"));
	addAnim("attack-diago-up-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-diago-up-1"));
	addAnim("attack-diago-up-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-diago-up-2"));
	addAnim("attack-diago-up-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-diago-up-3"));
	
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT, "attack-diago-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_LEFT, true);

	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT, "attack-diago-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP_RIGHT, false);

	//lateral and downwards attack
	addAnim("attack-diago-down-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-diago-down-0"));
	addAnim("attack-diago-down-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-diago-down-1"));
	addAnim("attack-diago-down-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-diago-down-2"));
	addAnim("attack-diago-down-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-diago-down-3"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT, "attack-diago-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_LEFT, true);

	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT, "attack-diago-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN_RIGHT, false);

	//upwards attack
	addAnim("attack-up-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-up-0"));
	addAnim("attack-up-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-up-1"));
	addAnim("attack-up-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-up-2"));
	addAnim("attack-up-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-up-3"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP, "attack-up-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_UP, false);

	//down
	addAnim("attack-down-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-down-0"));
	addAnim("attack-down-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-down-1"));
	addAnim("attack-down-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-down-2"));
	addAnim("attack-down-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-attack-down-3"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN, "attack-down-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN, EnemyStaticModel::ATTACK_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN, 4);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_ATTACK_DOWN, false);

	//DIE
	addAnim("dead-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-dead-0"));
	addAnim("dead-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-dead-1"));
	addAnim("dead-2", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-dead-2"));
	addAnim("dead-3", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-dead-3"));
	addAnim("dead-4", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-dead-4"));
	addAnim("dead-5", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("grunt-dead-5"));
	setAnimString(AvatarModel::AvatarState::AVATAR_STATE_DIE, "dead-");
	setAnimTimeout(AvatarModel::AvatarState::AVATAR_STATE_DIE, EnemyStaticModel::DIE_TIMEOUT);
	setNumAnim(AvatarModel::AvatarState::AVATAR_STATE_DIE, 6);
	setAnimFlipped(AvatarModel::AvatarState::AVATAR_STATE_DIE, false);

	setAnim("walk-side-0");
	m_avatarModel->setPixelWidth(m_curAnim->width());
	m_avatarModel->setPixelHeight(m_curAnim->height());
	 
}
