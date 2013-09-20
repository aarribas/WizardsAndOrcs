#include "HUDView.h"
#include "Core.h"
#include <sstream>
HUDView::HUDView():
m_visibility(true)
{
}

HUDView::~HUDView()
{
}

void HUDView::init(PlayerModel* playerModel)
{
	m_playerModel = playerModel;
}

void HUDView::draw()
{

	//09/09/12 The following positions are hardcoded due to  lack of time

	//show life and face
	glPushMatrix();
	glTranslatef(42, glutGet(GLUT_WINDOW_HEIGHT)-42, 0.0f);
	Core::singleton().textureManager().getTextureAtlas("items")->mesh("face")->draw();
	glPopMatrix();
	std::stringstream ss;
	ss<<(int)m_playerModel->getLifePoints();
	freetype::print(*Core::singleton().fontManager().getFont("LifeCraft_Font"), 80, glutGet(GLUT_WINDOW_HEIGHT)-64,  ss.str().c_str());

	if(m_visibility)
	{
		//show life potions 
		glPushMatrix();
		glTranslatef(42, glutGet(GLUT_WINDOW_HEIGHT)-42 -70 , 1.0f);
		Core::singleton().textureManager().getTextureAtlas("items")->mesh("potion")->draw();
		glPopMatrix();
		std::stringstream ss1;
		ss1<<m_playerModel->getInventory()->getPotions();
		freetype::print(*Core::singleton().fontManager().getFont("LifeCraft_Font"), 80, glutGet(GLUT_WINDOW_HEIGHT)-64-70,  ss1.str().c_str());

		//show  shield and protection
		glPushMatrix();
		glTranslatef(glutGet(GLUT_WINDOW_WIDTH)/6+42, glutGet(GLUT_WINDOW_HEIGHT)-42 , 1.0f);
		Core::singleton().textureManager().getTextureAtlas("items")->mesh("shield")->draw();
		glPopMatrix();
		std::stringstream ss2;
		ss2<<m_playerModel->getInventory()->getProtection();
		freetype::print(*Core::singleton().fontManager().getFont("LifeCraft_Font"), glutGet(GLUT_WINDOW_WIDTH)/6+80, glutGet(GLUT_WINDOW_HEIGHT)-64,  ss2.str().c_str());

		//show coins
		glPushMatrix();
		glTranslatef(glutGet(GLUT_WINDOW_WIDTH)/6+42, glutGet(GLUT_WINDOW_HEIGHT)-42 -70, 1.0f);
		Core::singleton().textureManager().getTextureAtlas("items")->mesh("coins")->draw();
		glPopMatrix();
		std::stringstream ss3;
		ss3<<m_playerModel->getInventory()->getCoins();
		freetype::print(*Core::singleton().fontManager().getFont("LifeCraft_Font"), glutGet(GLUT_WINDOW_WIDTH)/6+80, glutGet(GLUT_WINDOW_HEIGHT)-64-70,  ss3.str().c_str());

		//show boots
		glPushMatrix();
		glTranslatef(glutGet(GLUT_WINDOW_WIDTH)/3+42, glutGet(GLUT_WINDOW_HEIGHT)-42, 1.0f);
		Core::singleton().textureManager().getTextureAtlas("items")->mesh("boots")->draw();
		glPopMatrix();
		std::stringstream ss4;
		ss4<<m_playerModel->getInventory()->getBoots();
		freetype::print(*Core::singleton().fontManager().getFont("LifeCraft_Font"), glutGet(GLUT_WINDOW_WIDTH)/3+80, glutGet(GLUT_WINDOW_HEIGHT)-64,  ss4.str().c_str());


		//show gems
		glPushMatrix();
		glTranslatef(glutGet(GLUT_WINDOW_WIDTH)/3+42, glutGet(GLUT_WINDOW_HEIGHT)-42 -70 , 1.0f);
		Core::singleton().textureManager().getTextureAtlas("items")->mesh("bloodgem")->draw();
		glPopMatrix();
		glPushMatrix();
		glPopMatrix();
		std::stringstream ss5;
		ss5<<m_playerModel->getInventory()->getGems();	
		freetype::print(*Core::singleton().fontManager().getFont("LifeCraft_Font"), glutGet(GLUT_WINDOW_WIDTH)/3+80, glutGet(GLUT_WINDOW_HEIGHT)-64-70,  ss5.str().c_str());

	}
}