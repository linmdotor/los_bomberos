/**
@file AvatarController.cpp

Contiene la implementaci�n del componente que controla el movimiento 
de la entidad.
 
@see Logic::CAvatarController
@see Logic::IComponent

@author David Llans�
@date Agosto, 2010
*/

#include "AvatarController.h"

#include "Logic/Entity/Entity.h"
#include "Map/MapEntity.h"


namespace Logic 
{
	IMP_FACTORY(CAvatarController);
	
	//---------------------------------------------------------

	bool CAvatarController::spawn(CEntity *entity, CMap *map, const Map::CEntity *entityInfo) 
	{
		if(!IComponent::spawn(entity,map,entityInfo))
			return false;

		// leer el atributo "speed"
		if (entityInfo->hasAttribute("speed"))
			_speed = entityInfo->getFloatAttribute("speed");

		return true;

	} // spawn
	
	//---------------------------------------------------------

	bool CAvatarController::activate()
	{
		return true;
	} // activate
	
	//---------------------------------------------------------

	void CAvatarController::deactivate()
	{

	} // deactivate
	
	//---------------------------------------------------------

	bool CAvatarController::accept(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		return messagePtr->m_type == IMessage::MESSAGE_TYPE_SET_CONTROL;

	} // accept
	
	//---------------------------------------------------------

	void CAvatarController::process(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		switch (messagePtr->m_type)
		{
		case IMessage::MESSAGE_TYPE_SET_CONTROL:
			MessageControl *messageControl = (MessageControl*)messagePtr.get();
			if (!messageControl->m_animation.compare("walk"))
				walk();
			else if (!messageControl->m_animation.compare("walkBack"))
				walkBack();
			else if (!messageControl->m_animation.compare("stopWalk"))
				stopWalk();
			else if (!messageControl->m_animation.compare("strafeLeft"))
				strafeLeft();
			else if (!messageControl->m_animation.compare("strafeRight"))
				strafeRight();
			else if (!messageControl->m_animation.compare("stopStrafe"))
				stopStrafe();
			else if (!messageControl->m_animation.compare("turn"))
				turn(messageControl->m_turn);
		}

	} // process
	
	//---------------------------------------------------------

	void CAvatarController::turn(float amount) 
	{
		// recibimos el giro en radianes que se quiere realizar.
		// Con esto giramos la entidad
		_entity->yaw(amount);
	} // turn
	
	//---------------------------------------------------------

	void CAvatarController::walk() 
	{
		// nos informan que se quiere empezar a andar. Se debe seguir
		// andando hasta que se invoque a stopWalk. Deberemos cambiar 
		// la animaci�n ("Walk" es el nombre de la animaci�n de andar) 
		// y actualizar PERIODICAMENTE la posici�n.
		_walking = true;
		_walkingBack = false;
		MessageSetAnimation *mAnimation = new MessageSetAnimation();
		mAnimation->m_animation = "Walk";//tambi�n tiene run
		mAnimation->m_loop = true;
		_entity->emitMessage(mAnimation, this);
	} // walk
	
	//---------------------------------------------------------

	void CAvatarController::walkBack() 
	{
		// nos informan que se quiere empezar a andar. Se debe seguir
		// andando hasta que se invoque a stopWalk. Deberemos cambiar 
		// la animaci�n ("WalkBack" es el nombre de la animaci�n de 
		// retroceder) y actualizar PERIODICAMENTE la posici�n.
		_walking = false;
		_walkingBack = true;
		MessageSetAnimation *mAnimation = new MessageSetAnimation();
		mAnimation->m_animation = "WalkBack";
		mAnimation->m_loop = true;
		_entity->emitMessage(mAnimation, this);
	} // walkBack
	
	//---------------------------------------------------------

