//---------------------------------------------------------------------------
// LoadingState.h
//---------------------------------------------------------------------------

/**
@file LoadingState.h

Contiene la declaraci�n del estado de loading.

@see Application::CApplicationState
@see Application::CLoadingState

@author Daniel Parra L�pez
@date Diciembre, 2015
*/

#ifndef __Application_LoadingState_H
#define __Application_LoadingState_H

#include "ApplicationState.h"
#include <string>

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Application 
{
	class CBaseApplication;
}

namespace CEGUI
{
	class EventArgs;
	class Window;
}

namespace Application 
{
	/**
	Esta clase muestra una pantalla de carga mientras se cargan los recursos de la escena

	@ingroup applicationGroup

	@author Daniel Parra L�pez
	@date Diciembre, 2015
	*/
	class CLoadingState : public CApplicationState 
	{
	public:
		/** 
		Constructor de la clase 
		*/
		CLoadingState(CBaseApplication *app) : CApplicationState(app)
				{}

		/** 
		Destructor 
		*/
		virtual ~CLoadingState();

		/**
		Funci�n llamada cuando se crea el estado (se "engancha" en la
		aplicaci�n, para que inicialice sus elementos.

		@return true si todo fue bien.
		*/
		virtual bool init();

		/**
		Funci�n llamada cuando se elimina ("desengancha") el
		estado de la aplicaci�n.
		*/
		virtual void release();

		/**
		Funci�n llamada por la aplicaci�n cuando se activa
		el estado.
		*/
		virtual void activate();

		/**
		Funci�n llamada por la aplicaci�n cuando se desactiva
		el estado.
		*/
		virtual void deactivate();

		/**
		Funci�n llamada por la aplicaci�n para que se ejecute
		la funcionalidad del estado.

		@param msecs N�mero de milisegundos transcurridos desde
		la �ltima llamada (o desde la �ctivaci�n del estado, en caso
		de ser la primera vez...).
		*/
		virtual void tick(unsigned int msecs);


	}; // CMenuState

} // namespace Application

#endif //  __Application_LoadingState_H
