#pragma once
#include <string>
#include "RectangleMesh.h"
#include "Vector4.h"
#include <map>
#include "StaticObjectModel.h"
class StaticObjectView
{
public:
	StaticObjectView();
	virtual ~StaticObjectView();
public:
	
	virtual void initView(StaticObjectModel* StaticObjectModel) = 0;
	void draw();
	void addAnim(const std::string& name, RectangleMesh *mesh);
	void setAnim(const std::string& name);
	
	float getPixelHeight(){return m_curAnim->height();}
	float getPixelWidth(){return m_curAnim->width();}
	
protected:
	std::map<std::string, RectangleMesh*> m_anim;
	std::string m_curAnimName;
	RectangleMesh *m_curAnim;
	Vector4 m_screenPosition;
	std::string m_atlasKey;
	StaticObjectModel* m_staticObjectModel;
};