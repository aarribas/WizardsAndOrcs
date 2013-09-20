//###############################################################################
// INTRODUCCION: HudEntity.cpp
//------------------------------------------------------------------------------
// Este codigo define una entidad Hud para mostrar el estado del juego.
//
// PROGRESO DEL CODIGO
//------------------------------------------------------------------------------
// Fecha       Editor           Descripcion
//------------------------------------------------------------------------------
// 2012.03.20  Helio Tejedor    Codigo creado
//##############################################################################

#pragma once

#include "MyGL.h"
#include "Vector4.h"
#include "TextureAtlas.h"
#include "MyConverter.h"


#include <string>

class RectangleMesh;

class HudEntity
{
public:
	static const float LIFEBAR_SCALE_FACTOR;
	static const float X_LIFEBAR;
	static const float Y_LIFEBAR;
	static const float X_FACE_FIGHTER;
	static const float Y_FACE_FIGHTER;
	static const float X_TEXT;
	static const float Y_TEXT;
public:
	HudEntity(float screenWidth, float screenHeight, float zPos);
	virtual ~HudEntity();

public:
	void update(const float timeleft, int fighter1hitpoints, int fighter2hitpoints );
	void draw();
	void setFace1(RectangleMesh *);

	void setFontTextureAtlas(TextureAtlas * fontTextureAtlas){m_fontTextureAtlas = fontTextureAtlas;}
	void setFaceTextureAtlas(TextureAtlas * faceTextureAtlas){m_faceTextureAtlas = faceTextureAtlas;}
	void setMainTextureAtlas(TextureAtlas * mainTextureAtlas){m_mainTextureAtlas = mainTextureAtlas;}

	void drawName(const std::string&, bool isOnLeftSide);
	void drawText(const std::string&, float xoffset, float yoffset);
	void drawFace(const std::string&, bool isOnLeftSide);
	void drawLifeBar(bool isOnLeftSide);
	void drawHitPoints();
	void drawTime();

private:
	float m_screenWidth;
	float m_screenHeight;
	float m_zPos;
	TextureAtlas *m_fontTextureAtlas; 
	TextureAtlas *m_faceTextureAtlas;
	TextureAtlas *m_mainTextureAtlas;
	float m_time;
	int m_fighter1HitPoints, m_fighter2HitPoints;
	std::string m_fighter1Name, m_fighter2Name;
};
