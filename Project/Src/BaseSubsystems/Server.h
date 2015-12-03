//---------------------------------------------------------------------------
// Server.h
//---------------------------------------------------------------------------

/**
@file Server.h

Contiene la declaraci�n de la clase principal que engloba los subsistemas
usados. La mayor�a de ellos son parte de Ogre.

@see BaseSubsystems::CServer

@author David Llans�
@date Julio, 2010
*/

#ifndef __BaseSubsystems_Server_H
#define __BaseSubsystems_Server_H

/**
Si se define la siguiente directiva, en modo ventana el juego no toma rat�n
y teclado como como de uso exclusivo sino que se sigue viendo el del OS y se
pueden usar en otras ventanas. Por defecto en debug se usa el rat�n del OS.
*/
#ifdef _DEBUG
#define NON_EXCLUSIVE_MODE_IN_WINDOW_MODE
#endif // _DEBUG

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Ogre 
{
	class Root;
	class Timer;
	class RenderWindow;
}

namespace OIS
{
	class InputManager;
	class Mouse;
	class Keyboard;
}

namespace CEGUI
{
	class XMLParser;
	class System;
}

namespace BaseSubsystems
{
	class WindowEventListener;
}

/**
Namespace con todo lo que rodea la aplicaci�n. Engloba los sistemas 
externos en los que se apoya la aplicaci�n, o clases que los inicializan.
(para m�s informaci�n ver @ref baseSubsystemsGroup).

@author David Llans�
@date Julio, 2010
*/
namespace BaseSubsystems 
{
	/**
	Clase central que se encarga de inicializar y gestionar los diferentes
	subsistemas necesarios para correr la aplicaci�n. Su misi�n principal es 
	la de inicializar los subsistemas de Ogre, OIS, etc. y hacerlos accesibles 
	al resto de proyectos de la soluci�n.
	<p>
	En esta clase es donde se ocultan los detalles engorrosos de la creaci�n
	y destrucci�n de los recursos necesarios para que luego el resto de 
	proyectos de la soluci�n puedan acceder a ellos de forma f�cil sin
	preocuparse.
	<p>
	De la parte de Ogre se encarga de la carga de los diferentes plugins, de
	la carga de los resursos, de la inicializaci�n del sistema de render y de
	la creaci�n de la ventana de renderizado. Ofrece m�todos accesores a las
	diferentes instancias y modificadores como el del tama�o de la pantalla.
	Tambi�n da acceso al temporizador de Ogre, usado por la aplicaci�n para 
	gestionar los tiempos del juego.
	<p>
	En la parte de OIS crea el sistema de gesti�n de perif�ricos de entrada,
	un buffer para el teclado y otro para el rat�n. Ofrece m�todos accesores a 
	las diferentes instancias y modificadores como el del tama�o de la pantalla,
	que pone el rango de actuaci�n del rat�n.
	<p>
	Est� implementado como un Singleton; se debe llamar a su m�todo Init(), para
	que la instancia est� creada. Al final de la aplicaci�n, habr� que llamar
	a Release().

	@author David Llans�
	@date Julio, 2010
	@ingroup baseSubsystemsGroup
	*/
	class CServer 
	{
	public:

		/**
		Devuelve la �nica instancia de la clase.

		@return Puntero al gestor de subsistemas.
		*/
		static BaseSubsystems::CServer *getSingletonPtr() { return _instance; }
		/**
		Inicializa los diferentes subsistemas.

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera el gestor de subsistemas. Debe llamarse al finalizar la 
		aplicaci�n.
		*/
		static void Release();

		/**
		Devuelve el temporizador de la aplicaci�n.

		@return Temporizados de la aplicaci�n.
		*/
		Ogre::Timer* getAppTimer();

		/**
		Devuelve el punto de entrada a Ogre.

		@return Puntero al punto de entrada a Ogre.
		*/
		Ogre::Root *getOgreRoot() {return _root;}

		/**
		Devuelve la ventana de reenderizado.

		@return Puntero a la actual ventana de reenderizado.
		*/
		Ogre::RenderWindow *getRenderWindow() {return _renderWindow;}

		/**
		Devuelve propiedades de la ventana de reenderizado.

		@param width Ancho de la ventana de reenderizado en pixels.
		Si no hay ventana devuelve -1.
		@param height Alto de la ventana de reenderizado en pixels.
		Si no hay ventana devuelve -1.
		*/
		void getWindowExtents(unsigned int &width, unsigned int &height);
		
		/**
		Devuelve el identificador de la ventana de reenderizado sobre
		la que estamos trabajando.

		@return Identificador de la ventana de reenderizado sobre la
		que estamos trabajando. Si no hay ventana devuelve -1.
		*/
		const unsigned int getWindowHnd();

