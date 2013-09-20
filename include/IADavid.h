#pragma once
#include <InterfaceIA.h>

class IA : public InterfaceIA
{
public:
	static const int CLOSE_RANGE;
	static const int MAX_HIT_COUNT;
	static const float IA_UPDATE_RATE;
	static const float MAX_LIFE_RATE;
	static const float DIFFICULTY_UPDATE_RATE;

public:
	IA();
	~IA();
public:
	void Init(int PlayerId, bool CommonMovesOnly, int Difficulty, const Vector4 &Position, InterfaceLogicInfo* LogicInfo);
	void Update(float timeElapsed);
	const Vector4 &GetPosition(){return KnowledgeTable.Position;}
	void SetPosition(const Vector4& position){KnowledgeTable.Position=position;}
private:
	void UpdateKnowledge();
	void EvaluateMainTree();

	//CommonMovesOnly Tree
	void EvaluateCloseRangeTree();
	void EvaluateFarRangeTree();

	//Addaptative difficulty functions
	void AdjustDifficulty();
	void FastLifeLossReaction();

	//Full Mode TREE

	void FullCloseRangeTree();
	void EnemyAttackingTree(int DifficultyFactorIndex);
	void FullFarRangeTree();

	//Action functions CommonMovesOnly==True
	void Idle();
	void Approach();
	void Flee();
	void Punch();
	void Kick();
	void Defense();

	//Action functions CommonMovesOnly==False
	void Lower();
	void Jump();
	void JumpForward();
	void JumpBack();	
	void MegaPunch();
	void DeathRay();

private:
	struct Knowledge
	{
		int PlayerId;
		int Difficulty;
		Vector4 Position;
		Vector4 EnemyPosition;
		bool CommonMovesOnly;
		float Life;
		float EnemyLife;
		int Round;
		float RoundTime;
		InterfaceLogicInfo::State MyState;
		InterfaceLogicInfo::State EnemyState;
		bool Collision;
		float DistanceBetweenPlayers;
		float MinXPos,MaxXPos;
		

	}KnowledgeTable;
	
	InterfaceLogicInfo* pLogicInfo;
	int RandomNumber;
	float IAupdaterate,DifficultyRate;
	int DifficultyFactor[2];
	float PreviousLife;
	int PreviousDifficulty;
	int HitCount;
};