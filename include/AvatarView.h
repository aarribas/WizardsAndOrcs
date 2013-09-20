#pragma once
#include <string>
#include "RectangleMesh.h"
#include "Vector4.h"
#include <map>
#include "AvatarModel.h"
#include <string>
class AvatarView
{
public:
	AvatarView();
	virtual ~AvatarView();
public:
	
	virtual void initView(AvatarModel* avatarModel) = 0;
	void addAnim(const std::string& name, RectangleMesh *mesh);
	void prepareNewAnim();
	void setNextAnim();
	void draw();

	const std::string& anim() const { return m_curAnimName; }
	void setAnim(const std::string& name);

	void setScreenPosition(const Vector4& terrainPosition) { m_screenPosition = terrainPosition; }
	const Vector4& getScreenPosition() const { return m_screenPosition; }

	const float getAnimTimeout();
	void setAnimTimeout(AvatarModel::AvatarState state, float timeout);
	
	const float getNumAnims();
	void setNumAnim(AvatarModel::AvatarState state, int numAnim);
	
	const std::string getAnimString();
	void setAnimString(AvatarModel::AvatarState state, std::string str);

	const bool isAnimFlipped();
	void setAnimFlipped(AvatarModel::AvatarState state, bool);

	float getPixelHeight(){return m_curAnim->height();}
	float getPixelWidth(){return m_curAnim->width();}
	
protected:
	std::map<std::string, RectangleMesh*> m_anim;
	std::string m_curAnimName;
	RectangleMesh *m_curAnim;
	Vector4 m_screenPosition;
	std::string m_atlasKey;
	AvatarModel* m_avatarModel;
	int m_animCounter;
	float m_animDisplayTime;
	float m_animReferenceTime;
	std::map<AvatarModel::AvatarState, std::string> m_animStrings;
	std::map<AvatarModel::AvatarState, int> m_numAnims;
	std::map<AvatarModel::AvatarState, float> m_animTimeouts;
	std::map<AvatarModel::AvatarState, bool> m_animFlipped;
	bool m_flip;
};