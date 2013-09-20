//###############################################################################
// INTRODUCCION: Core.cpp
//------------------------------------------------------------------------------
// Este codigo contiene el bucle principal del programa. Consiste basicamente 
// de dos funciones, la funcion init que inicializa todo el entorno, y la
// funcion run que contiene la ejecucion del bucle.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "Core.h"
#include "MyGL.h"
#include "IntroState.h"
#include "EndGameState.h"
#include "MenuState.h"
#include "GameState.h"

#include <ctime>
#include <iostream>

Core::Core()
{
}

Core::~Core()
{
	

}


//##############################################################################
//Funcion para inicializar el bucle principal
void Core::init(int* argc, char* argv[])
{
   
	//Creamos la ventana principal del programa utilizando la libreria GLUT
	glutInit(argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
	//glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1024, 768); 
	int mainWindow = glutCreateWindow("YMID");
	//glutFullScreen();
	glutSetWindow(mainWindow);

	HWND hwnd = GetForegroundWindow();
	HWND window = FindWindow(L"GLUT", L"YMID");

	//Inicializamos el Input Manager
    m_inputManager.init((unsigned int) window);
	m_inputManager.createKeyboardBuffered();
	m_inputManager.createMouseBuffered();

	//Inicializamos el Sound Manager
    m_soundManager.init();
	
	//Inicializamos el Settings Manager
	m_settingsManager.init();


	//Inicializamos el Texture Manager
	m_textureManager.init();
	
	//Inicializamos el Font Manager
	m_fontManager.init();
	
	//Inicializamos el Resources Manager
	m_resourcesManager.init();

	
	//Inicializamos el Game Progress Manager
	m_gameProgressManager.init();

	//Inicializamos el juego
	m_stateManager.registerState("game", new GameState());
	m_stateManager.registerState("menu", new MenuState());
	m_stateManager.registerState("intro", new IntroState());
	m_stateManager.registerState("endgame", new EndGameState());
	m_stateManager.changeTo("intro");
    
	//Asignamos todas las funciones de callback del glut
	//a las funciones que definiremos posteriormente
	glutDisplayFunc(static_display);
	glutReshapeFunc(static_reshape);
	glutIdleFunc(static_idle);
	

	initGL();
}

void Core::initGL()
{
	//Incializamos el sistema OpenGL
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

void Core::run()
{
	//Pasamos el control del bucle principal al glut
	//que nos gestionara los eventos y llamara a las 
	//funciones de callback definidas a continuacion
	glutMainLoop();
}




//##############################################################################
// FUNCIONES DE CALLBACK DEL GLUT
// Estas funciones se llaman cuando se lanza un evento concreto

//Esta funcion se llama cuando se tiene que refrescar la pantalla
void Core::static_display()
{
    Core::singleton().m_stateManager.display();
}

//Esta funcion se llama cuando se cambia el tamano de la ventana
void Core::static_reshape(int width, int height)
{
    Core::singleton().m_stateManager.reshape(width, height);
}

//Esta funcion se llama cuando el sistema no hace nada
void Core::static_idle()
{
	//Vamos a repintar cada cierto numero de frames
	//Miramos el reloj del sistema
	static clock_t lastTime = clock();
	clock_t now = clock();
	//Miramos cuanto tiempo ha pasado desde la ultima vez que se ha ejecutado esta funcion
	float elapsedTime = (float) (now - lastTime) / (float) CLOCKS_PER_SEC;
	lastTime = now;

	//Actualizamos el estado del teclado y el raton
    Core::singleton().inputManager().capture();

	//Actualizamos el estado del sonido
    Core::singleton().soundManager().update();

	//Actualizamos el estado del juego
    Core::singleton().m_stateManager.update(elapsedTime);
    
	//Repintamos la escena
	glutPostRedisplay();

}


