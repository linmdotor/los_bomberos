/**
@file EntityId.cpp

Contiene la implementaci�n del tipo de identificaci�n de entidades y una 
funci�n para generaci�n de nuevos IDs.
 
@see Logic::TEntityID
@see Logic::EntityID

@author David Llans�
@date Agosto, 2010
*/

#include "EntityID.h"

#include <cassert>

namespace Logic 
{
	TEntityID EntityID::_nextId = EntityID::FIRST_ID;

	//---------------------------------------------------------

	TEntityID EntityID::NextID() 
	{
		TEntityID ret = _nextId;
		assert(ret != EntityID::UNASSIGNED && "Se han asignado todos los identificadores posibles.");
		_nextId++;
		return ret;

	} // NextEntityId

}; // namespace Logic
