
#include "Core.h"
#include "MenuState.h"
#include <time.h>
#include <iostream>
#include "FreeType.h"
#include "MyText.h"

const float MenuState::Y_SEPARATOR=30.0f;
const float MenuState::Y_OFFSET = 125.0f;
const float MenuState::X_OFFSET_DIVIDER = 8.0f;
const float MenuState::Y_TITLE_OFFSET = 50.0f;

MenuState::MenuState()
{
}

MenuState::~MenuState()
{

	
}

void MenuState::enter()
{
	
	Core::singleton().resourcesManager().loadMenuStateResources();
	m_musicid  =  Core::singleton().soundManager().playSong("ice");
	m_currentMenu = "main";
	m_menuPosition = 0;
	m_toggleTime=0;
	m_selectedOn=false;

	m_settings = Core::singleton().settingsManager().getSettings();

	buildMenu();

	m_menuPositionRenderer = new MenuPositionRenderer(Core::singleton().textureManager().getTextureAtlas("menu")->mesh("marker"), Y_OFFSET, Y_SEPARATOR, X_OFFSET_DIVIDER, width(), height());
}

void MenuState::buildMenu()
{
	std::vector<std::string> mainMenu;
	mainMenu.resize(4);
	mainMenu[0] = ". Play"; 
	mainMenu[1] = ". Settings"; 
	mainMenu[2] = ". Credits"; 
	mainMenu[3] = ". Exit"; 
	m_menu["main"] = mainMenu; 

	std::vector<std::string> settingsMenu;

	settingsMenu.resize(5);

	settingsMenu[0] = ". Sfx Sounds:  " + m_settings->sfxOnToString(); 
	settingsMenu[1] = ". Fight Music:  " +  m_settings->musicOnToString(); 
	settingsMenu[2] = ". Difficulty:  " +  m_settings->difficultyToString();  
	settingsMenu[3] = ". Save";
	settingsMenu[4] = ". Back"; 

	m_menu["settings"] = settingsMenu; 

	std::vector<std::string> creditsMenu;
	creditsMenu.resize(2);
	creditsMenu[0] = "Andres Arribas - UOC - 2012"; 
	creditsMenu[1] = ". Back"; 

	m_menu["credits"] = creditsMenu; 
	
}
void MenuState::display()
{
	//Cada vez que hay que redibujar la pantalla, primero limpiamos los buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	
	//draw background
	glPushMatrix();
	glTranslatef(width()/2.0f, height()/2.0f, 0);
	Core::singleton().textureManager().getTextureAtlas("menu")->mesh("menu_background")->draw();
	glPopMatrix();

	//draw game title
	//myText::drawText(m_fontTextureAtlas,"street#fighter",width()/X_OFFSET_DIVIDER,height()-Y_TITLE_OFFSET,1.0f);
	
	//draw menu text
	drawTextMenu();

	//draw menu position marker
	m_menuPositionRenderer->Render(m_menuPosition, m_currentMenu);

	glutSwapBuffers();
}

void MenuState::drawTextMenu()
{
	
	

	//draw truetype based text
	for(unsigned int i=0; i < m_menu[m_currentMenu].size(); i++)
	{
		if(m_selectedOn == true && i == m_menuPosition)
		{
			freetype::print(*Core::singleton().fontManager().getFont("selected"), width()/X_OFFSET_DIVIDER, height()-Y_OFFSET - Y_SEPARATOR*(i),  m_menu[m_currentMenu][i].c_str());
		}
		else
		{
			freetype::print(*Core::singleton().fontManager().getFont("unselected"), width()/X_OFFSET_DIVIDER, height()-Y_OFFSET - Y_SEPARATOR*(i),  m_menu[m_currentMenu][i].c_str());
		}
	}
}

void MenuState::reshape(int width, int height)
{
		//reshape window
	glViewport(0, 0, (GLsizei)width, (GLsizei)height); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, this->width()*(3.0f/4.0f)*((float)width/(float)height), 0, this->height());
	glMatrixMode(GL_MODELVIEW);
}

