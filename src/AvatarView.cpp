#include "AvatarView.h"	
#include <iostream>
#include "MyGL.h"
#include <sstream>



AvatarView::AvatarView()
	: m_curAnim(NULL),
	m_flip(false)
{

}

AvatarView::~AvatarView()
{
//clean anims?
}

void AvatarView::addAnim(const std::string& name, RectangleMesh *mesh)
{
	m_anim.insert(std::pair<std::string, RectangleMesh*>(name, mesh));
	if (m_curAnim == NULL) {
		m_curAnimName = name;
		m_curAnim = mesh;
	}
}
	
void AvatarView::setAnim(const std::string& name)
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


void AvatarView::prepareNewAnim()
{
	if(m_avatarModel->getState() == AvatarModel::AvatarState::AVATAR_STATE_IDLE)
	{
		//we keep displaying the previous animation
	}
	else
	{
		//resetCounters
		m_animCounter = 0;
		m_animDisplayTime = 0;
		m_animReferenceTime = getAnimTimeout();
		
		//set flipping on/off
		if(m_animFlipped[m_avatarModel->getState()])
		{	
			m_flip = true;
		}
		else
		{
			m_flip = false;
		}
		
		setNextAnim();
	}
}

void AvatarView::setNextAnim()
{
	float timeout = m_avatarModel->getTimeout();
	
	//in case the maximum of animations has been reached we start a new round
	/*if(m_animCounter == getNumAnims())
	{
		m_animCounter = 0;
		m_animDisplayTime = 0;
		m_animReferenceTime = getAnimTimeout();
	}*/

	//set the animation
	std::stringstream ss;
	ss<<m_animCounter;
	setAnim(getAnimString() + ss.str());
	

	//if enough time has elapsed we prepare to draw the next animation
	if((m_animDisplayTime) > getAnimTimeout()/getNumAnims())
	{
		m_animCounter++;
		m_animDisplayTime = 0;
		m_animReferenceTime = timeout;
	}
	
	//compute how long the current anim has been displayed
	m_animDisplayTime = m_animReferenceTime - timeout;
}

void AvatarView::draw()
{
	if (m_curAnim == NULL) {
		std::cerr << "W: anim not set" << std::endl;
		return;
	}
	//Primero de todo tenemos que posicionar el avatar dentro de la pantalla
	glPushMatrix();
	//actualizar lo siguiente
	glTranslatef(m_avatarModel->getScreenPosition()[0], m_avatarModel->getScreenPosition()[1], 0);
	if(m_flip)glScalef(-1.0f,1.0f,1.0);
	m_curAnim->draw();
	glPopMatrix();

}


void AvatarView::setAnimString(AvatarModel::AvatarState state, std::string str)
{
	m_animStrings.insert(std::make_pair(state, str));
}

void AvatarView::setNumAnim(AvatarModel::AvatarState state, int numAnim)
{
	m_numAnims.insert(std::make_pair(state, numAnim));
}

void AvatarView::setAnimTimeout(AvatarModel::AvatarState state, float timeout)
{
	m_animTimeouts.insert(std::make_pair(state, timeout ));
}

const std::string AvatarView::getAnimString()
{
	return m_animStrings[m_avatarModel->getState()];
}

const float AvatarView::getNumAnims()
{
	return m_numAnims[m_avatarModel->getState()];
}

const float AvatarView::getAnimTimeout()
{
	return m_animTimeouts[m_avatarModel->getState()];
}

const bool AvatarView::isAnimFlipped()
{
	return  m_animFlipped[m_avatarModel->getState()];
}

void AvatarView::setAnimFlipped(AvatarModel::AvatarState state, bool flipped)
{
	m_animFlipped.insert(std::make_pair(state, flipped ));
}

