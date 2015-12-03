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

		// @todo leer el atributo "speed"

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

	bool CAvatarController::accept(const TMessage &message)
	{
		return message._type == Message::CONTROL;

	} // accept
	
	//---------------------------------------------------------

	void CAvatarController::process(const TMessage &message)
	{
		switch(message._type)
		{
		case Message::CONTROL:
			if(!message._string.compare("walk"))
				walk();
			else if(!message._string.compare("walkBack"))
				walkBack();
			else if(!message._string.compare("stopWalk"))
				stopWalk();
			else if(!message._string.compare("strafeLeft"))
				strafeLeft();
			else if(!message._string.compare("strafeRight"))
				strafeRight();
			else if(!message._string.compare("stopStrafe"))
				stopStrafe();
			else if(!message._string.compare("turn"))
				turn(message._float);
		}

	} // process
	
	//---------------------------------------------------------

	void CAvatarController::turn(float amount) 
	{
		// @todo recibimos el giro en radianes que se quiere realizar.
		// Con esto giramos la entidad

	} // turn
	
	//---------------------------------------------------------

	void CAvatarController::walk() 
	{
		// @todo nos informan que se quiere empezar a andar. Se debe seguir
		// andando hasta que se invoque a stopWalk. Deberemos cambiar 
		// la animación ("Walk" es el nombre de la animación de andar) 
		// y actualizar PERIODICAMENTE la posición.

	} // walk
	
	//---------------------------------------------------------

	void CAvatarController::walkBack() 
	{
		// @todo nos informan que se quiere empezar a andar. Se debe seguir
		// andando hasta que se invoque a stopWalk. Deberemos cambiar 
		// la animación ("WalkBack" es el nombre de la animación de 
		// retroceder) y actualizar PERIODICAMENTE la posición.

	} // walkBack
	
	//---------------------------------------------------------

	void CAvatarController::stopWalk() 
	{
		// @todo nos informan que se quiere parar. Deberemos cambiar la
		// animación (la de parado se llama "Idle") y dejar de actualizar
		// periodicamente la posición si nos movíamos hacia delante o
		// detrás

	} // stopWalk
	
	//---------------------------------------------------------

	void CAvatarController::strafeLeft() 
	{
		// @todo nos informan que se quiere empezar a desplazar a la 
		// izquierda. Se debe seguir desplazando hasta que se invoque
		// stopStrafe. Deberemos cambiar la animación ("StrafeLeft"). 
		// y actualizar periodicamente la posición.
		// DEJAR ESTE MÉTODO PARA EL FINAL YA QUE ES SIMILAR A walk()

	} // strafeLeft
	
	//---------------------------------------------------------

	void CAvatarController::strafeRight() 
	{
		// @todo nos informan que se quiere empezar a desplazar a la 
		// derecha. Se debe seguir desplazando hasta que se invoque
		// stopStrafe. Deberemos cambiar la animación ("StrafeRight"). 
		// y actualizar periodicamente la posición.
		// DEJAR ESTE MÉTODO PARA EL FINAL YA QUE ES SIMILAR A walkBack()

	} // strafeRight
	
	//---------------------------------------------------------

	void CAvatarController::stopStrafe() 
	{
		// @todo nos informan que se quiere parar un desplazamiento 
		// lateral. Puede que debamos cambiar la animación (la de parado se 
		// llama "Idle").
		// DEJAR ESTE MÉTODO PARA EL FINAL YA QUE ES SIMILAR A stopWalk()

	} // stopStrafe
	
	//---------------------------------------------------------

	void CAvatarController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		
		// @todo aquí se tendrán que realizar tareas periódicas de 
		// las que no doy más pistas.

		// Si nos estamos desplazando calculamos la próxima posición.
		// Para esto calculamos el vector de movimiento y lo escalamos
		// según la velocidad y el tiempo transcurrido.

		// Aunque no tienen porqué usarse necesariamente aquí, seguramente
		// os vendrán bien métodos que se encuentran en BaseSubsystems::Math

	} // tick

} // namespace Logic

