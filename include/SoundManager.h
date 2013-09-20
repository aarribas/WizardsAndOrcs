#pragma once
#include "FMODManager.h"


class SoundManager
{
private:
	static FMODManager m_fmodManager;
public:
	friend class Core;
	SoundManager();
	~SoundManager();

	void init();
	 
    void update();

    void addSound(const std::string &name, const std::string &filename);

	void removeSound(const std::string &name);

	int playSfx(const std::string &name);
	
	int playSong(const std::string &name);

	void stopSfxOrSong(int id);

	
};