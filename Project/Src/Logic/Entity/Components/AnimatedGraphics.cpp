/**
@file AnimatedGraphics.cpp

Contiene la implementación del componente que controla la representación
gráfica de una entidad estática.
 
@see Logic::CAnimatedGraphics
@see Logic::IComponent

@author David Llansó
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

		return CGraphics::accept(messagePtr) || messagePtr->m_type == IMessage::MESSAGE_TYPE_SET_ANIMATION
			|| messagePtr->m_type == IMessage::MESSAGE_TYPE_STOP_ANIMATION;

	} // accept
	
	//---------------------------------------------------------

	void CAnimatedGraphics::process(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		CGraphics::process(messagePtr);
		switch (messagePtr->m_type)
		{
			case IMessage::MESSAGE_TYPE_SET_ANIMATION:
			{
				MessageSetAnimation *mAnimation = (MessageSetAnimation*)messagePtr.get();
				_animatedGraphicsEntity->setAnimation(mAnimation->m_animation, mAnimation->m_loop);
				break;
			}
			case IMessage::MESSAGE_TYPE_STOP_ANIMATION:
			{
				_animatedGraphicsEntity->stopAllAnimations();
				break;
			}
		}

	} // process
	
	//---------------------------------------------------------
	
	void CAnimatedGraphics::animationFinished(const std::string &animation)
	{
		// Si acaba una animación y tenemos una por defecto la ponemos
		_animatedGraphicsEntity->stopAllAnimations();
		_animatedGraphicsEntity->setAnimation(_defaultAnimation,true);
	}

} // namespace Logic

