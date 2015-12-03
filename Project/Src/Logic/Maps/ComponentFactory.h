/**
@file ComponentFactory.h

Contiene la declaraci�n de la clase CComponentFactory, Singleton que almacena 
los punteros a funci�n de funciones de creaci�n componentes (IComponent).

@see Logic::CComponentFactory
@see BaseSubsystems::CFactory
@see Logic::CComponent

@author David Llans�
@date Julio, 2010
*/
#ifndef __Logic_ComponentFactory_H
#define __Logic_ComponentFactory_H

#include "BaseSubsystems/Factory.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class IComponent;
}

// Declaraci�n de la clase
namespace Logic
{
	/**
	Factor�a de componentes. Extiende la plantilla BaseSubsystems::CFactory
	para IComponent haciendo de ella un singleton por lo que solo habr� una 
	instancia de esta clase.
	<p>
	Es usada para almacenar componentes 
	en Logic::CEntityFactory donde todo el registro de componentes se realiza 
	utilizando macros del preprocesador declarados en Logic::CComponent.

	@ingroup logicGroup
	@ingroup mapGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CComponentFactory : public BaseSubsystems::CFactory<IComponent*>
	{
	public:

		/**
		Devuelve la �nica instancia de la clase CComponentFactory.
		
		@return �nica instancia de la clase CComponentFactory.
		*/
		static CComponentFactory* getSingletonPtr();

		/**
		Destructor.
		*/
		~CComponentFactory();

	protected:
		/**
		Constructor.
		*/
		CComponentFactory ();

	private:
		/**
		�nica instancia de la clase.
		*/
		static CComponentFactory* _instance;

	}; // class CComponentFactory

} // namespace Logic

#endif // __Logic_ComponentFactory_H
