#pragma once
#include "DynamicObjectModel.h"

class DynamicObjectMagicRayModel : public DynamicObjectModel
{
public:
	static const float CELERITY;
	static const float MOVE_TIMEOUT;
	static const float IMPACT_TIMEOUT;
	static const float VANISH_TIMEOUT;

public:
	float getCelerity() {return CELERITY;}

};