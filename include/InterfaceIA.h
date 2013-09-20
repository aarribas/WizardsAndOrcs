//Interfaz génerica para la IA

#pragma once
#include <InterfaceLogicInfo.h>

class InterfaceIA
{
public:
	virtual void Init(int PlayerId, bool CommonMovesOnly, int Difficulty, const Vector4 &Position, InterfaceLogicInfo* LogicInfo) = 0; 
	//PlayerId puede ser 0 o 1, en base a esto la IA estará a la izquierda (0) o derecha (1)
	//CommonMovesOnly indica si la IA va a luchar contra otra IA y debe utilizar solamente los movimientos comunes en el ActionManager:
	// puñetazo, patada, moverse y defensa.
	//
	//struct actions
	//{
	//											Permisos si CommonMovesOnly==TRUE
	//											=================================================
	//	bool up, down,left, right;				SOLO UNO DE ELLOS PUEDE SER TRUE AL MISMO TIEMPO
	//	bool punch,kick;						PERMITIDO CON LIMITACIONES, SOLO PUEDE USARSE SI (UP==FALSE && DOWN==FALSE)
	//	bool defense;							PERMITIDO CON LIMITACIONES, SOLO PUEDE USARSE SI DOWN==FALSE
	//	bool megapunch;							NO PERMITIDO, PONER SIEMPRE A FALSE
	//	bool deathray;							NO PERMITIDO, PONER SIEMPRE A FALSE
	//};
	//
	// Difficulty puede ser 0 (Easy), 1 (Normal) o 2 (Hard)
	
	virtual void Update(float timeElapsed) = 0;
	//El método Update como mínimo debe llamar a ActionManager.setplayeractions(int index, actions inputplayeractions) cada vez que
	//se ejecuta para generar la salida de la IA.
	//inputplayeractions debe seguir las reglas definidas arriba si CommonMovesOnly==TRUE

	virtual const Vector4 &GetPosition() = 0;
	virtual void SetPosition(const Vector4& position) = 0;
	//GetPosition y SetPosition en principio no deberían hacer falta pero pueden ser útiles.

}; 