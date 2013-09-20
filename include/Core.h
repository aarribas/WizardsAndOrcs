//###############################################################################
// INTRODUCCION: Core.h
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

#pragma once

#include "StateManager.h"
#include "InputManager.h"
#include "SoundManager.h"
#include "SettingsManager.h"
#include "ResourcesManager.h"
#include "TextureManager.h"
#include "FontManager.h"
#include "GameProgressManager.h"

class Core
{

private:
	// Constructor y destructor de la clase
	Core();
	~Core();

public:
	static Core& singleton()
	{
		static Core instance;
		return instance;
	}

public:
	//Funcion para inicializar el bucle principal
	void init(int* argc, char* argv[]);
	//Funcion para ejecutar el bucle principal
	void run();
	void initGL();
	
public:
	//Funcion para acceder a los controladores
	InputManager& inputManager() { return m_inputManager; }
    SoundManager& soundManager() { return m_soundManager; }
	StateManager& stateManager() { return m_stateManager; }
	SettingsManager& settingsManager() { return m_settingsManager; }
	ResourcesManager& resourcesManager() { return m_resourcesManager; }
	TextureManager& textureManager(){return m_textureManager;}
	FontManager& fontManager(){return m_fontManager;}
	GameProgressManager& gameProgressManager(){return m_gameProgressManager;}
private:
	// Funciones para capturar y tratar los eventos enviados por el glut
	static void static_display();
	static void static_reshape(int width, int height);
	static void static_idle();

private:
    StateManager m_stateManager;
    InputManager m_inputManager;
    SoundManager m_soundManager;
	SettingsManager m_settingsManager;
	ResourcesManager m_resourcesManager;
	TextureManager m_textureManager;
	FontManager m_fontManager;
	GameProgressManager m_gameProgressManager;
};
