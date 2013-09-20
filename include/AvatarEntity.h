//###############################################################################
// INTRODUCCION: AvatarEntity.h
//------------------------------------------------------------------------------
// Este codigo define una entidad Avatar, que seran los personajes jugables de
// nuestro juego. A parte de las funciones estandar que tienen todas las entidades
// (draw y update), definimos un conjunto de funciones para poder tener varias 
// animaciones, funciones para situar un avatar en el espacio, y finalmente
// funciones para controlar las acciones del avatar.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#pragma once

#include "Vector4.h"
#include "UOCInputManager.h"
#include <map>
#include <string>

class RectangleMesh;
class Texture;

enum Action {
		IDLE_ACT,
		PUNCH_ACT,
		LOWER_ACT,
		MOVE_RIGHT_ACT,
		MOVE_LEFT_ACT,
		KICK_ACT,
		JAB_ACT,
		JUMP_ACT,
		JUMP_LEFT_ACT,
		JUMP_RIGHT_ACT,
		DEFENSE_ACT
};

class AvatarEntity
{
public:

	//Estados o acciones del avatar
	enum State {
		IDLE,
		PUNCH,
		LOWER,
		MOVE,
		KICK,
		JAB,
		JUMP,
		DEFENSE
	};

	//Velocidad de movimiento del avatar
	static const float CELERITY;
	
	//Duracion de un puñetazo
	static const float PUNCH_TIMEOUT;

	//Duracion de una patada
	static const float KICK_TIMEOUT;

	//Duracion de un jab
	static const float JAB_TIMEOUT;

	//Duracion de DEFENSE
	static const float DEFENSE_TIMEOUT;
	
	//Duracion de una secuencia completa idle
	static const float IDLE_TIMEOUT;

	//Duracion de una secuencia completa agachado
	static const float LOWER_TIMEOUT;

	//Duracion de una secuencia completa de desplazamiento
	static const float MOVE_TIMEOUT;

	//Duracion de una secuencia completa de salto
	static const float JUMP_TIMEOUT;

	//Puntos de vida
	static const float HIT_POINTS;

public:
	//AvatarEntity(int (*func_playSfxSound)(std::string, Vector4), void (*stopSfxsound)(int));
	AvatarEntity();
	AvatarEntity(int (*func_playSfxSound)(std::string, Vector4), void (*stopSfxsound)(int), bool isOnleft, bool isExternal, bool isStandAlone, bool automatic, int index);
	virtual ~AvatarEntity();

public:
	//Funciones para añadir y seleccionar la animacion del avatar
	//Añadimos una animacion
	void addAnim(const std::string& name, RectangleMesh *mesh);
	//Devolvemos cual es la animacion activa
	const std::string& anim() const { return m_curAnimName; }
	//Activamos que animacion es la activa
	void setAnim(const std::string& name);

	//Funciones para posicionar el elemento en la pantalla
	//Posición sobre el terreno define la posición dentro del mundo virtual
	//Posición sobre la pantalla define la posición de dibujo dentro del Ortho 2D de OpenGL
	void setTerrainPosition(const Vector4& terrainPosition) { m_terrainPosition = terrainPosition; }
	void setScreenPosition(const Vector4& screenPosition) { m_screenPosition = screenPosition; }
	const Vector4& screenPosition() const { return m_screenPosition; }
	const Vector4& terrainPosition() const { return m_terrainPosition; }
	
	//Funcion para dibujar el avatar
	void draw();

	//Función para actualizar el avatar
	void update(const float elapsedTime);

	void updateExternal(std::string message, float value);

	//funcion para obtener HitPoints
	float getHitPoints(){ return m_hitPoints;}
	void reset(float hitPoints){ m_hitPoints = hitPoints; startIdle();m_action = IDLE_ACT;}

	//return whether avatar is supposed to be updater externally or not
	bool isExternal();
	bool isOnLeft();
	bool isArtificial();
	float updateHitPoints(AvatarEntity* enemy);
	float getCurAnimWidth();
	float getCurAnimHeight();
	State getState(){return m_state;}
	float heightCorrection(){ return m_heightCorrection;};
	void setAction(Action action){ m_action = action; };
	void updateState();
	void setHitpoints(float hitpoints){ m_hitPoints = hitpoints; };
	void goBackDelta();
	int getIndex(){return m_index;};

protected:
	//Funciones para actualizar segun la accion que este desarrollando
	void updateIdle(const float elapsedTime);
	void updatePunch(const float elapsedTime);
	void updateJab(const float elapsedTime);
	void updateKick(const float elapsedTime);
	void updateLower(const float elapsedTime);
	void updateMove(const float elapsedTime);
	void updateJump(const float elapsedTime);
	void updateDefense(const float elapsedTime);
	

	//Funciones para iniciar una accion
	void startIdle();
	void startPunch();
	void startJab();
	void startKick();
	void startLower();
	void startMove();
	void startJump();
	void startDefense();
	

protected:
	State m_state;
	std::map<std::string, RectangleMesh*> m_anim;
	std::string m_curAnimName;
	RectangleMesh *m_curAnim;
	Vector4 m_terrainPosition;
	Vector4 m_screenPosition;
	float m_timeout;
	float m_hitPoints;
	float m_direction;
	float m_jump_height;
	int m_moveSoundid, m_lowerSoundid;
	int(*playSfxSound)(std::string, Vector4);
	void(*stopSfxSound)(int);
	bool m_isOnLeft, m_isExternal, m_isStandAlone;
	bool m_engaged;
	bool  m_automatic;
	float m_heightCorrection;
	Action m_action;
	int m_index;
	float m_deltaX;
	
};