#include "Core.h"
#include "IntroState.h"
#include <time.h>
#include <iostream>
#include <string.h>
#include "FreeType.h"

IntroState::IntroState()
{
	Core::singleton().resourcesManager().loadIntroStateResources();
}

IntroState::~IntroState()
{
	
}

void IntroState::enter()
{


	int musicid = Core::singleton().soundManager().playSfx("intro");
	
	m_introCount = 500.0f;

	m_blinker=20;
}

void IntroState::display()
{
	//Cada vez que hay que redibujar la pantalla, primero limpiamos los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	if(m_blinker == 0)
	{ 
		m_blinker = 20;
	}
	else
	{
		m_blinker--;
	}

	if(m_introCount != 0.0f) m_introCount--;
	float scale_factor = (float) (100 - m_introCount)/100;
	
	//Dibujamos el fondo
	glPushMatrix();
	glTranslatef(width()/2.0f, height()/2.0f, 0.0f);
	Core::singleton().textureManager().getTextureAtlas("intro")->mesh("fondointro")->draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(width()/2, height()/2 , 1.0f);
	glScalef(scale_factor, 1.0f, 1.0f);
	Core::singleton().textureManager().getTextureAtlas("intro")->mesh("logo")->draw();
	
	glPopMatrix();
	glutSwapBuffers();
}

void IntroState::reshape(int width, int height)
{
	//Si cambiamos el tamaño de la pantalla,
	//tenemos que cambiar la matriz de proyección
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, this->width()*(3.0f/4.0f)*((float)width/(float)height), 0, this->height());
	glMatrixMode(GL_MODELVIEW);
}

void IntroState::update(const float elapsedTime)
{
	//Obtenemos la referencias al raton y al teclado
	OIS::Mouse* mouse = Core::singleton().inputManager().getMouse();
	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();

	//Comprobamos si se ha pulsado la tecla ESC para salir del juego
	if (keyboard->isKeyDown(OIS::KC_ESCAPE))
		exit(0);
	if (keyboard->isKeyDown(OIS::KC_RETURN))
	{
		//different for testing purposes

		if (m_introCount == 0) 
		{	
			Core::singleton().stateManager().changeTo("menu");
		}
	}
}

void IntroState::leave()
{
	Core::singleton().resourcesManager().unloadIntroStateResources();
}


