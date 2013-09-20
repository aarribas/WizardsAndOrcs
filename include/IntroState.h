#pragma once

#include "IState.h"
#include "MyGL.h"
#include "TextureAtlas.h"
#include "FreeType.h"

class IntroState
    : public IState
{

public:
    IntroState();
    virtual ~IntroState();

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
	float m_introCount;
	freetype::font_data m_intro_font;
	int m_blinker;
};



