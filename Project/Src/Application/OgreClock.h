//---------------------------------------------------------------------------
// OgreClock.h
//---------------------------------------------------------------------------

/**
@file OgreClock.h

Contiene la declaraci�n de un temporizador basado en Ogre.

@see Application::COgreClock

@author David Llans�
@date Julio, 2010
*/

#ifndef __Application_OgreClock_H
#define __Application_OgreClock_H

#include "Clock.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Ogre 
{
	class Timer;
}

namespace Application 
{
	/**
	Este temporizador  getTime() que deber� ser implementado en 
	las clases hijas y que devuelve el tiempo desde que se inici� la
	aplicaci�n, y getTimeSinceLastRequest que devuelve el tiempo transcurrido
	desde la �ltima llamada al m�todo. 

	@remarks Esta clase pide en su constructor una instancia del reloj de
	Ogre por lo que BaseSubsystems::CServer dever� haber sido inicializado
	antes de la construcci�n de esta clase.

	@ingroup applicationGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class COgreClock : public IClock
	{
	public:
		/** 
		Constructor de la clase 
		*/
		COgreClock();

		/** 
		Destructor 
		*/
		virtual ~COgreClock() {}

	protected:

		/**
		 M�todo que devuelve la "hora f�sica" del sistema
		 en milisegundos.

		 Utiliza el reloj de Ogre.

		@return Hora en milisegundos.
		*/
		virtual unsigned long getPhysicalTime();

		/**
		Temporizador de Ogre.
		*/
		Ogre::Timer* _timer;

	}; // COgreClock

} // namespace Application

#endif //  __Application_OgreClock_H
