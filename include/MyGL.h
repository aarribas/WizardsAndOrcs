//###############################################################################
// INTRODUCCION: MyGL.h
//------------------------------------------------------------------------------
// Realiza las inclusiones de ficheros de cabecera según plataforma de 
// desarrollo.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#ifndef __MyGL__
#define __MyGL__

#if defined(__APPLE__)
#  include <Carbon/Carbon.h>
#  include <OpenGL/OpenGL.h>
#  include <GLUT/GLUT.h>
#elif defined(__linux__)
#  include <GL/gl.h>
#  include <GL/glut.h>
#elif defined(WINDOWS) || defined(_WIN32)
//#include <WindowsIncludes.h>  //must be included before windows.h to avoid the bug in winsock.h
#  include <windows.h>		// Header File For Windows
#  include <gl\gl.h>		// Header File For The OpenGL32 Library
#  include <gl\glu.h>		// Header File For The GLu32 Library
#  include <gl\glut.h>		// Header File For The GLUT Library

#define GL_CLAMP_TO_EDGE 0x812F

#endif

#endif // __MyGL__

