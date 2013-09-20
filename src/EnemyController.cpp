#include "EnemyController.h"

EnemyController::EnemyController()
{
}

EnemyController::~EnemyController()
{
}

void EnemyController::init(LevelModel* levelModel, AvatarView* avatarView, AvatarLogicCalculator* avatarLogicCalculator, int key)
{
	m_avatarModel = levelModel->getEnemyModel(key);
	m_avatarLogicCalculator = avatarLogicCalculator; 
	m_avatarView = avatarView;
	m_avatarView->initView(m_avatarModel);
	updateBasicAvatarMeasurements();

}

void EnemyController::startIdle()
{
	m_avatarModel->setState(AvatarModel::AvatarState::AVATAR_STATE_IDLE);
	m_avatarView->prepareNewAnim();
}

void EnemyController::startDie()
{
	m_avatarModel->setState(AvatarModel::AvatarState::AVATAR_STATE_DIE);
	m_avatarModel->setTimeout(EnemyStaticModel::DIE_TIMEOUT);
	m_avatarView->prepareNewAnim();
}

void EnemyController::startMove(AvatarModel::AvatarState state)
{
	m_avatarModel->setState(state);
	m_avatarModel->setTimeout(EnemyStaticModel::MOVE_TIMEOUT);
	m_avatarView->prepareNewAnim();
}

void EnemyController::startAttack(AvatarModel::AvatarState state)
{
	m_avatarModel->setState(state);
	m_avatarModel->setTimeout(EnemyStaticModel::ATTACK_TIMEOUT);
	m_avatarView->prepareNewAnim();
}
