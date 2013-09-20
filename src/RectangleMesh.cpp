//###############################################################################
// INTRODUCCION: RectangleMesh.cpp
//------------------------------------------------------------------------------
// Este codigo nos permite definir un rectangulo texturado. Lo usaremos tanto
// para dibujar el fondo como los sprites de la pantalla.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "RectangleMesh.h"
#include "MyGL.h"
#include "Texture.h"


RectangleMesh::RectangleMesh(Texture *texture, float tx, float ty, float tw, float th, float width, float height)
	: m_texture(texture)
	, m_width(width)
	, m_height(height)
{
	//Definimos las coordenadas (x,y,z) y las coordenadas de textura (u,v)
	//de los cuatro puntos de un cuadrado en un vertex array
	
	//Primer vertice
	int v = 0;
	m_vertex[ v * 3 + 0 ] = -0.5f;
	m_vertex[ v * 3 + 1 ] = -0.5f;
	m_vertex[ v * 3 + 2 ] = 0;

	m_coords[ v * 2 + 0 ] = tx;
	m_coords[ v * 2 + 1 ] = ty + th;

	//Segundo vertice
	v++;
	m_vertex[ v * 3 + 0 ] =  0.5f;
	m_vertex[ v * 3 + 1 ] = -0.5f;
	m_vertex[ v * 3 + 2 ] = 0;
	
	m_coords[ v * 2 + 0 ] = tx + tw;
	m_coords[ v * 2 + 1 ] = ty + th;

	//Tercer vertice
	v++;
	m_vertex[ v * 3 + 0 ] = -0.5f;
	m_vertex[ v * 3 + 1 ] =  0.5f;
	m_vertex[ v * 3 + 2 ] = 0;
	
	m_coords[ v * 2 + 0 ] = tx;
	m_coords[ v * 2 + 1 ] = ty;

	//Cuarto vertice
	v++;
	m_vertex[ v * 3 + 0 ] = 0.5f;
	m_vertex[ v * 3 + 1 ] = 0.5f;
	m_vertex[ v * 3 + 2 ] = 0;
	
	m_coords[ v * 2 + 0 ] = tx + tw;
	m_coords[ v * 2 + 1 ] = ty;
}

RectangleMesh::~RectangleMesh()
{
}

void RectangleMesh::draw()
{
	//Para dibujar el cuadrado, en primer lugar nos aseguramos
	//que los vertex array que nos interesan estan activados
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	
	//Como trabajamos en 2D, la normal de todas las caras
	//es siempre la misma
	glNormal3f(0, 0, 1);
	
	//Asignamos los vertex array a los punteros 
	glVertexPointer(3, GL_FLOAT, 0, m_vertex);
	glTexCoordPointer(2, GL_FLOAT, 0, m_coords);

	//Escalamos el cuadrado para que tenga el tamaño que corresponda
	glPushMatrix();
	float w=glutGet(GLUT_WINDOW_WIDTH);
	float h=glutGet(GLUT_WINDOW_HEIGHT);
	glScalef(m_width, m_height, 1);

	//Asignamos la textura al cuadrado
	m_texture->bind();
	
	//Finalmente dibujamos el cuadrado
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glPopMatrix();
}
