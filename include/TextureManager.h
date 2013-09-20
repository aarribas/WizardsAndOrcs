#pragma once

#include <map>
#include <string>
#include "TextureAtlas.h"

class TextureManager
{
public:
	friend class Core;
	TextureManager();
	~TextureManager();

	void init();
	void loadAtlas(const std::string& textureAtlasKey, const std::string& textureFilename, const std::string& atlasFilename );
	void TextureManager::unLoadAtlas(const std::string& textureAtlasKey );
	TextureAtlas* getTextureAtlas(const std::string& textureAtlasKey);
	const std::string findAtlas(const std::string& name);

private:
	std::map<std::string, TextureAtlas*> m_masterTextureAtlas;

};