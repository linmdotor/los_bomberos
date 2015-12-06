//---------------------------------------------------------------------------
// BaseApplication.h
//---------------------------------------------------------------------------

/**
@file BaseApplication.h

Contiene la declaraci�n de la clase aplicacion, que maneja la ejecuci�n
de todo el juego.

@see Application::CBaseApplication
@see Application::CApplicationState

@author Marco Antonio G�mez Mart�n & David Llans�
@date Julio, 2010
*/

#ifndef __Application_BaseApplication_H
#define __Application_BaseApplication_H

#include "GUI/InputManager.h"

#include <map>
#include <string>
#include <cassert>

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Application 
{
  class CApplicationState;
  class IClock;
}

/**
Namespace con todo lo relacionado con la aplicaci�n: clase abstracta, 
estados, etc. Es el coraz�n del juego, el encargado de inicializar
el resto de sistemas necesarios para la ejecuci�n del juego.
(para m�s informaci�n ver @ref applicationGroup).

@author Marco Antonio G�mez Mart�n & David Llans�
@date Julio, 2010
*/
namespace Application 
{
	/**
	Clase CBaseApplication, que contiene el control de la aplicaci�n
	del juego, implementando una m�quina de estados de aplicaci�n.

	Las clases que heredan de esta se preocupar�n de inicializar
	los subsistemas necesarios para esa aplicaci�n concreta
	(subsistema gr�fico, etc.), as� como de la creaci�n de los estados
	que componen la aplicaci�n.

	@remarks Las clases que implementen est� clase <em>deben</em> inicializar el
	reloj (_clock).
	
	@ingroup applicationGroup

	@author Marco Antonio G�mez Mart�n & David Llans�
	@date Julio, 2010
	*/
	class CBaseApplication : public GUI::CKeyboardListener,
							 public GUI::CMouseListener
	{
	public:
		/**
		Constructor de la clase
		*/
		CBaseApplication();

		/**
		Destructor de la aplicaci�n
		*/
		virtual ~CBaseApplication();

		/**
		Devuelve la aplicaci�n instanciada. La clase
		implementa el patr�n singleton, pero a trav�s del
		constructor, es decir, se deber� hacer un <code>new</code>
		expl�citamente (o declarar una variable global o local; en definitiva
		que se llame al constructor de la clase). Ese objeto creado
		ser� el que devuelva este m�todo.

		@return Puntero a la aplicaci�n instanciada.
		*/
		static CBaseApplication *getSingletonPtr() {return _instance;}

		/**
		Inicializa la aplicaci�n. En depuraci�n se comprueba que la aplicaci�n
		se inicialice solo una vez.

		@return false si la inicializaci�n ha fallado.
		*/
		virtual bool init();

		/**
		Finaliza la aplicaci�n, liberando todos los recursos utilizados. En 
		depuraci�n se comprueba que la aplicaci�n est� inicializada.
		*/
		virtual void release();

		/**
		Libera y elimina todos los estados de la aplicaci�n.
		*/
		virtual void releaseAllStates();

		/**
		Funci�n de ejecuci�n de la aplicaci�n. Aqu� se encuentra la ejecuci�n 
		del bucle principal, que se repite hasta que alguien solicite su 
		terminaci�n. En el bucle simplemente se comprueba si hay que realizar
		una transici�n de estado, si es as� se hace efectivo el cambio. Tras 
		est� se hace el tick() para la actualizaci�n de la vuelta.
		*/
		virtual void run();

		/**
		Esta funci�n es llamada cuando alguien externo a la
		aplicaci�n (normalmente un estado), desea que la aplicaci�n
		termine. Esta funci�n est� pensada para ser llamada mientras
		el m�todo run() est� en ejecuci�n. Al terminar la vuelta actual
		se finalizar� la aplicaci�n.
		*/
		void exitRequest() {_exit = true;}

		/**
		Funci�n para averiguar si alguien ha solicitado a la aplicaci�n
		su terminaci�n.

		@return Devuelve si la aplicaci�n debe terminar con la vuelta
		del bucle actual.
		*/
		bool exitRequested() {return _exit;}

		// FUNCIONES ASOCIADAS CON LOS ESTADOS

		/**
		A�ade un estado a la aplicaci�n. La aplicaci�n acepta la
		responsabilidad de borrar el estado al finalizar la aplicaci�n.

		@param name Nombre del estado
		@param newState Estado a a�adir. La aplicaci�n se encargar�
		de eliminarlo al finalizar.
		@return true si todo fue bien.
		*/
		bool addState(const std::string &name,
						CApplicationState *newState);

		/**
		Establece el estado de la aplicaci�n, a partir de su nombre. La 
		acci�n <em>no</em> es inmediata, sino que se realizar� en la siguiente
		vuelta del bucle principal de la aplicaci�n.

		@param name Nombre del estado.
		@return Devuelve cierto si el estado solicitado existe. Si el
		estado no existe, <em>no</em> hay un cambio efectivo del estado.
		*/
		bool setState(const std::string &name);

		/**
		Devuelve el estado actual de la aplicaci�n.

		@return Estado actual de la aplicaci�n.
		*/
		CApplicationState *getState() {return _currentState;}

		/**
		Devuelve el tiempo de la aplicaci�n.

		@return Tiempo que la aplicaci�n lleva activa.
		*/
		unsigned int getAppTime();

		// M�todos de CKeyboardListener
		
		/**
		M�todo que ser� invocado siempre que se pulse una tecla. La
		aplicaci�n avisa de este evento al estado actual.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool keyPressed(GUI::TKey key);
		
		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de una tecla. La aplicaci�n avisa de este evento al estado 
		actual.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool keyReleased(GUI::TKey key);

		// M�todos de CMouseListener
		
		/**
		M�todo que ser� invocado siempre que se mueva el rat�n. La
		aplicaci�n avisa de este evento al estado actual.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool mouseMoved(const GUI::CMouseState &mouseState);
		
		/**
		M�todo que ser� invocado siempre que se pulse un bot�n. La
		aplicaci�n avisa de este evento al estado actual.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners.
		*/
		virtual bool mousePressed(const GUI::CMouseState &mouseState);

		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de un bot�n. La aplicaci�n avisa de este evento al estado 
		actual.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners. 
		*/
		virtual bool mouseReleased(const GUI::CMouseState &mouseState);

	protected:

		/**
		Realiza un cambio de estado, avisando al estado saliente
		y al estado entrante del hecho.
		*/
		void changeState();

		/**
		Funci�n que ejecuta una vuelta del bucle principal
		de la aplicaci�n.

		@param msecs N�mero de milisegundos transcurridos desde
		la �ltima llamada (o desde la �ctivaci�n de la aplicaci�n, 
		en caso de ser la primera vez...).
		*/
		virtual void tick(unsigned int msecs);

		/**
		Instancia �nica de la aplicaci�n.
		*/
		static CBaseApplication *_instance;

		/**
		Indica si la aplicaci�n ha sido inicializada
		*/
		bool _initialized;

		/**
		Tipo de datos tabla de estados. Es una tabla hash
		de las STL.
		*/
		typedef std::map<std::string, CApplicationState*> TStateTable;

		/**
		Tabla hash con todos los estados de la aplicaci�n
		*/
		TStateTable _states;

		/**
		Puntero al estado actual
		*/
		CApplicationState *_currentState;

		/**
		Puntero al estado objetivo. Alguien externo a la apliaci�n
		ha solicitado un cambio de estado que a�n no se ha hecho
		efectivo.
		*/
		CApplicationState *_nextState;

		/**
		Indica si la aplicaci�n terminar� al final de la vuelta
		del bucel actual.
		*/
		bool _exit;

		/**
		Temporizador que lleva la cuenta del tiempo desde que se 
		inici� la aplicaci�n.
		*/
		IClock *_clock;

	}; // class BaseApplication

} // namespace Application

#endif // __Application_BaseApplication_H
