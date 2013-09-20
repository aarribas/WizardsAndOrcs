#include "MyGL.h"
#include "MenuPositionRenderer.h"
#include "RectangleMesh.h"

MenuPositionRenderer::MenuPositionRenderer(RectangleMesh* mesh, const float yOffset, const float ySeparator, const float xOffsetDivider, const float width, const float height)
{
	m_mesh = mesh;
	this->yOffset = yOffset;
	this->ySeparator = ySeparator;
	this->height= height;
	xOffset = width/xOffsetDivider;
}

MenuPositionRenderer::~MenuPositionRenderer()
{
};

void MenuPositionRenderer::Render(unsigned char position, std::string currentMenu)
{
	glPushMatrix();

	//logic to translate the mesh according to the position, the sceen settings and the currentMenu
	glTranslatef(xOffset - m_mesh->width()/2 , height - yOffset - position*ySeparator + m_mesh->height()/2, 1.0f);
	m_mesh->draw();
	glPopMatrix();
}
