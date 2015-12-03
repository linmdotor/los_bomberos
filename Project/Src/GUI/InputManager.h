//---------------------------------------------------------------------------
// InputManager.h
//---------------------------------------------------------------------------

/**
@file InputManager.h

Contiene la declaraci�n del gestor de perif�ricos de entrada
as� como las clases oyentes que deben extender las clases que
quieran ser avisadas de los eventos de dichos perif�ricos:
rat�n y teclado.

@see GUI::CInputManager
@see GUI::CKeyboardListener
@see GUI::CMouseListener

@author David Llans�
@date Julio, 2010
*/

#ifndef __GUI_InputManager_H
#define __GUI_InputManager_H

#include <OISMouse.h>
#include <OISKeyboard.h>

#include <list>

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace OIS
{
	class InputManager;
}

/**
Namespace con todo lo que se refiere a la interfaz con el usuario.
Recoge y procesa los eventos del rat�n y teclado e informa al 
usuario cuando es necesario.
(para m�s informaci�n ver @ref GUIGroup).

@author David Llans�
@date Julio, 2010
*/
namespace GUI
{
	/**
	Namespace que contiene el tipo que define los diferentes c�digos de 
	los botones del	rat�n. De esta manera independizamos el resto de la 
	aplicaci�n de la biblioteca OIS.
	*/
	namespace Button
	{
		/**
		Tipo para los c�digos de los botones del rat�n. Declararlos aqu� 
		tiene como funci�n independizar el resto de la aplicaci�n de la 
		biblioteca OIS.
		*/
		enum TButton
		{
			UNASSIGNED = 0xFFFFFFFF,
			LEFT       = OIS::MB_Left,
			RIGHT      = OIS::MB_Right,
			MIDDLE     = OIS::MB_Middle,
			BUTTON_3   = OIS::MB_Button3,
			BUTTON_4   = OIS::MB_Button4,
			BUTTON_5   = OIS::MB_Button5,
			BUTTON_6   = OIS::MB_Button6,
			BUTTON_7   = OIS::MB_Button7

		}; // enum TButton

	} // namespace Button

	/**
	Tipo copia para los c�digos de los botones del rat�n. Por simplicidad.
	*/
	typedef Button::TButton TButton;

