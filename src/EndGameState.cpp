
#include "Core.h"
#include "EndGameState.h"
#include <time.h>
#include <iostream>
#include <string.h>
#include "FreeType.h"
#include "MyText.h"

EndGameState::EndGameState()
{
}

EndGameState::~EndGameState()
{
}

void EndGameState::enter()
{
	Core::singleton().resourcesManager().loadEndStateResources();
	m_musicid = Core::singleton().soundManager().playSong("ancient");
	
}

void EndGameState::display()
{
	//Cada vez que hay que redibujar la pantalla, primero limpiamos los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	
	//Dibujamos el fondo
	glPushMatrix();
	glTranslatef(glutGet(GLUT_WINDOW_WIDTH)/2, glutGet(GLUT_WINDOW_HEIGHT)/2, 0.0f);
	Core::singleton().textureManager().getTextureAtlas("game_over")->mesh("game_over")->draw();
	glPopMatrix();

	glutSwapBuffers();
}

void EndGameState::reshape(int width, int height)
{
	//reshape window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, this->width()*(3.0f/4.0f)*((float)width/(float)height), 0, this->height());
	glMatrixMode(GL_MODELVIEW);
}

void EndGameState::update(const float elapsedTime)
{
	//Obtenemos la referencias al raton y al teclado
	OIS::Mouse* mouse = Core::singleton().inputManager().getMouse();
	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();

	//Comprobamos si se ha pulsado la tecla ESC para salir del juego
	if (keyboard->isKeyDown(OIS::KC_ESCAPE))
		exit(-1);
	if (keyboard->isKeyDown(OIS::KC_RETURN)) Core::singleton().stateManager().changeTo("menu");
}

void EndGameState::leave()
{
	Core::singleton().soundManager().stopSfxOrSong(m_musicid);
	Core::singleton().resourcesManager().unloadEndStateResources();
}


