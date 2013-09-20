#include "StaticObjectGemView.h"
#include "Core.h" 

void StaticObjectGemView::initView(StaticObjectModel* staticObjectModel)
{
	m_staticObjectModel = staticObjectModel;

	//Obtain the atlas key looking up where the mesh is. Could be any mesh.
	m_atlasKey = Core::singleton().textureManager().findAtlas("cgem");
	addAnim("cgem", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("cgem"));
	setAnim("cgem");
}
