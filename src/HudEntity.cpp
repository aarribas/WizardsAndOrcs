//###############################################################################
// INTRODUCCION: HudEntity.cpp
//------------------------------------------------------------------------------
// Este codigo define una entidad Hud que representa un fondo de pantalla.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#include "HudEntity.h"
#include "RectangleMesh.h"
#include "MyGL.h"
#include "MyText.h"


const float HudEntity::LIFEBAR_SCALE_FACTOR=0.5;
const float HudEntity::X_LIFEBAR = 100;
const float HudEntity::Y_LIFEBAR = 40;
const float HudEntity::X_FACE_FIGHTER = 15;
const float HudEntity::Y_FACE_FIGHTER = 5;
const float HudEntity::X_TEXT = 100;
const float HudEntity::Y_TEXT = 5;

HudEntity::HudEntity(float screenWidth, float screenHeight, float zPos)
	: m_screenWidth(screenWidth)
	, m_screenHeight(screenHeight)
	, m_zPos(zPos)
	, m_time(0)
	, m_fighter1HitPoints(100)
	, m_fighter2HitPoints(100)
	, m_fighter1Name("paco")
	, m_fighter2Name("pepe")
{
	//Creamos todos los elementos del HUD
}

HudEntity::~HudEntity()
{
}

void HudEntity::draw()
{
	//Dibujamos todos los elementos del HUD

	//Dibujar Parte Izquierda
	bool isOnLeftSide  = true;
	drawFace("ryu", isOnLeftSide);
	drawName(m_fighter1Name, true);
	drawLifeBar(isOnLeftSide);
	
	

	//Dibujar Parte Derecha
	//Primero de todo tenemos que posicionar el avatar dentro de la pantalla
	isOnLeftSide = false;
	drawFace("ryu", isOnLeftSide);
	drawName(m_fighter2Name, false); 
	drawLifeBar(isOnLeftSide);

	drawHitPoints();
	drawTime();
}

void HudEntity::drawFace(const std::string& text, bool onLeftSide)
{
	glPushMatrix();
	RectangleMesh* mesh = m_faceTextureAtlas->mesh(text);
	if (onLeftSide)
	{
	glTranslatef(mesh->m_width/2 + X_FACE_FIGHTER, m_screenHeight - (mesh->m_height/2 + Y_FACE_FIGHTER), m_zPos);
	}
	else
	{
		glTranslatef(m_screenWidth-(mesh->m_width/2 + X_FACE_FIGHTER), m_screenHeight - (mesh->m_height/2 + Y_FACE_FIGHTER), m_zPos);
	}
	mesh->draw();
	glPopMatrix();

}

void HudEntity::drawName(const std::string& text, bool isOnLeftSide)
{
	if(isOnLeftSide)
	{
		drawText(text,X_TEXT,Y_TEXT);
	}
	else
	{
		float textWidth = 0;
		for(int j = 0; j < text.length() ; j++)
		{
			RectangleMesh* mesh = m_fontTextureAtlas->mesh(text.substr(j,1));
			textWidth += mesh->m_width;	
		}
		drawText(text,m_screenWidth - (textWidth + X_TEXT),Y_TEXT);
	}
}			
void HudEntity::drawText(const std::string& text, float xoffset, float yoffset)
{
	/*
	for(int i = 0; i < text.length() ; i++)
	{
		glPushMatrix();
		RectangleMesh* mesh = m_fontTextureAtlas->mesh(text.substr(i,1));
		glTranslatef(mesh->m_width/2 + xoffset, m_screenHeight - (mesh->m_height/2 + yoffset), m_zPos);
		mesh->draw();
		glPopMatrix();
		xoffset=mesh->m_width+xoffset;
		
	}
	*/
	myText::drawText(m_fontTextureAtlas, text, xoffset, m_screenHeight - yoffset, m_zPos);


}


