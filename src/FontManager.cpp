#include "FontManager.h"	
#include <iostream>

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
}

void FontManager::init()
{
}

void FontManager::loadFont(const std::string& fontKey, const std::string& fontFilename, unsigned int height, unsigned int red, unsigned int green, unsigned int blue)
{
	std::map<std::string, freetype::font_data*>::const_iterator found = m_fonts.find(fontKey);
	if(found == m_fonts.end())
	{
		freetype::font_data* tempFont = new freetype::font_data();
		tempFont->init((fontFilename).c_str(), height, red, green, blue);
		m_fonts.insert(std::make_pair(fontKey, tempFont));
	}
	else
	{
		std::cerr << "W: Font already exists!" << std::endl;
		return;
	}
}

freetype::font_data* FontManager::getFont(const std::string& fontKey)
{
	std::map<std::string, freetype::font_data*>::const_iterator found = m_fonts.find(fontKey);

	if (found == m_fonts.end()) {
		std::cerr << "W: Font doesn't exist!" << std::endl;
		return NULL;
	}

	return found->second;
}

void FontManager::unLoad(const std::string& fontKey)
{
	std::map<std::string, freetype::font_data*>::const_iterator found = m_fonts.find(fontKey);

	if (found == m_fonts.end()) {
		std::cerr << "W: Font doesn't exist!" << std::endl;
		return;
	}
	else
	{
		found->second->clean();
		m_fonts.erase(found);
	}
}