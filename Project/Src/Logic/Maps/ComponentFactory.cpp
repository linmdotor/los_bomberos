/**
@file ComponentFactory.cpp

Contiene la implementaci�n de la clase CComponentFactory, Singleton que almacena 
los punteros a funci�n de funciones de creaci�n componentes (IComponent).

@see Logic::CComponentFactory
@see BaseSubsystems::CFactory
@see Logic::CComponent

@author David Llans�
@date Julio, 2010
*/
#include "ComponentFactory.h"
#include "Logic/Entity/Component.h"

#include <cassert>

namespace Logic {

	CComponentFactory* CComponentFactory::_instance = 0;

	//--------------------------------------------------------

	CComponentFactory::CComponentFactory() : CFactory()
	{
		_instance = this;

	} // CComponentFactory

	//--------------------------------------------------------

	CComponentFactory::~CComponentFactory()
	{
		_instance = 0;

	} // ~CComponentFactory
	
	//--------------------------------------------------------

	CComponentFactory* CComponentFactory::getSingletonPtr()
	{
		if(!_instance)
			new CComponentFactory();

		return _instance;

	} // Init

} // namespace Logic