void MenuState::update(const float elapsedTime)
{
	//Obtenemos la referencias al raton y al teclado
	OIS::Mouse* mouse = Core::singleton().inputManager().getMouse();
	OIS::Keyboard* keyboard = Core::singleton().inputManager().getKeyboard();
	int ntime = glutGet(GLUT_ELAPSED_TIME);

	//Comprobamos si se ha pulsado la tecla ESC para salir del juego
	if( (ntime - m_toggleTime) > 200)
	{
		if (keyboard->isKeyDown(OIS::KC_ESCAPE))
			exit(-1);
		if (keyboard->isKeyDown(OIS::KC_RETURN))
		{
			m_toggleTime = ntime;
			if(m_currentMenu == "main")
			{
				if(m_menuPosition == 0)
				{
					Core::singleton().gameProgressManager().setGameProgressState(GameProgressManager::LOADING_LEVEL);
					Core::singleton().stateManager().changeTo("game");
					
				}

				if(m_menuPosition == 1) 
				{
					m_currentMenu = "settings";
					m_menuPosition = 0;
					return;

				}
				if(m_menuPosition == 2)
				{
					m_currentMenu = "credits";
					m_menuPosition = 1;
					return;
				}
				if(m_menuPosition == 3)
				{
					exit(0);
				}
			}
			else if (m_currentMenu == "settings")
			{
			
				if(m_menuPosition == 0)
				{
					m_selectedOn=!m_selectedOn;
				}	
				if(m_menuPosition == 1)
				{
					m_selectedOn=!m_selectedOn;
				}
				if(m_menuPosition == 2)
				{
					m_selectedOn=!m_selectedOn;
				}	
				if(m_menuPosition == 3)
				{
					//Core::singleton().settingsManager().setSettings(m_settings);
					//!! no more save needed!!!!!
					return;
				}	
				if(m_menuPosition == 4)
				{
					m_currentMenu = "main";
					m_menuPosition = 0;
					
					buildMenu();
					return;
				}
			
			}
			else if ( m_currentMenu == "credits")
			{
				m_currentMenu = "main";
				m_menuPosition = 2;
				return;
			}
		}

		if(m_selectedOn == false)
		{
			//change the menu position when pressing DOWN. Up to bottom of menu (maximum pos)
			if (keyboard->isKeyDown(OIS::KC_DOWN))
			{
				m_toggleTime = ntime;

				if(m_currentMenu == "main")
				{
					if(m_menuPosition < 3) m_menuPosition++;
				}
				if(m_currentMenu == "settings")
				{
					if(m_menuPosition < 4) m_menuPosition++;
				}
			}

			//change the menu position when pressing UP. Up to top of menu (minimum pos)
			if (keyboard->isKeyDown(OIS::KC_UP))
			{
				m_toggleTime = ntime;
				if(m_currentMenu == "main")
				{
					if(m_menuPosition > 0) m_menuPosition--;
				}
				if(m_currentMenu == "settings")
				{
					if(m_menuPosition > 0) m_menuPosition--;
				}
				if(m_currentMenu == "credits")
				{
					//no change of position allowed.
				}
			}
		}
		else
		{
			if (keyboard->isKeyDown(OIS::KC_SPACE))
			{
				m_toggleTime = ntime;
				
				if(m_menuPosition == 0)
				{
					m_settings->switchSfxOnOff();
					buildMenu();
				}	
				if(m_menuPosition == 1)
				{
					m_settings->switchMusicOnOff();
					buildMenu();
				}
				if(m_menuPosition == 2)
				{
					m_settings->difficultyIncrease();
					buildMenu();
				}
			}
		}
	}
}

void MenuState::leave()
{
	Core::singleton().soundManager().stopSfxOrSong(m_musicid);
	Core::singleton().resourcesManager().unloadMenuStateResources();
	
}