	/**
	Namespace que contiene el tipo que define los diferentes c�digos de 
	las teclas. Declararlos aqu� tiene como funci�n independizar el resto 
	de la aplicaci�n de la biblioteca OIS.
	*/
	namespace Key
	{
		/**
		Tipo para los c�digos de las teclas. Declararlos aqu� tiene como 
		funci�n independizar el resto de la aplicaci�n de la biblioteca 
		OIS.
		*/
		enum TKeyID
		{
			UNASSIGNED    = OIS::KC_UNASSIGNED,
			ESCAPE        = OIS::KC_ESCAPE,
			NUMBER1       = OIS::KC_1,
			NUMBER2       = OIS::KC_2,
			NUMBER3       = OIS::KC_3,
			NUMBER4       = OIS::KC_4,
			NUMBER5       = OIS::KC_5,
			NUMBER6       = OIS::KC_6,
			NUMBER7       = OIS::KC_7,
			NUMBER8       = OIS::KC_8,
			NUMBER9       = OIS::KC_9,
			NUMBER0       = OIS::KC_0,
			MINUS         = OIS::KC_MINUS,    // - on main keyboard
			EQUALS        = OIS::KC_EQUALS,
			BACK          = OIS::KC_BACK,    // backspace
			TAB           = OIS::KC_TAB,
			Q             = OIS::KC_Q,
			W             = OIS::KC_W,
			E             = OIS::KC_E,
			R             = OIS::KC_R,
			T             = OIS::KC_T,
			Y             = OIS::KC_Y,
			U             = OIS::KC_U,
			I             = OIS::KC_I,
			O             = OIS::KC_O,
			P             = OIS::KC_P,
			LBRACKET      = OIS::KC_LBRACKET,
			RBRACKET      = OIS::KC_RBRACKET,
			RETURN        = OIS::KC_RETURN,    // Enter on main keyboard
			LCONTROL      = OIS::KC_LCONTROL,
			A             = OIS::KC_A,
			S             = OIS::KC_S,
			D             = OIS::KC_D,
			F             = OIS::KC_F,
			G             = OIS::KC_G,
			H             = OIS::KC_H,
			J             = OIS::KC_J,
			K             = OIS::KC_K,
			L             = OIS::KC_L,
			NGRAVE        = OIS::KC_SEMICOLON,    // �
			APOSTROPHE    = OIS::KC_APOSTROPHE,
			GRAVE         = OIS::KC_GRAVE,    // accent
			LSHIFT        = OIS::KC_LSHIFT,
			BACKSLASH     = OIS::KC_BACKSLASH,
			Z             = OIS::KC_Z,
			X             = OIS::KC_X,
			C             = OIS::KC_C,
			V             = OIS::KC_V,
			B             = OIS::KC_B,
			N             = OIS::KC_N,
			M             = OIS::KC_M,
			COMMA         = OIS::KC_COMMA,
			PERIOD        = OIS::KC_PERIOD,    // . on main keyboard
			SLASH         = OIS::KC_SLASH,    // / on main keyboard
			RSHIFT        = OIS::KC_RSHIFT,
			MULTIPLY      = OIS::KC_MULTIPLY,    // * on numeric keypad
			LALT          = OIS::KC_LMENU,    // left Alt
			SPACE         = OIS::KC_SPACE,
			CAPITAL       = OIS::KC_CAPITAL,
			F1            = OIS::KC_F1,
			F2            = OIS::KC_F2,
			F3            = OIS::KC_F3,
			F4            = OIS::KC_F4,
			F5            = OIS::KC_F5,
			F6            = OIS::KC_F6,
			F7            = OIS::KC_F7,
			F8            = OIS::KC_F8,
			F9            = OIS::KC_F9,
			F10           = OIS::KC_F10,
			NUMLOCK       = OIS::KC_NUMLOCK,
			SCROLL        = OIS::KC_SCROLL,    // Scroll Lock
			NUMPAD7       = OIS::KC_NUMPAD7,
			NUMPAD8       = OIS::KC_NUMPAD8,
			NUMPAD9       = OIS::KC_NUMPAD9,
			SUBTRACT      = OIS::KC_SUBTRACT,    // - on numeric keypad
			NUMPAD4       = OIS::KC_NUMPAD4,
			NUMPAD5       = OIS::KC_NUMPAD5,
			NUMPAD6       = OIS::KC_NUMPAD6,
			ADD           = OIS::KC_ADD,    // + on numeric keypad
			NUMPAD1       = OIS::KC_NUMPAD1,
			NUMPAD2       = OIS::KC_NUMPAD2,
			NUMPAD3       = OIS::KC_NUMPAD3,
			NUMPAD0       = OIS::KC_NUMPAD0,
			DECIMAL       = OIS::KC_DECIMAL,    // . on numeric keypad
			OEM_102       = OIS::KC_OEM_102,    // < > | on UK/Germany keyboards
			F11           = OIS::KC_F11,
			F12           = OIS::KC_F12,
			NUMPADEQUALS  = OIS::KC_NUMPADEQUALS,    // = on numeric keypad (NEC PC98)
			PREVTRACK     = OIS::KC_PREVTRACK,    // Previous Track (OIS::KC_CIRCUMFLEX on Japanese keyboard)
			AT            = OIS::KC_AT,    //                     (NEC PC98)
			COLON         = OIS::KC_COLON,    //                     (NEC PC98)
			UNDERLINE     = OIS::KC_UNDERLINE,    //                     (NEC PC98)
			STOP          = OIS::KC_STOP,    //                     (NEC PC98)
			NEXTTRACK     = OIS::KC_NEXTTRACK,    // Next Track
			NUMPADENTER   = OIS::KC_NUMPADENTER,    // Enter on numeric keypad
			RCONTROL      = OIS::KC_RCONTROL,
			MUTE          = OIS::KC_MUTE,    // Mute
			CALCULATOR    = OIS::KC_CALCULATOR,    // Calculator
			PLAYPAUSE     = OIS::KC_PLAYPAUSE,    // Play / Pause
			MEDIASTOP     = OIS::KC_MEDIASTOP,    // Media Stop
			VOLUMEDOWN    = OIS::KC_VOLUMEDOWN,    // Volume -
			VOLUMEUP      = OIS::KC_VOLUMEUP,    // Volume +
			WEBHOME       = OIS::KC_WEBHOME,    // Web home
			NUMPADCOMMA   = OIS::KC_NUMPADCOMMA,    // , on numeric keypad (NEC PC98)
			DIVIDE        = OIS::KC_DIVIDE,    // / on numeric keypad
			SYSRQ         = OIS::KC_SYSRQ,
			RALT          = OIS::KC_RMENU,    // right Alt
			PAUSE         = OIS::KC_PAUSE,    // Pause
			HOME          = OIS::KC_HOME,    // Home on arrow keypad
			UPARROW       = OIS::KC_UP,    // UpArrow on arrow keypad
			PGUP          = OIS::KC_PGUP,    // PgUp on arrow keypad
			LEFTARROW     = OIS::KC_LEFT,    // LeftArrow on arrow keypad
			RIGHTARROW    = OIS::KC_RIGHT,    // RightArrow on arrow keypad
			END           = OIS::KC_END,    // End on arrow keypad
			DOWNARROW     = OIS::KC_DOWN,    // DownArrow on arrow keypad
			PGDOWN        = OIS::KC_PGDOWN,    // PgDn on arrow keypad
			INSERT        = OIS::KC_INSERT,    // Insert on arrow keypad
			DEL           = OIS::KC_DELETE,    // Delete on arrow keypad
			LWIN          = OIS::KC_LWIN,    // Left Windows key
			RWIN          = OIS::KC_RWIN,    // Right Windows key
			APPS          = OIS::KC_APPS,    // AppMenu key
			POWER         = OIS::KC_POWER,    // System Power
			SLEEP         = OIS::KC_SLEEP,    // System Sleep
			WAKE          = OIS::KC_WAKE,    // System Wake
			WEBSEARCH     = OIS::KC_WEBSEARCH,    // Web Search
			WEBFAVORITES  = OIS::KC_WEBFAVORITES,    // Web Favorites
			WEBREFRESH    = OIS::KC_WEBREFRESH,    // Web Refresh
			WEBSTOP       = OIS::KC_WEBSTOP,    // Web Stop
			WEBFORWARD    = OIS::KC_WEBFORWARD,    // Web Forward
			WEBBACK       = OIS::KC_WEBBACK,    // Web Back
			MYCOMPUTER    = OIS::KC_MYCOMPUTER,    // My Computer
			MAIL          = OIS::KC_MAIL,    // Mail
			MEDIASELECT   = OIS::KC_MEDIASELECT     // Media Select

		}; // enum TKeyID

	} // namespace Key

