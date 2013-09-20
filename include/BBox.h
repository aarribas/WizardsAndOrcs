#pragma once 

struct bbox_coords
{
	float x1;
	float y1;
	float x2;
	float y2;
	float x3;
	float y3;
	float x4;
	float y4;
};

class BBox
{
friend class LogicHelper;
public:
	BBox();
	~BBox();
public:
	void define(float x1,float y1,float x2 ,float y2,float x3,float y3,float x4,float y4);
	void drawForSprite(float xposition, float yposition, float width, float height, bool inverted);
	
protected:
	bbox_coords m_coords;
};