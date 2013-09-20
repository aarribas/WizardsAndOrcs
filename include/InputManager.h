//###############################################################################
// INTRODUCCION: InputManager.h
//------------------------------------------------------------------------------
// Esta clase nos permite trabajar con los recursos de entrada de una forma
// centralizada. Este codigo implementa las funciones que teneis en los apuntes
// para acceder al teclado y al raton de forma Buffered y unBuffered.
// El codigo esta basado en las librerias OIS,
// http://en.wikipedia.org/wiki/Object_Oriented_Input_System
// 
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#pragma once

#include <OIS/OISInputManager.h>
#include <OIS/OISException.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <OIS/OISJoyStick.h>
#include <OIS/OISEvents.h>

//Advanced Usage
#include <OIS/OISForceFeedback.h>

class Core;

class InputManager
{
private:
    friend class Core;
    InputManager();
    virtual ~InputManager();

public:
	//Funcion para inicializar el sistema
	void init(unsigned int window);
    void done();

	//Funciones para inicializar el funcionamiento de los dispositivos
    void createKeyboardBuffered();
    void createKeyboardUnbuffered(OIS::KeyListener* listener);
    void createMouseBuffered();
    void createMouseUnbuffered(OIS::MouseListener* listener);
    
	//Funcion para actualizar el estado del teclado y el raton
	void capture();

	//Funciones para consultar el estado del teclado y el raton
	OIS::Keyboard *getKeyboard() { return m_keyboard; }
    OIS::Mouse *getMouse() { return m_mouse; }
    
private:
    OIS::InputManager *m_ois;
    OIS::Keyboard *m_keyboard;
    OIS::Mouse *m_mouse;
};