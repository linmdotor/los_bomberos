/**
@file Graphics.cpp

Contiene la implementaci�n del componente que controla la representaci�n
gr�fica de la entidad.
 
@see Logic::CGraphics
@see Logic::IComponent

@author David Llans�
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
		// @todo true ante mensajes aceptados. Debe aceptar
		// Mensajes de tipo SET_TRANSFORM.

		return false;

	} // accept
	
	//---------------------------------------------------------

	void CGraphics::process(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		// @todo procesar mensajes aceptados.

	} // process

} // namespace Logic

