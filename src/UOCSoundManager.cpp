//###############################################################################
// INTRODUCCION: SoundManager.cpp
//------------------------------------------------------------------------------
// Esta classe nos permite gestionar el sonido de la aplicacion. Permite crear
// un sistema de sonido general, en el que podemos añadir sonidos y controlar
// su reproducción y sus parametros (volumen, ...). Esta basado en la libreria
// FMOD Ex: http://www.fmod.org
// 
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
    : m_system(NULL)
{
}

SoundManager::~SoundManager()
{
}

void SoundManager::init()
{
    FMOD_RESULT result;
    unsigned int version;
    FMOD_CAPS caps;
    FMOD_SPEAKERMODE speakerMode;
    
	//Inicializamos el sistema de sonido de FMOD 
    checkError(FMOD::System_Create(&m_system));
    checkError(m_system->getVersion(&version));
    if (version < FMOD_VERSION) {
        std::cout << "FMOD: Versión errónea " << std::hex << version << " < " << std::hex << FMOD_VERSION << std::endl;
        exit(-1);
    }

	//Inicializamos los parametros de configuración del sistema FMOD
    checkError(m_system->getDriverCaps(0, &caps, 0, &speakerMode));
    if (caps & FMOD_CAPS_HARDWARE_EMULATED)
        checkError(m_system->setDSPBufferSize(1024, 10));
    result = m_system->init(100, FMOD_INIT_NORMAL, 0);
    if (result == FMOD_ERR_OUTPUT_CREATEBUFFER) {
        checkError(m_system->setSpeakerMode(FMOD_SPEAKERMODE_STEREO));
        checkError(m_system->init(100, FMOD_INIT_NORMAL, 0));
    }
}

void SoundManager::done()
{
}

void SoundManager::update()
{
	//Llamamos a la funcion update de FMOD para que actualize los sonidos
    m_system->update();
}

void SoundManager::createSound(const std::string &name, const std::string &filename)
{
	//Creamos un nuevo sonido a partir de un fichero de sonido
    FMOD::Sound *sound;
    checkError(m_system->createSound(filename.c_str(), FMOD_3D, 0, &sound));
	
	//Y nos guardamos la referencia del sonido en una tabla de hashing
    m_sounds[name] = sound;
}

int SoundManager::playSound(const std::string &name)
{
	//Accedemos al sonido que tenemos guardado en la tabla de hashing
    FMOD::Sound *sound = m_sounds[name];
    
	//Escogemos un canal y reproducimos el sonido por este canal
	FMOD::Channel *channel;
    checkError(m_system->playSound(FMOD_CHANNEL_FREE, sound, true, &channel));
    static int nextID = 0;
    int id = nextID++;
    m_playingSounds[id] = channel;
    return id;
}

FMOD::Channel *SoundManager::getChannel(int playId)
{
    std::map<int, FMOD::Channel*>::iterator found = m_playingSounds.find(playId);
    if (found == m_playingSounds.end())
        return NULL;
    return found->second;
}

void SoundManager::checkError(FMOD_RESULT result)
{
	//Esta funcion comprueba si se ha ejectuado correctamente una llamada a la API
	//de FMOD. Si hay un error lo muestra por pantalla y sale de la aplicacion.
    if (FMOD_OK != result) {
        std::cout << FMOD_ErrorString(result) << std::endl;
        exit(-1);
    }
}