	void CAvatarController::stopWalk() 
	{
		// nos informan que se quiere parar. Deberemos cambiar la
		// animaci�n (la de parado se llama "Idle") y dejar de actualizar
		// periodicamente la posici�n si nos mov�amos hacia delante o
		// detr�s
		_walking = false;
		_walkingBack = false;
		MessageSetAnimation *mAnimation = new MessageSetAnimation();
		if (_strafingLeft)
			mAnimation->m_animation = "StrafeLeft";
		else if (_strafingRight)
			mAnimation->m_animation = "StrafeRight";
		else
			mAnimation->m_animation = "Idle";
		mAnimation->m_loop = true;
		_entity->emitMessage(mAnimation, this);
	} // stopWalk
	
	//---------------------------------------------------------

	void CAvatarController::strafeLeft() 
	{
		// nos informan que se quiere empezar a desplazar a la 
		// izquierda. Se debe seguir desplazando hasta que se invoque
		// stopStrafe. Deberemos cambiar la animaci�n ("StrafeLeft"). 
		// y actualizar periodicamente la posici�n.
		// DEJAR ESTE M�TODO PARA EL FINAL YA QUE ES SIMILAR A walk()
		_strafingLeft = true;
		_strafingRight = false;
		MessageSetAnimation *mAnimation = new MessageSetAnimation();
		mAnimation->m_animation = "StrafeLeft";
		mAnimation->m_loop = true;
		_entity->emitMessage(mAnimation, this);
	} // strafeLeft
	
	//---------------------------------------------------------

	void CAvatarController::strafeRight() 
	{
		// nos informan que se quiere empezar a desplazar a la 
		// derecha. Se debe seguir desplazando hasta que se invoque
		// stopStrafe. Deberemos cambiar la animaci�n ("StrafeRight"). 
		// y actualizar periodicamente la posici�n.
		// DEJAR ESTE M�TODO PARA EL FINAL YA QUE ES SIMILAR A walkBack()
		_strafingLeft = false;
		_strafingRight = true;
		MessageSetAnimation *mAnimation = new MessageSetAnimation();
		mAnimation->m_animation = "StrafeRight";
		mAnimation->m_loop = true;
		_entity->emitMessage(mAnimation, this);
	} // strafeRight
	
	//---------------------------------------------------------

	void CAvatarController::stopStrafe() 
	{
		// nos informan que se quiere parar un desplazamiento 
		// lateral. Puede que debamos cambiar la animaci�n (la de parado se 
		// llama "Idle").
		// DEJAR ESTE M�TODO PARA EL FINAL YA QUE ES SIMILAR A stopWalk()
		_strafingLeft = false;
		_strafingRight = false;
		MessageSetAnimation *mAnimation = new MessageSetAnimation();
		if (_walking)
			mAnimation->m_animation = "Run";
		else if (_walkingBack)
			mAnimation->m_animation = "WalkBack";
		else
			mAnimation->m_animation = "Idle";
		mAnimation->m_loop = true;
		_entity->emitMessage(mAnimation, this);
	} // stopStrafe
	
	//---------------------------------------------------------

	void CAvatarController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		
		// aqu� se tendr�n que realizar tareas peri�dicas de 
		// las que no doy m�s pistas.

		// Si nos estamos desplazando calculamos la pr�xima posici�n.
		// Para esto calculamos el vector de movimiento y lo escalamos
		// seg�n la velocidad y el tiempo transcurrido.

		// Aunque no tienen porqu� usarse necesariamente aqu�, seguramente
		// os vendr�n bien m�todos que se encuentran en BaseSubsystems::Math
		Vector3 dir(0, 0, 0);

		if (_walking)
		{
			dir += Math::getDirection(_entity->getTransform());
		}
		else if (_walkingBack)
		{
			dir -= Math::getDirection(_entity->getTransform());
		}
		if (_strafingLeft)
		{
			dir -= Math::getDirection(_entity->getTransform()).crossProduct(Vector3::UNIT_Y);
		}
		else if (_strafingRight)
		{
			dir += Math::getDirection(_entity->getTransform()).crossProduct(Vector3::UNIT_Y);
		}
		dir.normalise();
		_entity->setPosition(_entity->getPosition() + dir * _speed*msecs);
	} // tick

} // namespace Logic

