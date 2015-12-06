//---------------------------------------------------------------------------
// ApplicationState.h
//---------------------------------------------------------------------------

/**
@file ApplicationState.h

Contiene la declaraci�n de la clase que representa un estado de la
aplicacion.

@see Application::CApplicationState
@see Application::CBaseApplication

@author Marco Antonio G�mez Mart�n & David Llans�
@date Julio, 2010
*/

#ifndef __Application_ApplicationState_H
#define __Application_ApplicationState_H

#include "BaseApplication.h"
#include "GUI/InputManager.h"

namespace Application 
{
	/**
	Clase CApplicationState; representa un estado de la 
	aplicaci�n, como el estado del men�, o el estado jugando,
	etc.
	Distintos estados estar�n implementados como clases hijas
	de esta.
	
	@ingroup applicationGroup

	@author Marco Antonio G�mez Mart�n & David Llans�
	@date Julio, 2010
	*/
	class CApplicationState : public GUI::CKeyboardListener, 
							  public GUI::CMouseListener
	{
	public:
		/** 
		Constructor de la clase 

		@param app Aplicacion a la que pertenece el estado.
		*/
		CApplicationState(CBaseApplication *app) : _app(app) {};

		/** 
		Destructor 
		*/
		virtual ~CApplicationState() {}

		/**
		Funci�n llamada cuando se crea el estado (se "engancha" en la
		aplicaci�n, para que inicialice sus elementos.

		@return true si todo fue bien.
		*/
		virtual bool init() {return true;}

		/**
		Funci�n llamada cuando se elimina ("desengancha") el
		estado de la aplicaci�n.
		*/
		virtual void release() {}

		/**
		Funci�n llamada por la aplicaci�n cuando se activa
		el estado.
		*/
		virtual void activate() {}

		/**
		Funci�n llamada por la aplicaci�n cuando se desactiva
		el estado.
		*/
		virtual void deactivate() {}

		/**
		Funci�n llamada por la aplicaci�n para que se ejecute
		la funcionalidad del estado.

		@param msecs N�mero de milisegundos transcurridos desde
		la �ltima llamada (o desde la �ctivaci�n del estado, en caso
		de ser la primera vez...).
		*/
		virtual void tick(unsigned int msecs) {}

		// M�todos de CKeyboardListener
		
		/**
		M�todo que ser� invocado siempre que se pulse una tecla. 
		Ser� la aplicaci�n qui�n llame a este m�todo cuando el 
		estado est� activo. Esta clase NO se registra en el 
		InputManager sino que es la aplicaci�n quien lo hace y 
		delega en los estados. Por defecto no se capturan 
		pulsaciones.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool keyPressed(GUI::TKey key) {return false;}
		
		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de una tecla. Ser� la aplicaci�n qui�n llame a este m�todo 
		cuando el estado est� activo. Esta clase NO se registra en
		el InputManager sino que es la aplicaci�n quien lo hace y 
		delega en los estados. Por defecto no se capturan fin de
		pulsaciones.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool keyReleased(GUI::TKey key) {return false;}

		// M�todos de CMouseListener
		
		/**
		M�todo que ser� invocado siempre que se mueva el rat�n. La
		aplicaci�n avisa de este evento al estado actual. Por defecto 
		no se capturan movimiento del rat�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool mouseMoved(const GUI::CMouseState &mouseState)
														{return false;}
		
		/**
		M�todo que ser� invocado siempre que se pulse un bot�n. La
		aplicaci�n avisa de este evento al estado actual.Por defecto 
		no se capturan pulsaciones.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool mousePressed(const GUI::CMouseState &mouseState)
														{return false;}

		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de un bot�n. La aplicaci�n avisa de este evento al estado 
		actual.Por defecto no se capturan fin de pulsaciones.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners. 
		*/
		virtual bool mouseReleased(const GUI::CMouseState &mouseState)
														{return false;}

	protected:
		/**
		Puntero a la aplicaci�n a la que pertenece el estado
		*/
		CBaseApplication *_app;

	}; // CApplicationState

} // namespace Application

#endif //  __Application_ApplicationState_H
