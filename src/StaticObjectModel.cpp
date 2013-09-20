#include "StaticObjectModel.h"

StaticObjectModel::StaticObjectModel(StaticObjectType type)
{
	m_staticObjectType  = type;
	switch(type)
	{
	case STATIC_OBJECT_TYPE_COINS:
		m_staticObjectState = STATIC_OBJECT_TO_BE_COLLECTED;
		break;
	case STATIC_OBJECT_TYPE_SHIELD:
		m_staticObjectState = STATIC_OBJECT_TO_BE_COLLECTED;
		break;
	case STATIC_OBJECT_TYPE_GEM:
		m_staticObjectState = STATIC_OBJECT_TO_BE_COLLECTED;
		break;
	case STATIC_OBJECT_TYPE_LIFE_POTION:
		m_staticObjectState = STATIC_OBJECT_TO_BE_COLLECTED;
		break;
	case STATIC_OBJECT_TYPE_BOOTS:
		m_staticObjectState = STATIC_OBJECT_TO_BE_COLLECTED;
		break;
	case STATIC_OBJECT_TYPE_DECORATION:
		m_staticObjectState = STATIC_OBJECT_CANNOT_BE_COLLECTED;
		break;
	}
}

StaticObjectModel::~StaticObjectModel()
{
}

