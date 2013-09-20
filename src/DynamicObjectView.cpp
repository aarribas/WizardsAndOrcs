#include "DynamicObjectView.h"

#include "DynamicObjectView.h"	
#include <iostream>
#include "MyGL.h"
#include <sstream>



DynamicObjectView::DynamicObjectView()
	: m_curAnim(NULL),
	m_flip(false)
{

}

DynamicObjectView::~DynamicObjectView()
{
	//clean anims?
}

void DynamicObjectView::addAnim(const std::string& name, RectangleMesh *mesh)
{
	m_anim.insert(std::pair<std::string, RectangleMesh*>(name, mesh));
	if (m_curAnim == NULL) {
		m_curAnimName = name;
		m_curAnim = mesh;
	}
}

void DynamicObjectView::setAnim(const std::string& name)
{
	std::map<std::string, RectangleMesh*>::const_iterator found = m_anim.find(name);
	if (found == m_anim.end()) {
		std::cerr << "E: anim not found " << name << std::endl;
		return;
	}
	//Si la hemos encontrado la marcamos como activa
	m_curAnimName = found->first;
	m_curAnim = found->second;
}


void DynamicObjectView::prepareNewAnim()
{

	//resetCounters
	m_animCounter = 0;
	m_animDisplayTime = 0;
	m_animReferenceTime = getAnimTimeout();

	//set flipping on/off
	if(m_animFlipped[m_dynamicObjectModel->getState()])
	{	
		m_flip = true;
	}
	else
	{
		m_flip = false;
	}

	setNextAnim();

}

void DynamicObjectView::setNextAnim()
{
	//float timeout = m_dynamicObjectModel->getTimeout();

	//set the animation
	std::stringstream ss;
	ss<<m_animCounter;
	setAnim(getAnimString() + ss.str());

	/*
	//if enough time has elapsed we prepare to draw the next animation
	if((m_animDisplayTime) > getAnimTimeout()/getNumAnims())
	{
		m_animCounter++;
		m_animDisplayTime = 0;
		m_animReferenceTime = timeout;
	}

	//compute how long the current anim has been displayed
	m_animDisplayTime = m_animReferenceTime - timeout;
	*/
	
}

void DynamicObjectView::draw()
{
	if (m_curAnim == NULL) {
		std::cerr << "W: anim not set" << std::endl;
		return;
	}
	//Primero de todo tenemos que posicionar el avatar dentro de la pantalla
	glPushMatrix();
	//actualizar lo siguiente
	glTranslatef(m_dynamicObjectModel->getScreenPosition()[0], m_dynamicObjectModel->getScreenPosition()[1], 0);
	if(m_flip)glScalef(-1.0f,1.0f,1.0);
	m_curAnim->draw();
	glPopMatrix();

}


void DynamicObjectView::setAnimString(DynamicObjectModel::DynamicObjectState state, std::string str)
{
	m_animStrings.insert(std::make_pair(state, str));
}

void DynamicObjectView::setNumAnim(DynamicObjectModel::DynamicObjectState state, int numAnim)
{
	m_numAnims.insert(std::make_pair(state, numAnim));
}

void DynamicObjectView::setAnimTimeout(DynamicObjectModel::DynamicObjectState state, float timeout)
{
	m_animTimeouts.insert(std::make_pair(state, timeout ));
}

const std::string DynamicObjectView::getAnimString()
{
	return m_animStrings[m_dynamicObjectModel->getState()];
}

const float DynamicObjectView::getNumAnims()
{
	return m_numAnims[m_dynamicObjectModel->getState()];
}

const float DynamicObjectView::getAnimTimeout()
{
	return m_animTimeouts[m_dynamicObjectModel->getState()];
}

const bool DynamicObjectView::isAnimFlipped()
{
	return  m_animFlipped[m_dynamicObjectModel->getState()];
}

void DynamicObjectView::setAnimFlipped(DynamicObjectModel::DynamicObjectState state, bool flipped)
{
	m_animFlipped.insert(std::make_pair(state, flipped ));
}