	/**
	Tipo copia para los c�digos de las teclas del teclado. Por 
	simplicidad.
	*/
	typedef struct TKey
	{
		TKey(const unsigned int text, const Key::TKeyID keyId)
						{this->text = text; this->keyId = keyId;}
		unsigned int text;
		Key::TKeyID keyId;
	}TKey;

	/**
	Namespace que contiene el tipo que define los diferentes c�digos de 
	las teclas "modificadoras" Shift, Ctrl y Alt. Declararlos aqu� tiene 
	como funci�n independizar el resto de la aplicaci�n de la biblioteca 
	OIS.
	*/
	namespace Modifier
	{
		/**
		Tipo para los c�digos de las teclas "modificadoras" Shift, Ctrl y 
		Alt. Declararlos aqu� tiene como funci�n independizar el resto de 
		la aplicaci�n de la biblioteca OIS.
		*/
		enum TModifier
		{
			SHIFT  = OIS::Keyboard::Shift,
			CTRL   = OIS::Keyboard::Ctrl,
			ALT    = OIS::Keyboard::Alt

		}; // enum TModifier

	} // namespace Modifier

	/**
	Tipo copia para los c�digos de las teclas "modificadoras" Shift, Ctrl 
	y Alt. Por simplicidad.
	*/
	typedef Modifier::TModifier TModifier;
		
