/**
@file EntityFactory.h

Contiene la declaraci�n de la clase factor�a de entidades
del juego.

@see Logic::CEntityFactory

@author David Llans� Garc�a, Marco Antonio G�mez Mart�n
@date Agosto, 2010
*/

#ifndef __Logic_EntityFactory_H
#define __Logic_EntityFactory_H

#include <map>
#include <string>
#include <list>

#include "EntityID.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Map
{
	class CEntity;
}

namespace Logic 
{
	class CMap;
	class CEntity;
	class CBluePrint;
}

// Definici�n de la clase
namespace Logic 
{
	/**
	Factor�a de CEntity que centraliza tanto la construcci�n
	como la destrucci�n de entidades del juego. Es un singleton
	de inicializaci�n expl�cita. Hace uso de la factor�a de 
	componentes para ensamblar las entidades a partir de las descripciones
	de las entidades (blueprints).

	La factor�a carga la descripci�n de las entidades (componentes
	que las forman) del fichero blueprints.

	@ingroup logicGroup
	@ingroup mapGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CEntityFactory 
	{
	public:

		/**
		Inicializa la base de datos de la factor�a.

		@return false si no se ha podido inicializar.
		*/
		static bool Init();

		/**
		Libera la base de datos. Debe llamarse al finalizar la aplicaci�n.
		*/
		static void Release();

		/**
		Devuelve un puntero al �nico objeto de la clase.

		@return Factor�a de entidades.
		*/
		static CEntityFactory *getSingletonPtr() {return _instance;}

		/**
		Carga un nuevo listado de entidades que se pueden crear mediante 
		componentes. El fichero que contiene la definici�n es muy simple.
		Cada l�nea corresponde a una entidad que viene definida por una
		serie de palabras separadas por espacios donde la primera
		palabra es el tipo de la entidad y el resto son los componentes 
		que conforman dicha entidad.
		<p>
		Se puede cargar m�s de un fichero con definiciones de entidades.
		Si los tipo de entidad se encuentran repetidos siempre prevalece
		el �ltimo a�adido.

		@param filename Fichero con la descripci�n de las entidades.
		@return true si la carga se hizo correctamente.
		*/
		bool loadBluePrints(const std::string &filename);

		/**
		Descarga el listado de entidades creadas
		*/
		void unloadBluePrints();

		/**
		Crea una nueva entidad de juego en un mapa determinado a partir de
		su descripci�n en base a los componentes que necesita debido
		a su naturaleza seg�n lo le�do en el/los archivo/s blueprint.

		El m�todo se encarga de asignar un nuevo identificador �nico a la
		entidad y a�adirlo en el mapa del par�metro.

		@param entityInfo Descripci�n de la entidad; puede ser le�da
		de un fichero de mapa o montada "al vuelo".
		@param map Mapa donde se crea la entidad.
		@return Entidad creada o NULL si no se pudo crear.

		@note Las entidades aqu� creadas pueden eliminarse al final del 
		juego o bien utilizando deferredDeleteEntity.
		*/
		CEntity *createEntity(const Map::CEntity *entityInfo,
							  CMap *map);

		/**
		Destruye el CEntity pasado como par�metro. La destrucci�n
		es inmediata, por lo que el <em>invocante debe garantizar</em>
		que ese objeto no est� actualmente en uso (no se est� destruyendo
		a si mismo) o no afecta a otras entidades en acciones que est�n 
		aun por realizar en el tick() actual de la l�gica (si es que se
		est� en medio de uno). De no ser as�, el resultado ser� 
		indeterminado.

		@remarks Si no se est� seguro es recomendable usar el m�todo
		deferredDeleteEntity() que eliminar� la entidad cuando se 
		termine el tick() de todo el mapa.

		@param entidad Entidad de juego que se borrar�.
		*/
		void deleteEntity(CEntity *entity);

		/**
		Solicita la destrucci�n retrasada de la entidad que se pasa como 
		par�metro.
		<p>
		Este m�todo se utiliza cuando se est� a�n con el juego activo y
		el objeto no puede eliminarse en este momento bien porque se 
		intenta autodestruir en medio de su propio tick() o porque
		acciones que aun estar por procesar en otras entidades puedan
		requerir de la presencia de esta entidad.
		<p>
		La factor�a retrasa la destrucci�n del objeto hasta que el
		bucle de juego invoca a deleteDefferedObjects(). Ser�
		la propia factor�a la que se preocupe en ese momento de:
		<ul>
			<li>Desactivar el objeto si pertenece a un mapa activo.</li>
			<li>Eliminarlo del mapa al que pertenece.</li>
			<li>Borrarlo definitivamente.</li>
		</ul>

		@param entity Entidad del juego que se quiere borrar.
		@note Si se elimina la factor�a (se llama al destructor) _antes_
		de la invocaci�n a deleteDefferedObjects() esos objetos
		_no_ son borrados por esta factor�a como elementos diferidos,
		sino que se conf�a en que el mapa que a�n contiene el objeto
		eliminar� esa entidad.
		*/
		void deferredDeleteEntity(CEntity *entity);

		/**
		M�todo invocado por el bucle del juego para que la factor�a
		elimine todos los objetos pendientes de ser borrados.
		*/
		void deleteDefferedEntities();

		/**
		Estructura que define una entidad blueprint.
		*/
		typedef struct
		{
			/**
			Nombre del tipo de entidad
			*/
			std::string type;

			/**
			Lista de nombres de componentes que componen la entidad.
			*/
			std::list<std::string> components;

		}TBluePrint;

	protected:

		/**
		�nica instancia de la clase.
		*/
		static CEntityFactory *_instance;

		/** 
		Constructor de la clase, protegido, pues es un singleton.
		Registra al objeto como observer del cargador de mapas.
		*/
		CEntityFactory();

		/**
		Destructor protegido, por ser singleton.
		*/
		~CEntityFactory();

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
		Ensambla una nueva entidad de juego a partir de su tipo de entidad.
		En base al tipo de entidad se crear�n y a�adir�n a la entidad las 
		instancias de los componentes que necesita seg�n lo le�do en el/los 
		archivo/s blueprint.
		Es un procedimiento auxiliar utilizado por createEntity.

		@param type Tipo de la entidad que se quiere crear.
		@return La entidad creada o NULL si no se pudo crear.
		*/
		CEntity *assembleEntity(const std::string &type);

		/**
		Tipo lista de CEntity donde guardaremos los pendientes de borrar.
		*/
		typedef std::list<Logic::CEntity*> TEntityList;

		/**
		Lista de objetos pendientes de borrar.
		*/
		TEntityList _pendingEntities;

		/**
		Tipo tabla para almacenar entidades blueprint por nombre.
		*/
		typedef std::map<std::string,TBluePrint> TBluePrintMap;

		/**
		Tabla donde se almacenan las entidades blueprint por nombre.
		*/
		TBluePrintMap _bluePrints;

	}; // CEntityFactory

} // namespace Logic

#endif // __Logic_EntityFactory_H
