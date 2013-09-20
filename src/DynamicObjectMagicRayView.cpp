#include "DynamicObjectMagicRayView.h"
#include "Core.h"
#include "DynamicObjectMagicRayModel.h"

void DynamicObjectMagicRayView::initView(DynamicObjectModel* dynamicObjectModel)
{
	m_dynamicObjectModel = dynamicObjectModel;

	//Obtain the atlas key looking up where the mesh is. Could be any mesh.
	m_atlasKey = Core::singleton().textureManager().findAtlas("ray-vert-0");
	
	addAnim("ray-vert-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-vert-0"));
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP, "ray-vert-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP, DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP, false);
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN, "ray-vert-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN, DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN, false);
	
	addAnim("ray-horiz-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-horiz-0"));
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_RIGHT, "ray-horiz-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_RIGHT, DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_RIGHT, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_RIGHT, false);
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_LEFT, "ray-horiz-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_LEFT, DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_LEFT, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_LEFT, false);

	
	addAnim("ray-diago-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-diago-0"));
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT, "ray-diago-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT, DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_RIGHT, false);
	
	addAnim("ray-diago-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-diago-0"));
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT, "ray-diago-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT, DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_UP_LEFT, true);

	addAnim("ray-diago-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-diago-0"));
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT, "ray-diago-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT, DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_RIGHT, true);
	
	addAnim("ray-diago-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-diago-0"));
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT, "ray-diago-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT, DynamicObjectMagicRayModel::MOVE_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_MOVE_DOWN_LEFT, false);
		
	addAnim("ray-vanish-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-vanish-0"));
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHING, "ray-vanish-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHING, DynamicObjectMagicRayModel::VANISH_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHING, 1);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_VANISHING, false);

	addAnim("ray-impact-0", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-impact-0"));
	addAnim("ray-impact-1", Core::singleton().textureManager().getTextureAtlas(m_atlasKey)->mesh("ray-impact-1"));
	setAnimString(DynamicObjectModel::DYNAMIC_OBJECT_STATE_IMPACTING, "ray-impact-");
	setAnimTimeout(DynamicObjectModel::DYNAMIC_OBJECT_STATE_IMPACTING, DynamicObjectMagicRayModel::IMPACT_TIMEOUT);
	setNumAnim(DynamicObjectModel::DYNAMIC_OBJECT_STATE_IMPACTING, 2);
	setAnimFlipped(DynamicObjectModel::DYNAMIC_OBJECT_STATE_IMPACTING, false);
	 
	setAnim("ray-horiz-0");
	m_dynamicObjectModel->setPixelWidth(m_curAnim->width());
	m_dynamicObjectModel->setPixelHeight(m_curAnim->height());
}


void DynamicObjectMagicRayView::draw()
{
	if (m_curAnim == NULL) {
		std::cerr << "W: anim not set" << std::endl;
		return;
	}



	/*if(counter !=5)
	{
		counter++;
	}
	else
	{
		counter=0;
	}
	if(counter==0)
	{*/
	//Primero de todo tenemos que posicionar el avatar dentro de la pantalla
	glPushMatrix();
	//actualizar lo siguiente
	glTranslatef(m_dynamicObjectModel->getScreenPosition()[0], m_dynamicObjectModel->getScreenPosition()[1], 0);
	if(m_flip)glScalef(-1.0f,1.0f,1.0);
	m_curAnim->draw();
	glPopMatrix();
	
}