	/**
	Esta clase debe ser implementada por las clases que quieren
	registrarse en el gestor de perif�ricos de entrada para ser
	avisados de eventos del teclado.
	Las funciones retornan cierto si el evento ha sido procesado.
	En este caso el gestor no llamar� a otros listeners. Por 
	defecto los m�todos devuelven false.
	
	@ingroup GUIGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CKeyboardListener 
	{
	public:

		/**
		M�todo que ser� invocado siempre que se pulse una tecla.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners. Por defecto los 
		m�todos devuelven false.
		*/
		virtual bool keyPressed(TKey key) {return false;}
		
		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de una tecla.

		@param key C�digo de la tecla pulsada.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners. Por defecto los 
		m�todos devuelven false.
		*/
		virtual bool keyReleased(TKey key) {return false;}

	}; // CKeyboardListener
	
	/**
	clase que representa el estado del rat�n. Sirve para aunar 
	varios atributos simples que definen el estado. Los atributos
	son p�blicos para que sean m�s f�ciles de acceder.
	
	@ingroup GUIGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CMouseState
	{
	public:

		/**
		Constructor. Por defecto se le dan unos valores a los 
		atributos, pero estos deben de ser cambiados en funci�n
		de las propiedades de la ventana, posici�n del rat�n,
		bot�n pulsado, etc.
		*/
		CMouseState()
		{
			width = 800;
			height = 600;
			posAbsX = 0;
			posAbsY = 0;
			posRelX = 0;
			posRelY = 0;
			movX = 0;
			movY = 0;
			scrool = 0;
			button =  Button::UNASSIGNED;
		}

		/**
		Constructor parametrizado.
		
		@param width Anchura de la ventana en pixels.
		@param height Altura de la ventana en pixels.
		@param posAbsX Posici�n absoluta del eje X del puntero del rat�n.
		Va desde 0 hasta el ancho de la ventana.
		@param posAbsY Posici�n absoluta del eje Y del puntero del rat�n.
		Va desde 0 hasta el alto de la ventana.
		*/
		CMouseState(unsigned int width, unsigned int height, 
					unsigned int posAbsX = 0, unsigned int posAbsY = 0)
		{
			setExtents(width,height);
			setPosition(posAbsX,posAbsY);
			movX = 0;
			movY = 0;
			scrool = 0;
			button = (TButton)-1; // Button::UNASSIGNED
		}

		/**
		Establece la anchura y altura del �rea de 
		trabajo del rat�n.

		@param width Anchura de la ventana en pixels.
		@param height Altura de la ventana en pixels.
		*/
		void setExtents(unsigned int width, unsigned int height)
		{
			this->width = width;
			this->height = height;
		}

		/**
		Establece las posiciones de los ejes X e Y del puntero del 
		rat�n.
		
		@param posAbsX Posici�n absoluta del eje X del puntero del rat�n.
		Va desde 0 hasta el ancho de la ventana.
		@param posAbsY Posici�n absoluta del eje Y del puntero del rat�n.
		Va desde 0 hasta el alto de la ventana.
		*/
		void setPosition(unsigned int posAbsX, unsigned int posAbsY)
		{
			this->posAbsX = posAbsX;
			this->posAbsY = posAbsY;
			this->posRelX = (float)posAbsX / (float)width;
			this->posRelY = (float)posAbsY / (float)height;
		}

		/** 
		Estos valores representan la anchura y altura del �rea de 
		trabajo del rat�n. Suele estar asociado al tama�o de la 
		ventana de renderizado. Su valor es mutable para que se
		pueda cambiar aunque se pase como const.
		*/
		unsigned int width, height;

		/**
		Posiciones absolutas de los ejes X e Y del puntero del 
		rat�n. Los valores van desde 0 hasta el ancho y alto de 
		la ventana.
		*/
		unsigned int posAbsX, posAbsY;

		/**
		Posiciones relativas de los ejes X e Y del puntero del 
		rat�n. Los valores van desde 0 hasta 1 independientemente
		del ancho y alto de la ventana.
		*/
		float posRelX, posRelY;

		/**
		Movimiento de los ejes X e Y del puntero del rat�n respecto 
		del �ltimo evento. Valores positivos movimiento a derechas,
		negativos a izquierdas.
		*/
		int movX, movY;
		
		/**
		Movimiento de la rueda del rat�n respecto del �ltimo evento.
		*/
		int scrool;

		/**
		Indica que bot�n ha sido el �ltimo en producir un evento.
		Si no ha habido eventos de rat�n su valor es 
		Button::UNASSIGNED.
		*/
		TButton button;
	};
	
	/**
	Esta clase debe ser implementada por las clases que quieren
	registrarse en el gestor de perif�ricos de entrada para ser
	avisados de eventos del rat�n.
	Las funciones retornan cierto si el evento ha sido procesado.
	En este caso el gestor no llamar� a otros listeners. Por 
	defecto los m�todos devuelven false.
	
	@ingroup GUIGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CMouseListener 
	{
	public:
		
		/**
		M�todo que ser� invocado siempre que se mueva el rat�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners. Por defecto los 
		m�todos devuelven false.
		*/
		virtual bool mouseMoved(const CMouseState &mouseState)
														{return false;}
		
		/**
		M�todo que ser� invocado siempre que se pulse un bot�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners. Por defecto los 
		m�todos devuelven false.
		*/
		virtual bool mousePressed(const CMouseState &mouseState)
														{return false;}

		/**
		M�todo que ser� invocado siempre que se termine la pulsaci�n
		de un bot�n.

		@param mouseState Estado del rat�n cuando se lanza el evento.
		@return true si el evento ha sido procesado. En este caso 
		el gestor no llamar� a otros listeners. Por defecto los 
		m�todos devuelven false.
		*/
		virtual bool mouseReleased(const CMouseState &mouseState)
														{return false;}

	}; // CMouseListener

	/**
	Gestor de perif�ricos de entrada. Controla y captura los eventos
	que se producen en teclado y rat�n. Permite registrar oyentes que
	ser�n informados de dichos eventos. Cuando se registra un evento
	se emite este a los diferentes oyentes hasta que uno de los
	oyentes capture dicho evento. Los nuevos oyentes tienen prioridad
	a la hora de ser avisados de los eventos. Esto viene bien por si
	en condiciones especiales se quiere a�adir un oyente que cambia
	las acciones de ciertas teclas sin necesidad de eliminar oyentes.
	<p>
	Para la gesti�n de los eventos se usa OIS. Sin embargo esta clase
	redefine las clases oyentes de teclado y rat�n, as� como los 
	c�digos de las teclas del teclado y los botones y el estado del 
	rat�n para que el resto de las clases de la aplicaci�n sean 
	independientes del sistema usado para la captura de eventos (OIS).
	<p>
	La inicializaci�n del subsistema OIS NO se hace en esta clase
	sino que lo hace BaseSubsystems::CServer. De la misma manera esta
	clase no es responsable de su destrucci�n.
	<p>
	Por simplicidad no se han a�adido otros perif�ricos de entrada 
	como joysticks, aunque OIS los permite.
	
	@ingroup GUIGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CInputManager : public OIS::KeyListener, 
		public OIS::MouseListener 
	{
	public:

		/**
		Devuelve la �nica instancia de la clase.

		@return Puntero al gestor de perif�ricos de entrada.
		*/
		static GUI::CInputManager *getSingletonPtr() { return _instance; }

		/** 
		Inicia el gestor de perif�ricos de entrada basado en OIS.

		@return true si la inicializaci�n se hizo correctamente.
		*/
		static bool Init();

		/** 
		Libera el gestor de perif�ricos de entrada basado en OIS. 
		Debe llamarse al finalizar la aplicaci�n.
		*/
		static void Release();

		/** 
		Comprueba si ha habido eventos en los dispositivos de entrada.
		Debe llamarse en cada vuelta de la aplicaci�n.
		*/
		void tick();

		/** 
		A�ade un oyente del teclado.
		
		@param keyListener Oyente del teclado
		*/
		void addKeyListener(CKeyboardListener *keyListener);

		/** 
		A�ade un oyente del rat�n.
		
		@param keyListener Oyente del rat�n.
		*/
		void addMouseListener(CMouseListener *mouseListener);

		/** 
		Borra un oyente del teclado.
		
		@param keyListener Oyente del teclado
		*/
		void removeKeyListener(CKeyboardListener *keyListener);

		/** 
		Borra un oyente del rat�n.
		
		@param keyListener Oyente del rat�n.
		*/
		void removeMouseListener(CMouseListener *mouseListener);

		/** 
		Borra todos los oyentes.
		*/
		void removeAllListeners();

		/** 
		Borra todos los oyentes del teclado.
		*/
		void removeAllKeyListeners();

		/** 
		Borra todos los oyentes del rat�n.
		*/
		void removeAllMouseListeners();

		/**
		M�todo que consulta si una tecla est� o no pulsada.

		@param key Tecla que se quiere saber si est� o no pulsada.
		@return true si la tecla est� pulsada.
		*/
		bool isKeyPressed(TKey key) 
		{return _keyboard->isKeyDown((OIS::KeyCode)key.keyId);}

		/**
		M�todo que consulta si una tecla "modificadora" est� o no pulsada.

		@param key Tecla que se quiere saber si est� o no pulsada.
		@return true si la tecla est� pulsada.
		*/
		bool isModifierPressed(TModifier modifier) 
			{return _keyboard->isModifierDown((OIS::Keyboard::Modifier)modifier);}

	private:

		/**
		Constructor.
		*/
		CInputManager();

		/**
		Destructor.
		*/
		virtual ~CInputManager();

		/** 
		Segunda parte de la inicializaci�n del gestor de perif�ricos de entrada 
		basado en OIS. Sirve para hacer inicializaciones de la propia instancia 
		en vez de inicializaciones est�ticas.

		@return true si la inicializaci�n se hizo correctamente.
		*/
		bool open();

		/**
		Segunda fase de la destrucci�n del objeto. Sirve para hacer liberar 
		los recursos de la propia instancia, la liberaci�n de los recursos 
		est�ticos se hace en Release().
		*/
		void close();

		/** 
		�nica instancia de la clase. 
		*/
		static CInputManager *_instance;

		/** 
		M�todo invocado por OIS cuando se pulsa una tecla. Es el
		encargado de avisar a todos los oyentes del evento.

		@param e Evento producido.
		@return true si se desea parar de procesar la entrada.
		*/
		bool keyPressed(const OIS::KeyEvent &e);
		
		/** 
		M�todo invocado por OIS cuando se deja de pulsar una tecla. 
		Es el encargado de avisar a todos los oyentes del evento.

		@param e Evento producido.
		@return true si se desea parar de procesar la entrada.
		*/
		bool keyReleased(const OIS::KeyEvent &e);
		
		/**
		M�todo que convierte un evento de teclado OIS a uno propio.

		@param e Evento de teclado de OIS.
		@return Evento de teclado propio.
		*/
		TKey ois2galeon(const OIS::KeyEvent &e);

		/** 
		M�todo invocado por OIS cuando se mueve el rat�n. 
		Es el encargado de avisar a todos los oyentes del evento.

		@param e Evento producido.
		@return true si se desea parar de procesar la entrada.
		*/
		bool mouseMoved(const OIS::MouseEvent &e);
		
		/** 
		M�todo invocado por OIS cuando se pulsa un bot�n del rat�n. 
		Es el encargado de avisar a todos los oyentes del evento.

		@param e Evento producido.
		@param button c�digo del bot�n pulsado.
		@return true si se desea parar de procesar la entrada.
		*/
		bool mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID button);

		/** 
		M�todo invocado por OIS cuando se deja de pulsar un bot�n. 
		Es el encargado de avisar a todos los oyentes del evento.

		@param e Evento producido.
		@param button c�digo del bot�n soltado.
		@return true si se captura el evento.
		*/
		bool mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID button);

		/** 
		Buffer de la entrada del rat�n OIS.
		*/
		OIS::Mouse *_mouse;

		/** 
		Buffer de la entrada del teclado OIS.
		*/
		OIS::Keyboard *_keyboard;
		
		/**
		Estado del rat�n en el �ltimo evento. Se usa para transmitir
		los cambios a las clases oyentes. Sirve para independizar el
		resto de la aplicaci�n de OIS.
		*/
		CMouseState _mouseState;

		/**
		Sistema de gesti�n de perif�ricos de entrada de OIS.
		*/
		OIS::InputManager *_inputSystem;

		/**
		Lista de oyentes de eventos del teclado.
		*/
		std::list<CKeyboardListener*> _keyListeners;

		/**
		Lista de oyentes de eventos del rat�n.
		*/
		std::list<CMouseListener*> _mouseListeners;

	}; // class InputManager

} // namespace GUI

#endif // __GUI_