//###############################################################################
// INTRODUCCION: SoundManager.h
//------------------------------------------------------------------------------
// Esta clase nos permite gestionar el sonido de la aplicacion. Permite crear
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

#pragma once

#include "fmod/fmod.hpp"
#include "fmod/fmod_errors.h"
#include <map>
#include <string>

class Core;

class SoundManager
{
private:
    friend class Core;
    SoundManager();
    virtual ~SoundManager();

public:
	//Inicializamos el sistema de sonido de FMOD
    void init();
    void done();
    
	//Actualizamos los sonidos
    void update();

	//Añadimos un nuevo sonido
    void createSound(const std::string &name, const std::string &filename);
    
	//Reproducimos un sonido ya creado
	int playSound(const std::string &name);

	//Funcion para acceder a un sonido en reproduccion
    FMOD::Channel *getChannel(int playId);

private:
    static void checkError(FMOD_RESULT result);

private:
    FMOD::System *m_system;
    std::map<std::string, FMOD::Sound*> m_sounds;
public:
    std::map<int, FMOD::Channel*> m_playingSounds;
};