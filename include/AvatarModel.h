#pragma once
#include "Vector4.h"
#include "BasicLogicDefinitions.h"
class AvatarModel
{
public:

	typedef struct {
		float left,top,
		right,bottom;
	} Rect;
	
	enum AvatarState {
		AVATAR_STATE_IDLE,
		AVATAR_STATE_MOVE_UP,
		AVATAR_STATE_MOVE_DOWN,
		AVATAR_STATE_MOVE_RIGHT,
		AVATAR_STATE_MOVE_LEFT,
		AVATAR_STATE_MOVE_UP_RIGHT,
		AVATAR_STATE_MOVE_UP_LEFT,
		AVATAR_STATE_MOVE_DOWN_RIGHT,
		AVATAR_STATE_MOVE_DOWN_LEFT,
		AVATAR_STATE_ATTACK_UP,
		AVATAR_STATE_ATTACK_DOWN,
		AVATAR_STATE_ATTACK_RIGHT,
		AVATAR_STATE_ATTACK_LEFT,
		AVATAR_STATE_ATTACK_UP_RIGHT,
		AVATAR_STATE_ATTACK_UP_LEFT,
		AVATAR_STATE_ATTACK_DOWN_RIGHT,
		AVATAR_STATE_ATTACK_DOWN_LEFT,
		AVATAR_STATE_DIE,
		AVATAR_STATE_DEAD
	};
		
	enum AvatarAction {
		AVATAR_ACTION_IDLE,
		AVATAR_ACTION_MOVE_UP,
		AVATAR_ACTION_MOVE_DOWN,
		AVATAR_ACTION_MOVE_RIGHT,
		AVATAR_ACTION_MOVE_LEFT,
		AVATAR_ACTION_MOVE_UP_RIGHT,
		AVATAR_ACTION_MOVE_UP_LEFT,
		AVATAR_ACTION_MOVE_DOWN_RIGHT,
		AVATAR_ACTION_MOVE_DOWN_LEFT,
		AVATAR_ACTION_ATTACK_UP,
		AVATAR_ACTION_ATTACK_DOWN,
		AVATAR_ACTION_ATTACK_RIGHT,
		AVATAR_ACTION_ATTACK_LEFT,
		AVATAR_ACTION_ATTACK_UP_RIGHT,
		AVATAR_ACTION_ATTACK_UP_LEFT,
		AVATAR_ACTION_ATTACK_DOWN_RIGHT,
		AVATAR_ACTION_ATTACK_DOWN_LEFT,
		AVATAR_ACTION_DIE
	};

public:
	AvatarModel();
	virtual ~AvatarModel();

public:
	const float getLifePoints(){ return m_lifePoints;}
	void setLifePoints(float lifePoints){ m_lifePoints = lifePoints;}

	virtual AvatarState getState(){return m_state;}
	virtual void setState(AvatarState state){m_state = state;}

	virtual AvatarAction getAction(){return m_action;}
	virtual void setAction(AvatarAction action){m_action  = action; }

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

protected:
	AvatarState m_state;
	AvatarAction m_action;
	Vector4 m_terrainPosition;
	Vector4 m_screenPosition;
	float m_timeout;
	float m_stepX;
	float m_stepY;
	float m_lifePoints;
	int m_pixelWidth;
	int m_pixelHeight;
	Rect m_rect;
};
