#include "StaticObjectView.h"	
#include <iostream>
#include "MyGL.h"
#include <sstream>

StaticObjectView::StaticObjectView()
	: m_curAnim(NULL)
{

}

StaticObjectView::~StaticObjectView()
{
//clean anims?
}

void StaticObjectView::addAnim(const std::string& name, RectangleMesh *mesh)
{
	m_anim.insert(std::pair<std::string, RectangleMesh*>(name, mesh));
	if (m_curAnim == NULL) {
		m_curAnimName = name;
		m_curAnim = mesh;
	}
}

	
void StaticObjectView::setAnim(const std::string& name)
{
	std::map<std::string, RectangleMesh*>::const_iterator found = m_anim.find(name);
	if (found == m_anim.end()) {
		std::cerr << "E: anim not found " << name << std::endl;
		return;
	}
	m_curAnimName = found->first;
	m_curAnim = found->second;
}

void StaticObjectView::draw()
{
	if (m_curAnim == NULL) {
		std::cerr << "W: anim not set" << std::endl;
		return;
	}
	
	glPushMatrix();
	glTranslatef(m_staticObjectModel->getScreenPosition()[0], m_staticObjectModel->getScreenPosition()[1], 0);
	m_curAnim->draw();
	glPopMatrix();

}