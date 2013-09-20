#include "TextureManager.h"	
#include "TextureAtlas.h"
#include <iostream>

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::init()
{
}

void TextureManager::loadAtlas(const std::string& textureAtlasKey, const std::string& textureFilename, const std::string& atlasFilename)
{
	std::map<std::string, TextureAtlas*>::const_iterator found = m_masterTextureAtlas.find(textureAtlasKey);
	if(found == m_masterTextureAtlas.end())
	{
		TextureAtlas* textureAtlas = new TextureAtlas(textureFilename, atlasFilename);
		m_masterTextureAtlas.insert(std::make_pair(textureAtlasKey, textureAtlas));
		m_masterTextureAtlas[textureAtlasKey]->load();
	}
	else
	{
		std::cerr << "W: TextureAtlas already exists!" << std::endl;
		return;
	}
}

TextureAtlas* TextureManager::getTextureAtlas(const std::string& textureAtlasKey)
{
	std::map<std::string, TextureAtlas*>::const_iterator found = m_masterTextureAtlas.find(textureAtlasKey);

	if (found == m_masterTextureAtlas.end()) {
		std::cerr << "W: TextureAtlas " << textureAtlasKey << " doesn't exist!" << std::endl;
		return NULL;
	}

	return found->second;
}


void TextureManager::unLoadAtlas(const std::string& textureAtlasKey)
{
	std::map<std::string, TextureAtlas*>::const_iterator found = m_masterTextureAtlas.find(textureAtlasKey);

	if (found == m_masterTextureAtlas.end()) {
		std::cerr << "W: TextureAtlas " << textureAtlasKey << " doesn't exist!" << std::endl;
		return;
	}
	else
	{
		found->second->unload();
		m_masterTextureAtlas.erase(found);
	}
}

const std::string TextureManager::findAtlas(const std::string& name)
{
	std::map<std::string, TextureAtlas*>::const_iterator atlasIt = m_masterTextureAtlas.begin();

	while(atlasIt != m_masterTextureAtlas.end())
	{
		if (atlasIt->second->findMesh(name))
		{
			return atlasIt->first;
		}
		else
		{
			atlasIt++;
		}
	}
	
	std::cerr<<"E: No textureAtlas could be found containing the mesh: "<< name;
	std::cin.get();
	exit(0);
}