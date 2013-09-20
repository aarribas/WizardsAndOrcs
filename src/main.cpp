//###############################################################################
// INTRODUCCION: main.cpp
//------------------------------------------------------------------------------
// Programa principal. Hacemos una instancia del juego StreetFighter i la 
// pasamos al core para primero inicializarla y despues ejecutarla.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _INC_MALLOC
#endif
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include "Core.h"
#include <string>


int main(int argc, char* argv[])

{
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    Core::singleton().init(&argc, argv);
    Core::singleton().run();
    return 0;
}
