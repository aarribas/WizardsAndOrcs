#pragma once
#include <string>
#include "RectangleMesh.h"
#include "Vector4.h"
#include <map>
#include "DynamicObjectModel.h"
#include <string>
//Attention this should have been merged in an AbstractView not to duplicate code with DynamicObjectView TO_DO
//it is good enough to inherite DynamicObjectView (make DynamicObjectView AbstractDynamicView TO_DO)

class DynamicObjectView
{
public:
	DynamicObjectView();
	virtual ~DynamicObjectView();
public:
	
	virtual void initView(DynamicObjectModel* avatarModel) = 0;
	void addAnim(const std::string& name, RectangleMesh *mesh);
	void prepareNewAnim();
	void setNextAnim();
	virtual void draw();

	const std::string& anim() const { return m_curAnimName; }
	void setAnim(const std::string& name);

	void setScreenPosition(const Vector4& terrainPosition) { m_screenPosition = terrainPosition; }
	const Vector4& getScreenPosition() const { return m_screenPosition; }

	const float getAnimTimeout();
	void setAnimTimeout(DynamicObjectModel::DynamicObjectState state, float timeout);
	
	const float getNumAnims();
	void setNumAnim(DynamicObjectModel::DynamicObjectState state, int numAnim);
	
	const std::string getAnimString();
	void setAnimString(DynamicObjectModel::DynamicObjectState state, std::string str);

	const bool isAnimFlipped();
	void setAnimFlipped(DynamicObjectModel::DynamicObjectState state, bool);

	float getPixelHeight(){return m_curAnim->height();}
	float getPixelWidth(){return m_curAnim->width();}
	
protected:
	std::map<std::string, RectangleMesh*> m_anim;
	std::string m_curAnimName;
	RectangleMesh *m_curAnim;
	Vector4 m_screenPosition;
	std::string m_atlasKey;
	DynamicObjectModel* m_dynamicObjectModel;
	int m_animCounter;
	float m_animDisplayTime;
	float m_animReferenceTime;
	std::map<DynamicObjectModel::DynamicObjectState, std::string> m_animStrings;
	std::map<DynamicObjectModel::DynamicObjectState, int> m_numAnims;
	std::map<DynamicObjectModel::DynamicObjectState, float> m_animTimeouts;
	std::map<DynamicObjectModel::DynamicObjectState, bool> m_animFlipped;
	bool m_flip;
};