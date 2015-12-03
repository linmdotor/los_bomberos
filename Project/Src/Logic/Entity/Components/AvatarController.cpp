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
		// la animaci�n ("Walk" es el nombre de la animaci�n de andar) 
		// y actualizar PERIODICAMENTE la posici�n.

	} // walk
	
	//---------------------------------------------------------

	void CAvatarController::walkBack() 
	{
		// @todo nos informan que se quiere empezar a andar. Se debe seguir
		// andando hasta que se invoque a stopWalk. Deberemos cambiar 
		// la animaci�n ("WalkBack" es el nombre de la animaci�n de 
		// retroceder) y actualizar PERIODICAMENTE la posici�n.

	} // walkBack
	
	//---------------------------------------------------------

	void CAvatarController::stopWalk() 
	{
		// @todo nos informan que se quiere parar. Deberemos cambiar la
		// animaci�n (la de parado se llama "Idle") y dejar de actualizar
		// periodicamente la posici�n si nos mov�amos hacia delante o
		// detr�s

	} // stopWalk
	
	//---------------------------------------------------------

	void CAvatarController::strafeLeft() 
	{
		// @todo nos informan que se quiere empezar a desplazar a la 
		// izquierda. Se debe seguir desplazando hasta que se invoque
		// stopStrafe. Deberemos cambiar la animaci�n ("StrafeLeft"). 
		// y actualizar periodicamente la posici�n.
		// DEJAR ESTE M�TODO PARA EL FINAL YA QUE ES SIMILAR A walk()

	} // strafeLeft
	
	//---------------------------------------------------------

	void CAvatarController::strafeRight() 
	{
		// @todo nos informan que se quiere empezar a desplazar a la 
		// derecha. Se debe seguir desplazando hasta que se invoque
		// stopStrafe. Deberemos cambiar la animaci�n ("StrafeRight"). 
		// y actualizar periodicamente la posici�n.
		// DEJAR ESTE M�TODO PARA EL FINAL YA QUE ES SIMILAR A walkBack()

	} // strafeRight
	
	//---------------------------------------------------------

	void CAvatarController::stopStrafe() 
	{
		// @todo nos informan que se quiere parar un desplazamiento 
		// lateral. Puede que debamos cambiar la animaci�n (la de parado se 
		// llama "Idle").
		// DEJAR ESTE M�TODO PARA EL FINAL YA QUE ES SIMILAR A stopWalk()

	} // stopStrafe
	
	//---------------------------------------------------------

	void CAvatarController::tick(unsigned int msecs)
	{
		IComponent::tick(msecs);
		
		
		// @todo aqu� se tendr�n que realizar tareas peri�dicas de 
		// las que no doy m�s pistas.

		// Si nos estamos desplazando calculamos la pr�xima posici�n.
		// Para esto calculamos el vector de movimiento y lo escalamos
		// seg�n la velocidad y el tiempo transcurrido.

		// Aunque no tienen porqu� usarse necesariamente aqu�, seguramente
		// os vendr�n bien m�todos que se encuentran en BaseSubsystems::Math

	} // tick

} // namespace Logic

