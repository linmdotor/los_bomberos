//---------------------------------------------------------------------------
// GaleonApplication.cpp
//---------------------------------------------------------------------------

/**
@file GaleonApplication.cpp

Contiene la implementaci�n de la clase aplicacion para aplicaciones
basadas en Ogre. Esta clase maneja la ejecuci�n de todo el juego.

@see Application::CGaleonApplication
@see Application::C3DApplication

@author David Llans�
@date Septiembre, 2010
*/
#include "GaleonApplication.h"

#include "ExitState.h"
#include "MenuState.h"
#include "GameState.h"
#include "LoadingState.h"


namespace Application {

	CGaleonApplication::CGaleonApplication() : C3DApplication()
	{

	} // CGaleonApplication

	//--------------------------------------------------------

	CGaleonApplication::~CGaleonApplication()
	{

	} // ~CGaleonApplication

	//--------------------------------------------------------

	bool CGaleonApplication::init() 
	{
		// Inicializamos la clase de la que heredamos.
		if (!C3DApplication::init())
			return false;

		// Creamos los estados. La aplicaci�n se hace responsable de
		// destruirlos.
		if(!addState("menu", new CMenuState(this)))
			return false;
		
		if (!addState("loading", new CLoadingState(this)))
			return false;

		if(!addState("exit", new CExitState(this)))
			return false;

		if(!setState("menu"))
			return false;


		return true;

	} // init

	//--------------------------------------------------------

	void CGaleonApplication::release()
	{
		// Desactivamos y eliminamos todos los estados.
		releaseAllStates();

		C3DApplication::release();

	} // release

} // namespace Application
