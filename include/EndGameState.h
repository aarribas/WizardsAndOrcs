#pragma once

#include "IState.h"
#include "MyGL.h"
#include "TextureAtlas.h"
#include "FreeType.h"
#include <string>

class EndGameState
    : public IState
{

public:
    EndGameState();
    virtual ~EndGameState();

public:
	virtual int width() const { return 1024; }
	virtual int height() const { return 768; }
    virtual void enter();
    virtual void display();
    virtual void reshape(int width, int height);
	virtual void update(const float elapsedTime);
	virtual void leave();

private:
	int m_musicid;
};



