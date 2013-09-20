#pragma once
#include "PlayerModel.h"
#include "LevelModel.h"
#include "AvatarLogicCalculator.h"

class PlayerLogicCalculator : public AvatarLogicCalculator
{
public:
	PlayerLogicCalculator();
	~PlayerLogicCalculator();
public:
	void init(LevelModel* levelModel, AvatarModel* avatarModel);
	void computeLogic();
private:
	void processInput();
	bool checkIfValidMoveRequest(int tileClickedX, int tileClickedY);
	void correctStepsDueToEnemyCollisions();
	bool searchPath(int finalDestinationX, int finalDestinationY);	
	void keepWalkingPath();
	void startWalkingPath();
	void endWalkingPath();
	void interactWithEnemies();


private:
	int m_toggleTime;
	bool m_walkingFoundPath;
	std::vector<std::pair<int,int>> m_destinations;
	int m_visitedNodes;
	int contador;
	bool m_searchingPath;
	std::vector<std::pair<float,float>> m_forbiddenDirections;
};