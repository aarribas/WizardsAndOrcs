#pragma once

#include "IState.h"
#include "MyGL.h"
#include "TextureAtlas.h"
#include "FreeType.h"
#include <string>
#include <vector>
#include <map>
#include "MenuPositionRenderer.h"
#include "Settings.h"

class MenuState
    : public IState
{

public:
	static const float Y_SEPARATOR;
	static const float Y_OFFSET;
	static const float X_OFFSET_DIVIDER;
	static const float Y_TITLE_OFFSET;

public:
    MenuState();
    virtual ~MenuState();

// ConcretGame implementation
public:
	virtual int width() const { return 1024; }
	virtual int height() const { return 768; }
    virtual void enter();
    virtual void display();
    virtual void reshape(int width, int height);
	virtual void update(const float elapsedTime);
	virtual void leave();

private:
	void buildMenu();
	void drawTextMenu();

private:
	TextureAtlas *m_mainTextureAtlas;
	TextureAtlas *m_fontTextureAtlas;
	RectangleMesh* m_menuBgMesh;
	freetype::font_data m_menu_unselectedFont, m_menu_selectedFont;;
	std::map<std::string, std::vector<std::string>> m_menu;
	std::string m_currentMenu;
	unsigned char m_menuPosition;
	MenuPositionRenderer *m_menuPositionRenderer;
	float m_toggleTime;
	Settings* m_settings;
	bool m_selectedOn;
	int m_musicid;
};


