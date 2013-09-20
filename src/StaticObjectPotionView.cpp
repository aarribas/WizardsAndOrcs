#include "StaticObjectPotionView.h"
#include "Core.h" 

void StaticObjectPotionView::initView(StaticObjectModel* staticObjectModel)
{
	m_staticObjectModel = staticObjectModel;

	//Obtain the atlas key looking up where the mesh is. Could be any mesh.
	m_atlasKey = Core::singleton().textureManager().findAtlas("cpotion");
	addAnim("cpotion", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("cpotion"));
	setAnim("cpotion");
}