void HudEntity::drawLifeBar(bool isOnLeftSide)
{	
	glPushMatrix();
	RectangleMesh* mesh = m_mainTextureAtlas->mesh("lifebarred");
	if(isOnLeftSide)
	{
		glTranslatef(mesh->m_width/2*LIFEBAR_SCALE_FACTOR + X_LIFEBAR, m_screenHeight - mesh->m_height*LIFEBAR_SCALE_FACTOR - Y_LIFEBAR , m_zPos);
	}
	else
	{
		glTranslatef(m_screenWidth-(mesh->m_width/2*LIFEBAR_SCALE_FACTOR + X_LIFEBAR), m_screenHeight - mesh->m_height*LIFEBAR_SCALE_FACTOR - Y_LIFEBAR , m_zPos);
	
	}
	glScalef(LIFEBAR_SCALE_FACTOR, LIFEBAR_SCALE_FACTOR, 0);
	mesh->draw();
	glPopMatrix();
	
	glPushMatrix();
	mesh = m_mainTextureAtlas->mesh("lifebarframe");
	if(isOnLeftSide)
	{
		glTranslatef(mesh->m_width/2*LIFEBAR_SCALE_FACTOR + X_LIFEBAR, m_screenHeight - mesh->m_height*LIFEBAR_SCALE_FACTOR - Y_LIFEBAR , m_zPos);
	}
	else
	{
		glTranslatef(m_screenWidth-(mesh->m_width/2*LIFEBAR_SCALE_FACTOR + X_LIFEBAR), m_screenHeight - mesh->m_height*LIFEBAR_SCALE_FACTOR - Y_LIFEBAR , m_zPos);
	
	}
	glScalef(LIFEBAR_SCALE_FACTOR, LIFEBAR_SCALE_FACTOR, 0);
	mesh->draw();
	glPopMatrix();
}


void HudEntity::drawHitPoints()
{	
	glPushMatrix();
	RectangleMesh* mesh = m_mainTextureAtlas->mesh("lifebaryellow");
	glTranslatef(mesh->m_width/2*LIFEBAR_SCALE_FACTOR*m_fighter1HitPoints/100 + X_LIFEBAR, m_screenHeight - mesh->m_height*LIFEBAR_SCALE_FACTOR - Y_LIFEBAR , m_zPos);
	glScalef(LIFEBAR_SCALE_FACTOR*(float)m_fighter1HitPoints/100, LIFEBAR_SCALE_FACTOR, 0);
	mesh->draw();
	glPopMatrix();
	glPushMatrix();

	
	glPushMatrix();
	RectangleMesh* mesh2 = m_mainTextureAtlas->mesh("lifebaryellow");
	glTranslatef(m_screenWidth - (mesh2->m_width/2*LIFEBAR_SCALE_FACTOR*m_fighter2HitPoints/100 + X_LIFEBAR), m_screenHeight - mesh2->m_height*LIFEBAR_SCALE_FACTOR - Y_LIFEBAR , m_zPos);
	glScalef(LIFEBAR_SCALE_FACTOR*(float)m_fighter2HitPoints/100, LIFEBAR_SCALE_FACTOR, 0);
	mesh2->draw();
	glPopMatrix();
	glPushMatrix();
}

void HudEntity::drawTime()
{
	if(m_time >= 0)
		{
			std::string text = Converter::intToString((int)m_time);
		float xoffset = m_screenWidth/2;
		if(text.length()>2) 
		{
			xoffset-=32;	
		}
		float yoffset = 100; //pasar esto a constante mas tarde
		for(int i = 0; i < text.length() ; i++)
		{
			glPushMatrix();
			RectangleMesh* mesh = m_fontTextureAtlas->mesh(text.substr(i,1));
			glTranslatef(mesh->m_width/2 + xoffset, m_screenHeight - (mesh->m_height/2 + yoffset), m_zPos);
			mesh->draw();
			glPopMatrix();
			xoffset=mesh->m_width+xoffset;
		
		}
	}
}

void HudEntity::update(const float timeLeft, int fighter1HitPoints, int  fighter2HitPoints)
{
	//Actualizamos el estado de todos los elementos del HUD
	m_time = timeLeft;
	if (fighter1HitPoints >= 0) 
	{
		m_fighter1HitPoints = fighter1HitPoints;
	}
	else
	{
		m_fighter1HitPoints = 0;
	}

	if (fighter2HitPoints >= 0) 
	{
		m_fighter2HitPoints = fighter2HitPoints;
	}
	else
	{
		m_fighter2HitPoints = 0;
	}

}