#include "StaticObjectBootsView.h"
#include "Core.h" 

void StaticObjectBootsView::initView(StaticObjectModel* staticObjectModel)
{
	m_staticObjectModel = staticObjectModel;

	//Obtain the atlas key looking up where the mesh is. Could be any mesh.
	m_atlasKey = Core::singleton().textureManager().findAtlas("cboots");
	addAnim("cboots", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("cboots"));
	setAnim("cboots");
}
