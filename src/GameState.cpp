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

#include "Core.h"
#include "GameState.h"
#include <iostream>


GameState::GameState():
m_pointerX(0),
	m_pointerY(0),
	m_toggleTime(0)
{
}

GameState::~GameState()
{
	//unload resources TO_DO
}

void GameState::enter()
{
	//Incializamos el sistema OpenGL
	glInit();

	//init mouse
	setMouseReferenceWidthAndHeight();



}

void GameState::glInit()
{
	glEnable(GL_NORMALIZE);
	glClearColor(0, 0, 0, 0.5f);
	glClearDepth(1.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_NOTEQUAL, 0);

}


void GameState::leave()
{
	Core::singleton().soundManager().stopSfxOrSong(m_musicid);
	Core::singleton().resourcesManager().unloadLevelResources(Core::singleton().gameProgressManager().getLevel());
}

void GameState::display()
{
	//Cada vez que hay que redibujar la pantalla, primero limpiamos los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Despues dibujamos el background
	//m_backgroundEntity->draw();

	if( Core::singleton().gameProgressManager().getGameProgressState() == GameProgressManager::IN_PROGRESS)
	{
		m_levelController.draw();

		//draw the cursor but move slightly so that the uper left corner of the cursor sprites coincides with the pointer coordinates 
		glPushMatrix();
		glTranslatef(m_pointerX + Core::singleton().textureManager().getTextureAtlas("pointer")->mesh("pointer")->width()/2, m_pointerY - Core::singleton().textureManager().getTextureAtlas("pointer")->mesh("pointer")->height()/2, 1.0f);
		Core::singleton().textureManager().getTextureAtlas("pointer")->mesh("pointer")->draw();
		glPopMatrix();     
	}



	glutSwapBuffers();
}

void GameState::reshape(int width, int height)
{
	//reshape window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, this->width()*(3.0f/4.0f)*((float)width/(float)height), 0, this->height());
	glMatrixMode(GL_MODELVIEW);

	//calibrate mouse (depends on the window size)
	setMouseReferenceWidthAndHeight();
}

void GameState::update(const float elapsedTime)
{
	//update Game Progress Logic
	updateGameProgressLogic();

	captureInput(elapsedTime);

	if(Core::singleton().gameProgressManager().getGameProgressState() == GameProgressManager::IN_PROGRESS)
	{
		m_levelController.update(elapsedTime);
	}
}

void GameState::updateGameProgressLogic()
{

	//check game progress state
	if (Core::singleton().gameProgressManager().getGameProgressState() == GameProgressManager::IN_PROGRESS)
	{
		if(m_levelController.getState() == LevelController::LEVEL_IN_PROGRESS) 
		{
			//NOTHING
			return;
		}
		else if(m_levelController.getState() == LevelController::LEVEL_FINISHED)
		{
			//If level is finished we should move onto the next level (use loading level etc)
			//As long as we have only one level the game is finished TO_DO
			Core::singleton().gameProgressManager().setGameProgressState(GameProgressManager::FINISHED);
			return;
		}
		else if(m_levelController.getState() == LevelController::LEVEL_GAME_OVER)
		{
			//if game over then set game over go to next state
			Core::singleton().gameProgressManager().setGameProgressState(GameProgressManager::GAME_OVER);
			Core::singleton().stateManager().changeTo("endgame");
			return;
		}
	}
	else if(Core::singleton().gameProgressManager().getGameProgressState() == GameProgressManager::LOADING_LEVEL)
	{
		Tmx::Map* map = Core::singleton().resourcesManager().loadLevelResources(Core::singleton().gameProgressManager().getLevel());
		m_levelController.loadNewLevel(map);
		Core::singleton().gameProgressManager().setGameProgressState(GameProgressManager::IN_PROGRESS);
		
		//start playing music
		m_musicid  =  Core::singleton().soundManager().playSong("fortress");
		delete map;
	}

	//more logic will follow
}

void GameState::captureInput(const float elapsedTime)
{

	OIS::Mouse* mouse = Core::singleton().inputManager().getMouse();
	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();

	m_pointerX = (mouse->getMouseState().X.abs);
	m_pointerY = glutGet(GLUT_WINDOW_HEIGHT) - (mouse->getMouseState().Y.abs);


	int ntime = glutGet(GLUT_ELAPSED_TIME);

	if( (ntime - m_toggleTime) > 90)
	{
		if (keyboard->isKeyDown(OIS::KC_ESCAPE))	exit(0);
		if (keyboard->isKeyDown(OIS::KC_F))
		{
			m_toggleTime = ntime;
			glutFullScreen();
		}
		if (keyboard->isKeyDown(OIS::KC_P))
		{
			m_toggleTime = ntime;
			if(Core::singleton().gameProgressManager().getGameProgressState() == GameProgressManager::PAUSED)
			{
				Core::singleton().gameProgressManager().setGameProgressState(GameProgressManager::IN_PROGRESS);
			}
			else if(Core::singleton().gameProgressManager().getGameProgressState() == GameProgressManager::IN_PROGRESS) 	
			{
				//we only allow pausing the game when in progress 
				Core::singleton().gameProgressManager().setGameProgressState(GameProgressManager::PAUSED);
			}
		}
	}

	/* TO_DO implement sound control with keys
	if (keyboard->isKeyDown(OIS::KC_T))
	{
	keytime = ntime;
	pause();
	}
	if (keyboard->isKeyDown(OIS::KC_R))
	{
	keytime = ntime;
	switchDrawBBoxes();
	}
	if (keyboard->isKeyDown(OIS::KC_O))
	{
	keytime = ntime;turnMusicOn();
	}
	if (keyboard->isKeyDown(OIS::KC_P))
	{
	keytime = ntime;turnMusicOff();
	}
	if (keyboard->isKeyDown(OIS::KC_U))
	{
	keytime = ntime;turnSfxSoundsOn();
	}
	if (keyboard->isKeyDown(OIS::KC_I))
	{
	keytime = ntime;turnSfxSoundsOff();
	}
	if (keyboard->isKeyDown(OIS::KC_Q))
	{
	keytime = ntime;turnMusicVolumeUp();
	}
	if (keyboard->isKeyDown(OIS::KC_W))
	{
	keytime = ntime;turnMusicVolumeDown();
	}
	if (keyboard->isKeyDown(OIS::KC_A))
	{
	keytime = ntime;turnSfxSoundsVolumeUp();
	}
	if (keyboard->isKeyDown(OIS::KC_S))
	{
	keytime = ntime;turnSfxSoundsVolumeDown();
	}
	if (keyboard->isKeyDown(OIS::KC_N))
	{
	keytime = ntime;switchToNextMusicTheme();
	}
	}*/

}

void GameState::setMouseReferenceWidthAndHeight()
{
	OIS::Mouse* mouse = Core::singleton().inputManager().getMouse();
	mouse->getMouseState().height =  glutGet(GLUT_WINDOW_HEIGHT);	
	mouse->getMouseState().width =  glutGet(GLUT_WINDOW_WIDTH);

}
