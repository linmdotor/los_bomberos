/**
@file AvatarController.cpp

Contiene la implementación del componente que controla el movimiento 
de la entidad.
 
@see Logic::CAvatarController
@see Logic::IComponent

@author David Llansó
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
		// la animación ("Walk" es el nombre de la animación de andar) 
		// y actualizar PERIODICAMENTE la posición.
		_walking = true;
		_walkingBack = false;
		MessageSetAnimation *mAnimation = new MessageSetAnimation();
		mAnimation->m_animation = "Walk";//también tiene run
		mAnimation->m_loop = true;
		_entity->emitMessage(mAnimation, this);
	} // walk
	
	//---------------------------------------------------------

	void CAvatarController::walkBack() 
	{
		// nos informan que se quiere empezar a andar. Se debe seguir
		// andando hasta que se invoque a stopWalk. Deberemos cambiar 
		// la animación ("WalkBack" es el nombre de la animación de 
		// retroceder) y actualizar PERIODICAMENTE la posición.
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
		// animación (la de parado se llama "Idle") y dejar de actualizar
		// periodicamente la posición si nos movíamos hacia delante o
		// detrás
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
		// stopStrafe. Deberemos cambiar la animación ("StrafeLeft"). 
		// y actualizar periodicamente la posición.
		// DEJAR ESTE MÉTODO PARA EL FINAL YA QUE ES SIMILAR A walk()
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
		// stopStrafe. Deberemos cambiar la animación ("StrafeRight"). 
		// y actualizar periodicamente la posición.
		// DEJAR ESTE MÉTODO PARA EL FINAL YA QUE ES SIMILAR A walkBack()
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
		// lateral. Puede que debamos cambiar la animación (la de parado se 
		// llama "Idle").
		// DEJAR ESTE MÉTODO PARA EL FINAL YA QUE ES SIMILAR A stopWalk()
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
		
		
		// aquí se tendrán que realizar tareas periódicas de 
		// las que no doy más pistas.

		// Si nos estamos desplazando calculamos la próxima posición.
		// Para esto calculamos el vector de movimiento y lo escalamos
		// según la velocidad y el tiempo transcurrido.

		// Aunque no tienen porqué usarse necesariamente aquí, seguramente
		// os vendrán bien métodos que se encuentran en BaseSubsystems::Math
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