		/**
		Devuelve el sistema de gesti�n de perif�ricos de entrada de 
		OIS.

		@return Puntero al sistema de gesti�n de perif�ricos de 
		entrada de OIS.
		*/
		OIS::InputManager *getInputSystem() {return _inputSystem;}

		/**
		Devuelve la instancia OIS del buffer del rat�n.

		@return Instancia del buffer del rat�n.
		*/
		OIS::Mouse* getBufferedMouse(){return _mouse;}
		
		/**
		Devuelve la instancia OIS del buffer del teclado.

		@return Instancia del buffer del teclado.
		*/
		OIS::Keyboard* getBufferedKeyboard(){return _keyboard;}

		/**
		Devuelve el sistema de la interfaz gr�fica de usuario CEGUI.

		@return Puntero al sistema de la interfaz gr�fica de usuario 
		CEGUI.
		*/
		CEGUI::System *getGUISystem() {return _GUISystem;}

	protected:

		/**
		Constructor de la clase.
		*/
		CServer();

		/**
		Destructor de la aplicaci�n.
		*/
		virtual ~CServer();

		/**
		Segunda fase de la construcci�n del objeto. Sirve para hacer
		inicializaciones de la propia instancia en vez de inicializaciones 
		est�ticas.

		@return true si todo fue correctamente.
		*/
		bool open();

		/**
		Segunda fase de la destrucci�n del objeto. Sirve para liberar 
		los recursos de la propia instancia, la liberaci�n de los recursos 
		est�ticos se hace en Release().
		*/
		void close();

		/**
		Inicializaci�n de Ogre.

		@return true si todo fue correctamente.
		*/
		bool initOgre();

		/**
		Inicializaci�n de OIS.

		@return true si todo fue correctamente.
		*/
		bool initOIS();

		/**
		Inicializaci�n de CEGUI.

		@return true si todo fue correctamente.
		*/
		bool initCEGUI();

		/**
		Liberaci�n de Ogre.
		*/
		void releaseOgre();

		/**
		Liberaci�n de Ogre.
		*/
		void releaseOIS();

		/**
		Liberaci�n de CEGUI.
		*/
		void releaseCEGUI();

		/**
		M�todo que carga los recursos Ogre especificados en el fichero de 
		configuraci�n.
		*/
		void setupOgreResources();

		/**
		Carga los ajustes de configudaci�n de Ogre. Si estos no existen, o 
		se fuerza a ello, se lanza una ventana de configuraci�n

		@param force Indica si se quiere mostrar la pantalla de configuraci�n sin
		intentar cargar los valores de disco.
		@return true si de una u otra forma se pudieron cargar los ajustes.
		*/
		bool configureOgre(bool force = false);

		/**
		Una vez cargados los recursos del archivo de configuraci�n de Ogre se inicializa 
		un grupo de recursos "general". Posteriormente podr�an inicializarse nuevos 
		grupos de recursos para otros prop�sitos, como por ejemplo uno por nivel.
		Adem�s se encarga de inicializar el sistema de render y crear una
		ventana de renderizado. Antes de llamar a este m�todo debe haberse 
		seleccionado un sistema de render mediante Root::setRenderSystem o mediante
		el m�todo configureOgre().

		@return true si todo fue bien.
		*/
		bool initOgreResources();

		/** 
		Pone las dimensiones m�ximas de la pantalla en las propiedades del rat�n
		OIS. Si se redimendiona la ventana de reenderizado deberemos llamar a este 
		m�todo.

		@param width Anchura de la ventana en pixels.
		@param height Altura de la ventana en pixels.
		*/
		void setWindowExtents(unsigned int width, unsigned int height);

		/**
		Instancia �nica de la aplicaci�n.
		*/
		static CServer *_instance;
		
		/**
		Punto de entrada al sistema Ogre.
		*/
		Ogre::Root *_root;

		/** 
		Ventana de renderizado 
		*/
		Ogre::RenderWindow *_renderWindow;

		/**
		Clase que escucha los eventos de ventana. Capturamos el evento de
		cierre para forzar que la aplicaci�n se cierre.
		*/
		WindowEventListener* _windowEventListener;

		/**
		Sistema de gesti�n de perif�ricos de entrada de OIS.
		*/
		OIS::InputManager *_inputSystem;

		/** 
		Buffer de la entrada del rat�n OIS.
		*/
		OIS::Mouse *_mouse;

		/** 
		Buffer de la entrada del teclado OIS.
		*/
		OIS::Keyboard *_keyboard;

		/**
		Sistema de la interfaz gr�fica de usuario CEGUI.
		*/
		CEGUI::System *_GUISystem;

		CEGUI::XMLParser *_parser;

	}; // class CServer

} // namespace BaseSubsystems

#endif // __BaseSubsystems_Server_H
