#pragma once

#include <string>

class RectangleMesh;

class MenuPositionRenderer
{
public:
	MenuPositionRenderer();
	MenuPositionRenderer(
		RectangleMesh* mesh, 
		const float yOffset,		
		const float ySeparator,  
		const float xOffsetDivider, 
		float width, 
		float height);

	virtual ~MenuPositionRenderer();

	void Render(unsigned char position, std::string currentMenu);

private:
	RectangleMesh* m_mesh;
	float yOffset, xOffset, ySeparator;
	float height;
};