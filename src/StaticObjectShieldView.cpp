#include "StaticObjectShieldView.h"
#include "Core.h" 

void StaticObjectShieldView::initView(StaticObjectModel* staticObjectModel)
{
	m_staticObjectModel = staticObjectModel;

	//Obtain the atlas key looking up where the mesh is. Could be any mesh.
	m_atlasKey = Core::singleton().textureManager().findAtlas("cshield");
	addAnim("cshield", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("cshield"));
	setAnim("cshield");
}
