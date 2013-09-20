//###############################################################################
// INTRODUCCION: BackgroundEntity.h
//------------------------------------------------------------------------------
// Este codigo define una entidad Background que representa un fondo de pantalla.
// Permite ver una imagen más alargada que la pantalla y cambiar la posición de
// la cámara para verla (scrolling).
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#pragma once

#include "MyGL.h"
#include "RectangleMesh.h"
#include "Vector4.h"

#include <string>

class BackgroundEntity
{
public:
	BackgroundEntity(RectangleMesh *mesh, float screenWidth, float screenHeight, float zPos = -1);
	virtual ~BackgroundEntity();

public:
	float width() const { return m_mesh->width(); }
	float height() const { return m_mesh->height(); }
	float position() const { return m_xPos; }

	//Cambio de la posición de la cámara (Scrolling)
	void setCameraPosition(float position);
	void setCameraPosition(const Vector4& position) { setCameraPosition(position[0]); }

	//Funcion que permite transformar una posición en el terreno a una posición de pantalla (según la posición de la cámara)
	float terrain2screen(float position);
	Vector4 terrain2screen(const Vector4& position);

	//Traslada y dibuja la imagen
	void draw();

private:
	RectangleMesh *m_mesh;
	float m_screenWidth;
	float m_screenHeight;
	float m_effxPos;
	float m_xPos;
	float m_zPos;
};
