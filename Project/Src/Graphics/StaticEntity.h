//---------------------------------------------------------------------------
// StaticEntity.h
//---------------------------------------------------------------------------

/**
@file StaticEntity.h

Contiene la declaraci�n de la clase que representa una entidad gr�fica 
est�tica.

@see Graphics::CStaticEntity
@see Graphics::CEntity

@author David Llans�
@date Julio, 2010
*/

#ifndef __Graphics_StaticEntity_H
#define __Graphics_StaticEntity_H

#include "Entity.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Ogre 
{
	class CScene;
}

namespace Graphics 
{
	/**
	Clase que representa una entidad gr�fica est�tica. Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene. A�ade la posibilidad de a�adirse a una
	geometr�a est�tica. 
	<p>
	@remarks Una vez a�adida la entidad a la geometr�a est�tica las modificaciones
	hechas en los atributos de la clase Graphics::CEntity no tendr�n efecto en
	lo que se ver� en la escena, as� que se deben hacer todos los cambios antes
	de invocar a addToStaticGeometry. De hecho las estructuras creadas en Ogre
	antes de invocer a addToStaticGeometry sirven unicamente como referencia para 
	crear la geometr�a est�tica. Tras la creaci�n, se mantienen las estructuras de 
	las entidades din�micas de Ogre por si se requieren para cargar de nuevo en otra
	escena.
	<p>
	Oculta los detalles escabrosos del motor gr�fico.
	
	@ingroup graphicsGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CStaticEntity : public CEntity
	{
	public:

		/**
		Constructor de la clase.

		@param name Nombre de la entidad.
		@param mesh Nombre del modelo que debe cargarse.
		*/
		CStaticEntity(const std::string &name, const std::string &mesh):
					CEntity(name,mesh) {}

		/**
		Destructor de la aplicaci�n.
		*/
		virtual ~CStaticEntity() {}
	
	protected:

		/**
		Clase amiga. Solo la escena puede mandar a la entidad que pase a formar
		parte de la geometr�a est�tica.
		*/
		friend class CScene;

		/**
		Segundo paso de la carga de la entidad gr�fica est�tica. A�ade la 
		entidad a la geometr�a est�tica de la escena. En este paso, al a�adir
		las entidades que contiene el nodo a la geometr�a est�tica, el nodo que 
		contiene la entidad se desacopla de la escena para que la entidad 
		no se pinte dos veces, una por geometr�a est�tica y otra por estar en 
		un nodo de la escena.
		<p>
		@remarks Una vez a�adida la entidad a la geometr�a est�tica las modificaciones
		hechas en los atributos de la clase Graphics::CEntity no tendr�n efecto en
		lo que se ver� en la escena, as� que se deben hacer todos los cambios antes
		de invocar a este m�todo. Se mantiene sin embargo las estructuras de las 
		entidades din�micas de Ogre por si se requieren para cargar de nuevo en otra
		escena.

		@return true si la geometr�a est�tica se pudo crear correctamente.
		*/
		bool addToStaticGeometry();

	}; // class CStaticEntity

} // namespace Graphics

#endif // __Graphics_StaticEntity_H
