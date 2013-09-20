#include "PlayerController.h"

PlayerController::PlayerController()
{
}

PlayerController::~PlayerController()
{
}

void PlayerController::init(LevelModel* levelModel, AvatarView* playerView)
{
	m_avatarModel = levelModel->getPlayerModel();
	m_avatarLogicCalculator = new PlayerLogicCalculator();
	m_avatarLogicCalculator->init(levelModel,m_avatarModel);
	m_avatarView = playerView;
	m_avatarView->initView(m_avatarModel);
	updateBasicAvatarMeasurements();
}

void PlayerController::startIdle()
{
	m_avatarModel->setState(AvatarModel::AvatarState::AVATAR_STATE_IDLE);
	m_avatarView->prepareNewAnim();
}

void PlayerController::startDie()
{
	m_avatarModel->setState(AvatarModel::AvatarState::AVATAR_STATE_DIE);
	m_avatarModel->setTimeout(PlayerModel::DIE_TIMEOUT);
	m_avatarView->prepareNewAnim();
}

void PlayerController::startMove(AvatarModel::AvatarState state)
{
	m_avatarModel->setState(state);
	m_avatarModel->setTimeout(PlayerModel::MOVE_TIMEOUT);
	m_avatarView->prepareNewAnim();
}

void PlayerController::startAttack(AvatarModel::AvatarState state)
{
	m_avatarModel->setState(state);
	m_avatarModel->setTimeout(PlayerModel::ATTACK_TIMEOUT);
	m_avatarView->prepareNewAnim();
}
