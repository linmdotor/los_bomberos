/**
@file Graphics.cpp

Contiene la implementación del componente que controla la representación
gráfica de la entidad.
 
@see Logic::CGraphics
@see Logic::IComponent

@author David Llansó
@date Agosto, 2010
*/

#include "Graphics.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"
#include "Graphics/Entity.h"
#include "Graphics/StaticEntity.h"

namespace Logic 
{
	IMP_FACTORY(CGraphics);
	
	//---------------------------------------------------------

	CGraphics::~CGraphics() 
	{
		if(_graphicsEntity)
		{
			_scene->removeEntity(_graphicsEntity);
			delete _graphicsEntity;
			_graphicsEntity = 0;
		}

	} // ~CGraphics
	
	//---------------------------------------------------------

	bool CGraphics::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;
		
		_scene = _entity->getMap()->getScene();

		if(entityInfo->hasAttribute("model"))
			_model = entityInfo->getStringAttribute("model");

		_graphicsEntity = createGraphicsEntity(entityInfo);
		if(!_graphicsEntity)
			return false;

		return true;

	} // spawn
	
	//---------------------------------------------------------

	Graphics::CEntity* CGraphics::createGraphicsEntity(const Map::CEntity *entityInfo)
	{
		bool isStatic = false;
		if(entityInfo->hasAttribute("static"))
			isStatic = entityInfo->getBoolAttribute("static");

		if(isStatic)
		{
			_graphicsEntity = new Graphics::CStaticEntity(_entity->getName(),_model);
			if(!_scene->addStaticEntity((Graphics::CStaticEntity*)_graphicsEntity))
				return 0;
		}
		else
		{
			_graphicsEntity = new Graphics::CEntity(_entity->getName(),_model);
			if(!_scene->addEntity(_graphicsEntity))
				return 0;
		}

		_graphicsEntity->setTransform(_entity->getTransform());
		
		return _graphicsEntity;

	} // createGraphicsEntity
	
	//---------------------------------------------------------

	bool CGraphics::accept(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		return messagePtr->m_type == IMessage::MESSAGE_TYPE_SET_TRANSFORM || 
			messagePtr->m_type == IMessage::MESSAGE_TYPE_SET_POSITION;

	} // accept
	
	//---------------------------------------------------------

	void CGraphics::process(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		switch (messagePtr->m_type)
		{
			case IMessage::MESSAGE_TYPE_SET_TRANSFORM:
			{
				MessageTransform *mTransform = (MessageTransform*)messagePtr.get();
				_graphicsEntity->setTransform(mTransform->m_transform);
				break;
			}
			case IMessage::MESSAGE_TYPE_SET_POSITION:
			{
				MessagePosition *mPosition = (MessagePosition*)messagePtr.get();
				_graphicsEntity->setPosition(mPosition->m_position);
				break;
			}
		}

	} // process

} // namespace Logic

