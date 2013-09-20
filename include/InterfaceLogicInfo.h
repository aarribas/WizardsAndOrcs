//Interfaz génerica para la información que necesita la IA del motor de lógica

#pragma once
#include <Vector4.h>

class InterfaceLogicInfo
{
public:
	enum State {
		IDLE,
		PUNCH,
		LOWPUNCH,
		KICK,
		LOWKICK,
		MEGAPUNCH,
		DEATHRAY,
		JUMPING_UP,
		JUMPING_DOWN,
		LOWER,
		AIRATTACK,
		DEFENSE,
		LOWDEFENSE,
		HIT,
		LOWHIT,
		MOVE,
		JAB,
		JUMP
	};

	//Estados que el player puede tener, en caso de CommonMovesOnly==TRUE, solo és válido un subconjunto de ellos aunque los definamos todos.
	
	virtual void Init(bool CommonMovesOnly) = 0;

	virtual const Vector4& GetPosition(int PlayerId) = 0;
	virtual void SetPosition(int PlayerId, const Vector4& Position) = 0;

	virtual float GetPlayerLife(int PlayerId) = 0;
	virtual void SetPlayerLife(int PlayerId, float PlayerLife) = 0;

	virtual int GetRound()=0; //Round 0, 1 o 2
	virtual void SetRound(int Round)=0;

	virtual float GetRoundTime()=0;
	virtual void SetRoundTime(float RoundTime)=0;

	virtual State GetPlayerState(int PlayerId) = 0;
	virtual void SetPlayerState(int PlayerId, State PlayerState) = 0;

	virtual bool GetCollision() = 0;
	virtual void SetCollision(bool Collides) = 0;

	virtual float GetDistanceBetweenPlayers()=0; 
	virtual void SetDistanceBetweenPlayers(float Distance)=0;

	virtual void SetMaxXPos(float MaxXPos)=0;
	virtual float GetMaxXPos()=0;

	virtual void SetMinXPos(float MinXPos)=0;
	virtual float GetMinXPos()=0;

	//Los métodos Set los usa el motor de lógica para poner los datos en cada update
	//Los métodos Get los usa la InterfaceIA para leer los datos que necesita
	

};