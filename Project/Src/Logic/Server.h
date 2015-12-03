/**
@file Server.h

Contiene la declaraci�n de la clase CServer, Singleton que se encarga de
la gesti�n de la l�gica del juego.

@see Logic::CServer

@author David Llans�
@date Agosto, 2010
*/
#ifndef __Logic_Server_H
#define __Logic_Server_H

#include <string>

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Logic 
{
	class CMap;
	class CEntity;
}

/**
Namespace que engloba la l�gica del juego. Engloba desde el mapa l�gico
contenedor de todas las entidades del juego hasta las propias entidades,
sus componentes, mensajes, factorias de entidades y componentes, etc.
(para m�s informaci�n ver @ref LogicGroup).

@author David Llans�
@date Agosto, 2010
*/
namespace Logic
{
	/**
	Servidor de la l�gica que se se encarga de la creaci�n del mundo, su 
	destrucci�n y actualizaci�n a lo largo de la partida. Se encarga de 
	inicializar el parseador de mapas y la factor�a de entidades para cargar
	y gestionar el mapa de la partida. 

	@ingroup logicGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CServer
	{
	public:

		/**
		Devuelve la �nica instancia de la clase CServer.
		
		@return �nica instancia de la clase CServer.
		*/
		static CServer* getSingletonPtr() {return _instance;}

		/**
		Inicializa la instancia

		@return Devuelve false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera la instancia de CServer. Debe llamarse al finalizar la 
		aplicaci�n.
		*/
		static void Release();

		/**
		Funci�n llamada en cada frame para que se realicen las funciones
		de actualizaci�n adecuadas.
		<p>
		Llamar� al m�todo tick() del mapa.

		@param msecs Milisegundos transcurridos desde el �ltimo tick.
		*/
		void tick(unsigned int msecs);

		/**
		Funci�n que activa el mapa en curso.

		@return true si la inicializaci�n fue correcta.
		*/
		bool activateMap();

		/**
		Funci�n que desactiva el mapa en curso.
		*/
		void deactivateMap();

		/**
		Devuelve el mapa l�gico del juego.

		@return Mapa con las entidades de juego.
		*/
		CMap *getMap() {return _map;}

		/**
		Devuelve la entidad del jugador.

		@return Entidad del jugador.
		*/
		CEntity *getPlayer() {return _player;}

		/**
		Establece la entidad del jugador.

		@param player Entidad del jugador.
		*/
		void setPlayer(CEntity *player) {_player = player;}

		/**
		Carga un nuevo nivel a partir del nombre del mapa que se
		desea cargar. Si ya exist�a un mapa este se borra, solo
		permitimos un nivel activo.

		@param filename Fichero que se desea cargar.
		@return true si la carga fue correcta.
		*/
		bool loadLevel(const std::string &filename);

		/**
		Si hay un nivel cargado lo descarga  destruye.
		*/
		void unLoadLevel();

	protected:
		/**
		Constructor.
		*/
		CServer ();

		/**
		Destructor.
		*/
		~CServer();

		/**
		Segunda fase de la construcci�n del objeto. Sirve para hacer
		inicializaciones de la propia instancia en vez de inicializaciones 
		est�ticas.

		@return true si todo fue correctamente.
		*/
		bool open();

		/**
		Segunda fase de la destrucci�n del objeto. Sirve para hacer liberar 
		los recursos de la propia instancia, la liberaci�n de los recursos 
		est�ticos se hace en Release().
		*/
		void close();

		/**
		Mapa donde se encuentran todas las entidades l�gicas.
		*/
		CMap *_map;

		/**
		Entidad del jugador.
		*/
		CEntity *_player;

	private:
		/**
		�nica instancia de la clase.
		*/
		static CServer* _instance;

	}; // class CServer

} // namespace Logic

#endif // __Logic_Server_H
