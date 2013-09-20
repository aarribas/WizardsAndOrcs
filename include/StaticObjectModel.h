#pragma once
#include "Vector4.h"
#include "BasicLogicDefinitions.h"
class StaticObjectModel
{
public:
	typedef struct {
		float left,top,
		right,bottom;
	} Rect;

	enum StaticObjectState {
		STATIC_OBJECT_CANNOT_BE_COLLECTED,
		STATIC_OBJECT_TO_BE_COLLECTED,
		STATIC_OBJECT_COLLECTED
	};

	//The below is a simplification. We do not create separate classes for static objects
	//It is ok to do so for the time being since there are few objects and not much 
	//complexity/logic attached to them

		enum StaticObjectType {
		STATIC_OBJECT_TYPE_COINS,
		STATIC_OBJECT_TYPE_SHIELD,
		STATIC_OBJECT_TYPE_GEM,
		STATIC_OBJECT_TYPE_BOOTS,
		STATIC_OBJECT_TYPE_LIFE_POTION,
		STATIC_OBJECT_TYPE_DECORATION
	};



public:
	StaticObjectModel(StaticObjectType type);
	virtual ~StaticObjectModel();

public:

	void setTerrainPosition(const Vector4& terrainPosition) { m_terrainPosition = terrainPosition; }
	const Vector4& getTerrainPosition() const { return m_terrainPosition; }
	
	const Vector4 getScreenPosition() const { return m_terrainPosition*PIXELS_PER_METER; }
	
	void setScreenPosition(const Vector4& screenPosition) { m_terrainPosition = screenPosition * (float)(1/ (float)PIXELS_PER_METER); }

	void setRect(const Rect rect){ m_rect = rect; }
	const Rect getRect(){return m_rect;}
	
	void setStaticObjectState(StaticObjectState state){m_staticObjectState = state;}
	const StaticObjectState getStaticObjectState(){return m_staticObjectState;}
	const StaticObjectType getStaticObjectType(){return m_staticObjectType;}
	
	void setPixelWidth(int width){ m_pixelWidth = width; }
	const int getPixelWidth(){return m_pixelWidth;}
	
	void setPixelHeight(int height){ m_pixelHeight = height; }
	const int getPixelHeight(){return m_pixelHeight;}

protected:
	StaticObjectType m_staticObjectType;
	StaticObjectState m_staticObjectState;
	Rect m_rect;
	Vector4 m_terrainPosition;
	int m_pixelWidth;
	int m_pixelHeight;
};
