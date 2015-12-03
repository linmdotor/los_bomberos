//---------------------------------------------------------------------------
// ExitState.h
//---------------------------------------------------------------------------

/**
@file ExitState.h

Contiene la declaraci�n de un estado muy sencillo e independiente
de la plataforma, que provoca la terminaci�n de la aplicaci�n.

@see Application::CApplicationState
@see Application::CExitState

@author Marco Antonio G�mez Mart�n & David Llans�
@date Julio, 2010
*/

#ifndef __Application_ExitState_H
#define __Application_ExitState_H

#include "ApplicationState.h"

namespace Application 
{
	class CBaseApplication;
}

namespace Application 
{
	/**
	Clase CExitState; representa el estado de la aplicaci�n
	que provoca su terminaci�n inmediata.
	
	@ingroup applicationGroup

	@author Marco Antonio G�mez Mart�n & David Llans�
	@date Julio, 2010
	*/
	class CExitState : public CApplicationState 
	{
	public:
		/** 
		Constructor de la clase 
		*/
		CExitState(CBaseApplication *app) : CApplicationState(app) {}

		/** 
		Destructor 
		*/
		virtual ~CExitState() {}

		/**
		Funci�n llamada por la aplicaci�n cuando se activa
		el estado.
		*/
		virtual void activate() 
		{
			CApplicationState::activate();
			this->_app->exitRequest();
		}

	}; // CExitState

} // namespace Application

#endif // __Application_ExitState_H
