#include "StaticObjectCoinsView.h"
#include "Core.h" 

void StaticObjectCoinsView::initView(StaticObjectModel* staticObjectModel)
{
	m_staticObjectModel = staticObjectModel;

	//Obtain the atlas key looking up where the mesh is. Could be any mesh.
	m_atlasKey = Core::singleton().textureManager().findAtlas("ccoins");
	addAnim("ccoins", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ccoins"));
	setAnim("ccoins");
}
