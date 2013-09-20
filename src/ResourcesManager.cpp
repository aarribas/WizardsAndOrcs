#include "ResourcesManager.h"
#include "TextureManager.h"
#include "Core.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


//define default resource directories - must respect the definition order in the ResourceMananger::directories struct
const ResourcesManager::directories ResourcesManager::m_dirs = {
	"resources/level/",
	"resources/map/",
	"resources/png/",
	"resources/sfx/",
	"resources/music/",
	"resources/font/"
};

ResourcesManager::ResourcesManager()
{
	
}

ResourcesManager::~ResourcesManager()
{
}

void ResourcesManager::init()
{

	//clean up?
}


Tmx::Map* ResourcesManager::loadLevelResources(const int level)
{
	//load the level file
	std::string name;
	std::string line;
	std::string levelString;
	int numberOfTextureAtlases, numberOfSfxSounds, numberOfSongs, numberOfFonts;
	Tmx::Map *map = new Tmx::Map();
	std::stringstream s;
	s << level;
	std::ifstream myfile(m_dirs.levelDir + s.str() + ".txt");
	if (myfile.is_open())
	{	
		//read map filename
		getline(myfile, line);
		std::istringstream iss(line);
		iss >> name;

		//load map
		map->ParseFile(m_dirs.mapDir + name + ".tmx");

		if (map->HasError()) 
		{
			std::cerr << "Error Loading Map:" << map->GetErrorCode() << " " << map->GetErrorText().c_str();
			std::cin.get();
			exit(-1);
		}

		getline (myfile,line);
		std::istringstream iss0(line);
		iss0 >> numberOfTextureAtlases;

		for(int i=0; i<numberOfTextureAtlases; i++)
		{
			getline (myfile,line);
			std::istringstream iss(line);
			iss >> name;
			//load texture
			Core::singleton().textureManager().loadAtlas(name, m_dirs.pngDir + name + ".png", m_dirs.pngDir + name + ".txt" );
		}

		getline (myfile,line);
		std::istringstream iss1(line);
		iss1 >> numberOfSfxSounds;
		
		for(int i=0; i<numberOfSfxSounds; i++)
		{
			getline (myfile,line);
			std::istringstream iss(line);
			iss >> name;
			//load sfxFile
			Core::singleton().soundManager().addSound(name, std::string(m_dirs.sfxDir)+ name + ".mp3");
		}

		getline (myfile,line);
		std::istringstream iss2(line);
		iss2 >> numberOfSongs;

		for(int i=0; i<numberOfSongs; i++)
		{
			
			getline (myfile,line);
			std::istringstream iss(line);
			iss >> name;
		
			//load sfxFile
			Core::singleton().soundManager().addSound(name, std::string(m_dirs.musicDir) + name + ".mp3");
		}
	
	
		getline (myfile,line);
		std::istringstream iss3(line);
		iss3 >> numberOfFonts;

		for(int i=0; i<numberOfFonts; i++)
		{
			int height, red, blue, green;
			getline (myfile,line);
			std::istringstream iss(line);
			iss >> name;
			iss >> height;
			iss >> red;
			iss >> green;
			iss >> blue;
			//load font
				Core::singleton().fontManager().loadFont(name, m_dirs.fontDir + name + ".ttf",height,red,green,blue);
		}
	
		myfile.close();
		return map;
	}
	else 
	{
		std::cerr << "Resource file not found" << std::endl;
		exit(-1);
	}
}


void ResourcesManager::unloadLevelResources(const int level)
{
	//TO_DO
	//This is causing temporary memory leaks of course
}


void ResourcesManager::loadIntroStateResources()
{
	Core::singleton().textureManager().loadAtlas("intro", m_dirs.pngDir + "intro" + ".png", m_dirs.pngDir + "intro" + ".txt");
	Core::singleton().soundManager().addSound("intro", std::string(m_dirs.sfxDir)+"intro.wav");
	

}

void ResourcesManager::unloadIntroStateResources()
{
	Core::singleton().textureManager().unLoadAtlas("intro");
	Core::singleton().soundManager().removeSound("intro");
}

void ResourcesManager::loadEndStateResources()
{
	Core::singleton().textureManager().loadAtlas("game_over", m_dirs.pngDir + "game_over" + ".png", m_dirs.pngDir + "game_over" + ".txt");
	Core::singleton().soundManager().addSound("ancient", std::string(m_dirs.musicDir)+"ancient.mp3");
}

void ResourcesManager::unloadEndStateResources()
{
	Core::singleton().textureManager().unLoadAtlas("game_over");
	Core::singleton().soundManager().removeSound("ancient");

}


void ResourcesManager::loadMenuStateResources()
{
	Core::singleton().textureManager().loadAtlas("menu", m_dirs.pngDir + "menu" + ".png", m_dirs.pngDir + "menu" + ".txt");
	Core::singleton().fontManager().loadFont("unselected", m_dirs.fontDir + "LifeCraft_Font" + ".ttf", 16, 255, 255, 0);	
	Core::singleton().fontManager().loadFont("selected", m_dirs.fontDir + "LifeCraft_Font" + ".ttf", 16, 0, 250, 154);	
	Core::singleton().soundManager().addSound("ice", std::string(m_dirs.musicDir)+"ice.mp3");
}

void ResourcesManager::unloadMenuStateResources()
{
	Core::singleton().textureManager().unLoadAtlas("menu");
	Core::singleton().fontManager().unLoad("unselected");
	Core::singleton().fontManager().unLoad("selected");
	
}


