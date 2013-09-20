#pragma once
#include "Vector4.h"
#include "BasicLogicDefinitions.h"
class DynamicObjectModel
{
public:

	typedef struct {
		float left,top,
		right,bottom;
	} Rect;
	
	enum DynamicObjectState {
		DYNAMIC_OBJECT_STATE_MOVE_UP,
		DYNAMIC_OBJECT_STATE_MOVE_DOWN,
		DYNAMIC_OBJECT_STATE_MOVE_RIGHT,
		DYNAMIC_OBJECT_STATE_MOVE_LEFT,
		DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT,
		DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT,
		DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT,
		DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT,
		DYNAMIC_OBJECT_STATE_IMPACTING,
		DYNAMIC_OBJECT_STATE_VANISHING,
		DYNAMIC_OBJECT_STATE_VANISHED
	};
		
	enum DynamicObjectAction {
		DYNAMIC_OBJECT_ACTION_IDLE,
		DYNAMIC_OBJECT_ACTION_MOVE_UP,
		DYNAMIC_OBJECT_ACTION_MOVE_DOWN,
		DYNAMIC_OBJECT_ACTION_MOVE_RIGHT,
		DYNAMIC_OBJECT_ACTION_MOVE_LEFT,
		DYNAMIC_OBJECT_ACTION_MOVE_UP_RIGHT,
		DYNAMIC_OBJECT_ACTION_MOVE_UP_LEFT,
		DYNAMIC_OBJECT_ACTION_MOVE_DOWN_RIGHT,
		DYNAMIC_OBJECT_ACTION_MOVE_DOWN_LEFT,
		DYNAMIC_OBJECT_ACTION_IMPACT,
		DYNAMIC_OBJECT_ACTION_VANISH
	};

public:
	DynamicObjectModel();
	virtual ~DynamicObjectModel();
public:
	
	virtual DynamicObjectState getState(){return m_state;}
	virtual void setState(DynamicObjectState state){m_state = state;}

	virtual DynamicObjectAction getAction(){return m_action;}
	virtual void setAction(DynamicObjectAction action){m_action  = action; }

	const float getTimeout(){ return m_timeout;};
	void setTimeout(float timeout){m_timeout = timeout;}

	void setTerrainPosition(const Vector4& terrainPosition) { m_terrainPosition = terrainPosition; }
	const Vector4& getTerrainPosition() const { return m_terrainPosition; }
	
	const Vector4 getScreenPosition() const { return m_terrainPosition*PIXELS_PER_METER; }
	
	void setScreenPosition(const Vector4& screenPosition) { m_terrainPosition = screenPosition * (float)(1/ (float)PIXELS_PER_METER); }

	void setStep(const float &stepX, const float &stepY){ m_stepX = stepX; m_stepY = stepY; }
	void getStep(float *stepX, float *stepY){ *stepX = m_stepX; *stepY = m_stepY; }

	void setPixelWidth(int width){ m_pixelWidth = width; }
	const int getPixelWidth(){return m_pixelWidth;}
	
	void setPixelHeight(int height){ m_pixelHeight = height; }
	const int getPixelHeight(){return m_pixelHeight;}

	void setRect(const Rect rect){ m_rect = rect; }
	const Rect getRect(){return m_rect;}

	virtual float getCelerity() = 0;
	const float getDamagePoints(){ return m_damagePoints;}
	void setDamagePoints(float damagePoints){ m_damagePoints = damagePoints;}

protected:
	int m_damagePoints;
	DynamicObjectState m_state;
	DynamicObjectAction m_action;
	Vector4 m_terrainPosition;
	Vector4 m_screenPosition;
	float m_timeout;
	float m_stepX;
	float m_stepY;
	int m_pixelWidth;
	int m_pixelHeight;
	Rect m_rect;
};
