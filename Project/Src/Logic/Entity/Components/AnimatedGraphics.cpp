/**
@file AnimatedGraphics.cpp

Contiene la implementaci�n del componente que controla la representaci�n
gr�fica de una entidad est�tica.
 
@see Logic::CAnimatedGraphics
@see Logic::IComponent

@author David Llans�
@date Agosto, 2010
*/

#include "AnimatedGraphics.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Maps/Map.h"
#include "Map/MapEntity.h"

#include "Graphics/Scene.h"

namespace Logic 
{
	IMP_FACTORY(CAnimatedGraphics);
	
	//---------------------------------------------------------

	Graphics::CEntity* CAnimatedGraphics::createGraphicsEntity(const Map::CEntity *entityInfo)
	{
		_animatedGraphicsEntity = new Graphics::CAnimatedEntity(_entity->getName(),_model);
		if(!_scene->addEntity(_animatedGraphicsEntity))
			return 0;

		_animatedGraphicsEntity->setTransform(_entity->getTransform());
		
		if(entityInfo->hasAttribute("defaultAnimation"))
		{
			_defaultAnimation = entityInfo->getStringAttribute("defaultAnimation");
			_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
			_animatedGraphicsEntity->setObserver(this);
		}

		return _animatedGraphicsEntity;

	} // createGraphicsEntity
	
	//---------------------------------------------------------

	bool CAnimatedGraphics::accept(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		// @todo true ante mensajes aceptados. CAnimatedGraphics es un 
		// componente un tanto especial ya que extiende a el componente
		// CGraphics. Por este motivo devemos devolver true ante los 
		// mensajes que aceptan tanto uno como otro. Debe aceptar
		// Mensajes de tipo SET_ANIMATION y STOP_ANIMATION.

		return CGraphics::accept(messagePtr) /* || ... || ...*/;

	} // accept
	
	//---------------------------------------------------------

	void CAnimatedGraphics::process(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		CGraphics::process(messagePtr);

		// @todo procesar mensajes aceptados.

	} // process
	
	//---------------------------------------------------------
	
	void CAnimatedGraphics::animationFinished(const std::string &animation)
	{
		// Si acaba una animaci�n y tenemos una por defecto la ponemos
		_animatedGraphicsEntity->stopAllAnimations();
		_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
	}

} // namespace Logic

