#pragma once

#include "MyGL.h"
#include "TextureAtlas.h"
#include <string>

namespace myText
{
	void drawText(TextureAtlas* fontTextureAtlas, const std::string& text, float xpos, float ypos, float zPos);
	void drawTextCentered(TextureAtlas* fontTextureAtlas, const std::string& text, float xpos, float ypos, float zPos);
}
