//###############################################################################
// INTRODUCCION: BackgroundEntity.cpp
//------------------------------------------------------------------------------
// Este codigo define una entidad Background que representa un fondo de pantalla.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "BackgroundEntity.h"
#include "RectangleMesh.h"
#include "MyGL.h"
#include "MyMath.h"

BackgroundEntity::BackgroundEntity(RectangleMesh *mesh, float screenWidth, float screenHeight, float zPos)
	: m_mesh(mesh)
	, m_xPos(0)
	, m_effxPos(m_mesh->width() / 2.f)
	, m_screenWidth(screenWidth)
	, m_screenHeight(screenHeight)
	, m_zPos(zPos)
{
}

BackgroundEntity::~BackgroundEntity()
{
}

void BackgroundEntity::setCameraPosition(float position)
{
	//Cambio de posición de la cámara. Aprovechamos para calcular la posición de dibujo en Ortho 2D (effxPos)
	m_xPos = Math::clamp(position, 0, m_mesh->width());
	m_effxPos = Math::clamp(m_xPos, m_screenWidth / 2, m_mesh->width() - m_screenWidth / 2);
	m_effxPos = m_mesh->width() / 2 + m_screenWidth / 2 - m_effxPos;
}

float BackgroundEntity::terrain2screen(float position)
{
	//A partir de la posición de la cámara, se realiza el cambio de
	//coordenadas. De la posición en el terreno a la posición en el Ortho
	//según la posición de la cámara.
	if (position <= m_screenWidth / 2)
		return position;
	if (position > m_mesh->width() - m_screenWidth / 2)
		return m_screenWidth - m_mesh->width() + position;
	return m_screenWidth / 2;
	//return position

}
Vector4 BackgroundEntity::terrain2screen(const Vector4& position)
{
	return Vector4(terrain2screen(position[0]), position[1], position[2], position[3]);
}



void BackgroundEntity::draw()
{
	//Dibujamos el fondo. Primero lo situamos en su posicion
	glPushMatrix();
	glTranslatef(m_effxPos, m_screenHeight / 2.0f, m_zPos);
	
	//Y despues lo dibujamos por pantalla
	m_mesh->draw();
	glPopMatrix();
}