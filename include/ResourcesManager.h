#pragma once
#include "TmxParser/Tmx.h"
#include <string>

class ResourcesManager
{
public:
	struct directories
	{
		std::string levelDir;
		std::string mapDir;
		std::string pngDir;
		std::string sfxDir;
		std::string musicDir;
		std::string fontDir;
		
	};
public:
	friend class Core;
	ResourcesManager();
	~ResourcesManager();
	void init();

	Tmx::Map* loadLevelResources(const int level);
	void unloadLevelResources(const int level);
	
	void loadIntroStateResources();
	void unloadIntroStateResources();

	void loadEndStateResources();
	void unloadEndStateResources();

	
	void loadMenuStateResources();
	void unloadMenuStateResources();

private:
	static const directories m_dirs;
};