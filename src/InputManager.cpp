//###############################################################################
// INTRODUCCION: InputManager.cpp
//------------------------------------------------------------------------------
// Esta classe nos permite trabajar con los recursos de entrada de una forma
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

#include "InputManager.h"

#include <iostream>
#include <sstream>

#if defined OIS_WIN32_PLATFORM
#  define WIN32_LEAN_AND_MEAN
#  include "windows.h"
#  ifdef min
#    undef min
#  endif

#elif defined OIS_LINUX_PLATFORM
#  include <X11/Xlib.h>

#elif defined OIS_APPLE_PLATFORM
#  include <Carbon/Carbon.h>
#endif

const char *DEVICE_TYPE[6] =  {"OISUnknown", "OISKeyboard", "OISMouse", "OISJoyStick",
							 "OISTablet", "OISOther"};
                             
InputManager::InputManager()
    : m_ois(NULL)
    , m_keyboard(NULL)
	, m_mouse(NULL)
{
}

InputManager::~InputManager()
{
}

void InputManager::init(unsigned int window)
{
	//Primero leemos que dispositivos disponibles
	OIS::ParamList paramList;
    std::stringstream ss;
    ss << window;
    paramList.insert(std::make_pair(std::string("WINDOW"), ss.str()));
    

	//Inicializamos todos los dispositivos que haya en el sistema
	m_ois = OIS::InputManager::createInputSystem(paramList);
	m_ois->enableAddOnFactory(OIS::InputManager::AddOn_All);
    m_keyboard = NULL;
    m_mouse = NULL;
    
	//Pintamos por pantalla el resultado de la inicializacion de dispositivos
	unsigned int v = m_ois->getVersionNumber();
	std::cout << "OIS Version: " << (v>>16 ) << "." << ((v>>8) & 0x000000FF) << "." << (v & 0x000000FF)
		<< "\nRelease Name: " << m_ois->getVersionName()
		<< "\nManager: " << m_ois->inputSystemName()
		<< "\nTotal Keyboards: " << m_ois->getNumberOfDevices(OIS::OISKeyboard)
		<< "\nTotal Mice: " << m_ois->getNumberOfDevices(OIS::OISMouse)
		<< "\nTotal JoySticks: " << m_ois->getNumberOfDevices(OIS::OISJoyStick);
	OIS::DeviceList list = m_ois->listFreeDevices();
	for(OIS::DeviceList::iterator it = list.begin(); it != list.end(); it++)
		std::cout << "\n\tDevice: " << DEVICE_TYPE[it->first] << " Vendor: " << it->second;
    std::cout << std::endl;
}

void InputManager::done()
{
}

void InputManager::createKeyboardBuffered()
{
	//Si existe un objeto teclado ya creado anteriormente, lo borramos
    if (m_keyboard)
        m_ois->destroyInputObject(m_keyboard);

	//Creamos un nuevo objeto de tipo keyboard. No le asociamos funcion de callback
	//porque nosotros actualizaremos y consultaremos 'manualmente' el estado del teclado
	if (m_ois->getNumberOfDevices(OIS::OISKeyboard) > 0)
	{
		m_keyboard = (OIS::Keyboard*) m_ois->createInputObject(OIS::OISKeyboard, true);
	}
    else
        m_keyboard = NULL;
}

void InputManager::createKeyboardUnbuffered(OIS::KeyListener* listener)
{
	//Si existe un objeto teclado ya creado anteriormente, lo borramos
	if (m_keyboard)
        m_ois->destroyInputObject(m_keyboard);
	
	//Creamos un nuevo objeto de tipo keyboard y le asociamos un listener
	//(funcion de callback) para que gestione los evento de teclado.
	if (m_ois->getNumberOfDevices(OIS::OISKeyboard) > 0) {
        m_keyboard = (OIS::Keyboard*) m_ois->createInputObject(OIS::OISKeyboard, false);
        m_keyboard->setEventCallback(listener);
    } else
    m_keyboard = NULL;
}

void InputManager::createMouseBuffered()
{
	//Si existe un objeto mouse ya creado anteriormente, lo borramos
	if (m_mouse)
        m_ois->destroyInputObject(m_mouse);
    
	//Creamos un nuevo objeto de tipo mouse. No le asociamos funcion de callback
	//porque nosotros actualizaremos y consultaremos 'manualmente' el estado del raton
	if (m_ois->getNumberOfDevices(OIS::OISMouse) > 0)
        m_mouse = (OIS::Mouse*) m_ois->createInputObject(OIS::OISMouse, true);
    else
        m_mouse = NULL;
}

void InputManager::createMouseUnbuffered(OIS::MouseListener* listener)
{
	//Si existe un objeto mouse ya creado anteriormente, lo borramos
    if (m_mouse)
        m_ois->destroyInputObject(m_mouse);
	
	//Creamos un nuevo objeto de tipo mouse y le asociamos un listener
	//(funcion de callback) para que gestione los evento de raton.
    if (m_ois->getNumberOfDevices(OIS::OISMouse) > 0) {
        m_mouse = (OIS::Mouse*) m_ois->createInputObject(OIS::OISMouse, false);
        m_mouse->setEventCallback(listener);
    } else
        m_mouse = NULL;
}

void InputManager::capture()
{
	//Actualizamos el estado del teclado y del raton
    if (m_keyboard)
        m_keyboard->capture();
    if (m_mouse)
        m_mouse->capture();
    
}
