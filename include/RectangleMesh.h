//###############################################################################
// INTRODUCCION: RectangleMesh.h
//------------------------------------------------------------------------------
// Este codigo nospermite definir un rectangulo texturado. Lo usaremos tanto
// para dibujar el fondo como los sprites de la pantalla.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#pragma once

class Texture;

class RectangleMesh
{
public:
	// El constructor del cuadrado tiene que recibir una textura (ya cargada), las 4 coordenadas de textura
	// que se utilizaran de esta textura, y el alto/ancho del cuadrado
	RectangleMesh(Texture *texture, float tx, float ty, float tw, float th, float width, float height);
	virtual ~RectangleMesh();

public:
	// Devuelve el ancho del cuadrado
	float width() const { return m_width; }
	// Devuelve el alto del cuadrado
	float height() const { return m_height; }
	//Dibuja 
	void draw();

private:
	Texture *m_texture;
	float m_vertex[4 * 3];
	float m_coords[4 * 2];
public:
	float m_width;
	float m_height;
};