#include "SoundManager.h"	
#include "Core.h"
#include <iostream>
FMODManager SoundManager::m_fmodManager;

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	
}

void SoundManager::init()
{
	m_fmodManager.init();
}

void SoundManager::update()
{
	m_fmodManager.update();
}

 void SoundManager::addSound(const std::string &name, const std::string &filename)
 {
	 m_fmodManager.addSound(name,filename);
 }
 void SoundManager::removeSound(const std::string &name)
 {
	 m_fmodManager.removeSound(name);
 
 }
int SoundManager::playSfx(const std::string &name)
{
	if(Core::singleton().settingsManager().getSettings()->isSfxOn())
	{
	int id = m_fmodManager.playSound(name);
	m_fmodManager.getChannel(id)->setPaused(false);
	m_fmodManager.getChannel(id)->setVolume(Core::singleton().settingsManager().getSettings()->getSfxVolume());
	return id;
	}
	else
	{
		return -1;
	}

}
	
int SoundManager::playSong(const std::string &name)
{
	if(Core::singleton().settingsManager().getSettings()->isMusicOn())
	{
		int id = m_fmodManager.playSound(name);
		m_fmodManager.getChannel(id)->setPaused(false);
		m_fmodManager.getChannel(id)->setLoopCount(1000);
		m_fmodManager.getChannel(id)->setVolume(Core::singleton().settingsManager().getSettings()->getMusicVolume());
		return id;
	}
	else
	{
		return -1;
	}

}


void SoundManager::stopSfxOrSong(int id)
{
	m_fmodManager.getChannel(id)->stop();	
}
