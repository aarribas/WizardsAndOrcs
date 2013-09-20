//###############################################################################
// INTRODUCCION: MyMath.h
//------------------------------------------------------------------------------
// Definimos una funcion que permite hacer clamp de un valor: Si el valor esta
// entre min(por defecto 0) y max(por defecto 1) se mantiene el valor. Si es mas 
// pequeño de min valdra min y si es mayor que max valdra max.
// Esta funcion es muy util para trabajar con texturas.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "MyMath.h"

float Math::clamp(float value, float min, float max)
{
	if (value <= min)
		return min;
	if (value >= max)
		return max;
	return value;
}
