#pragma once

#include <map>
#include <string>
#include "FreeType.h"

class FontManager
{
public:
	friend class Core;
	FontManager();
	~FontManager();

	void init();
	void loadFont(const std::string& fontKey, const std::string& fontFilename, unsigned int height, unsigned int red, unsigned int green, unsigned int blue);
	freetype::font_data* getFont(const std::string& fontKey);
	void FontManager::unLoad(const std::string& fontKey);
private:
	std::map<std::string, freetype::font_data*> m_fonts;

};