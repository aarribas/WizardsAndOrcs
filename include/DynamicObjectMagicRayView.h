#pragma once
#include "DynamicObjectView.h"
#include "DynamicObjectModel.h" 

class DynamicObjectMagicRayView : public DynamicObjectView
{	
public:
	void initView(DynamicObjectModel* dynamicObjectModel);
	 void draw();
private:
int counter;
};