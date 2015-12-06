//---------------------------------------------------------------------------
// 3DApplication.h
//---------------------------------------------------------------------------

/**
@file 3DApplication.h

Contiene la declaraci�n de la clase aplicacion para aplicaciones
basadas en Ogre. Esta clase maneja la ejecuci�n de todo el juego.

@see Application::C3DApplication
@see Application::CBaseApplication

@author David Llans�
@date Julio, 2010
 */

#ifndef __Application_3DApplication_H
#define __Application_3DApplication_H

#include "BaseApplication.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Application 
{
  class CApplicationState;
}
namespace Graphics 
{
  class CServer;
}
namespace Ogre 
{
  class Timer;
}

namespace Application 
{
	/**
	Clase C3DApplication, que contiene el control de la aplicaci�n
	del juego. Extiende CBaseApplication y su m�quina de estados para
	realizar las tareas de pintado de la escena usando Ogre. Para 
	la interfaz de usuario utiliza OIS y CeGUI.

	@ingroup applicationGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class C3DApplication : public CBaseApplication
	{
	public:
		/**
		Constructor de la clase
		*/
		C3DApplication();

		/**
		Destructor de la aplicaci�n
		*/
		virtual ~C3DApplication();

		/**
		Inicializa la aplicaci�n.

		@return false si la inicializaci�n ha fallado.
		*/
		virtual bool init();

		/**
		Finaliza la aplicaci�n, liberando todos los recursos
		utilizados.
		*/
		virtual void release();

	protected:

		/**
		Funci�n que ejecuta una vuelta del bucle principal
		de la aplicaci�n.

		@param msecs N�mero de milisegundos transcurridos desde
		la �ltima llamada (o desde la activaci�n de la aplicaci�n, 
		en caso de ser la primera vez...).
		*/
		virtual void tick(unsigned int msecs);

	}; // class 3DApplication

} // namespace Application

#endif // __Application_3DApplication_H
