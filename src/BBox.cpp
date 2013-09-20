#include "BBox.h"
#include "MyGL.h"

BBox::BBox()
{
}

BBox::~BBox()
{
}


void BBox::define(float x1,float y1,float x2 ,float y2,float x3,float y3,float x4,float y4)
{
	m_coords.x1=x1;
	m_coords.x2=x2;
	m_coords.x3=x3;
	m_coords.x4=x4;

	m_coords.y1=y1;
	m_coords.y2=y2;
	m_coords.y3=y3;
	m_coords.y4=y4;

}

void BBox::drawForSprite(float xposition, float yposition, float width, float height, bool inverted)
{
	float x1,x2,x3,x4;

	if (inverted)
	{
		float xorig = xposition + width/2;
		x1= xorig - m_coords.x1*width;
		x2= xorig - m_coords.x2*width;
		x3= xorig - m_coords.x3*width;
		x4= xorig - m_coords.x4*width;
	}
	else
	{
		float xorig = xposition - width/2;
		x1= xorig + m_coords.x1*width;
		x2= xorig + m_coords.x2*width;
		x3= xorig + m_coords.x3*width;
		x4= xorig + m_coords.x4*width;
	}

	float y1=(yposition - height/2) + m_coords.y1*width;
	float y2=(yposition - height/2) + m_coords.y2*width;
	float y3=(yposition - height/2) + m_coords.y3*width;
	float y4=(yposition - height/2) + m_coords.y4*width;
	
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glLineWidth(3.0f);
	glColor4f(1.0f,0.0f,0.0f,1.0f); 
	glBegin(GL_LINES);
	glVertex3f(x1, y1, 1.0f); // origin of the line
	glVertex3f(x2, y2, 1.0f); // ending point of the line
	glVertex3f(x2, y2, 1.0f); // origin of the line
	glVertex3f(x3, y3, 1.0f); // ending point of the line
	glVertex3f(x3, y3, 1.0f); // ending point of the line
	glVertex3f(x4, y4, 1.0f); // ending point of the line
	glVertex3f(x4, y4, 1.0f); // ending point of the line
	glVertex3f(x1, y1, 1.0f); // origin of the line
	glEnd( );
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);


}