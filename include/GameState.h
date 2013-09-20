//###############################################################################
// INTRODUCCION: StreetFighterGame.cpp
//------------------------------------------------------------------------------
// Esta implementacion de ConcretGame es un juego de Street Fighter, con su fondo
// de pantalla y un luchador. Para las 3 primera PEC tendremos que trabajar los
// aspectos de sonido, interacción y redes del juego.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#pragma once

#include "IState.h"
#include "MyGL.h"
#include "LevelController.h"

class GameState
    : public IState
{

public:
    GameState();
    virtual ~GameState();

public:
	virtual int width() const { return 1024; }
	virtual int height() const { return 768; }
    virtual void enter();
	virtual void leave();
    virtual void display();
    virtual void reshape(int width, int height);
	virtual void update(const float elapsedTime);
private:
	void glInit();
	void captureInput(const float elapsedTime);
	void updateGameProgressLogic();
	void setMouseReferenceWidthAndHeight();

private:
	float m_pointerX;
	float m_pointerY;
	LevelController m_levelController;
	int m_toggleTime;
	int m_musicid;
};



