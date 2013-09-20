//###############################################################################
// INTRODUCCION: ConcretGame.h
//------------------------------------------------------------------------------
// Esto es una interficie virtual que define todas las funciones que tiene que tener
// un juego para que se pueda inicializar y ejecutar dentro del Core.
// Los juegos tienen que extender esta interficie e implementar todas las funciones. 
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#pragma once



class IState
{
public:
    virtual ~IState() { }
    
	//Funcion que nos devuelve el ancho de la pantalla 
	virtual int width() const = 0;

	//Funcion que nos devuelve el alto de la pantalla 
	virtual int height() const = 0;

    //Funcion que nos permite inicializar estado
	virtual void enter() = 0;
    
	//Funcion que se ejecuta cuando se tiene que redibujar la pantalla
	virtual void display() = 0;
    
	//Funcion que se ejecuta cuando cambia el tamaño de la pantalla
	virtual void reshape(int width, int height) = 0;
	
	//Funcion que se ejecuta cada vez que queremos actualizar los elementos del juego
	virtual void update(const float elapsedTime) = 0;

	virtual void leave() = 0; 
};