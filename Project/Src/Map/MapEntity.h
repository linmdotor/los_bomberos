/**
@file Entity.h

Contiene la declaraci�n de la clase que representa una entidad leida 
del fichero del mapa.

@see Map::CEntity

@author David Llans� Garc�a
@date Agosto, 2010
*/

#ifndef __Map_Entity_H
#define __Map_Entity_H

#include "BaseSubsystems/Math.h"
#include <string>
#include <map>

namespace Map 
{
	/**
	Clase que representa una entidad leida del fichero del mapa. Es
	simplemente una colecci�n de pares <atributo,valor> m�s un string
	con el tipo de la entidad. 
	<p>
	La clase contiene m�todos accesores que devuelven un atributo 
	convertido al tipo de datos requerido. El demandante es responsable 
	de solicitar el atributo por el m�todo accesor adecuado, si el
	atributo no existe o no se puede convertir en el tipo de datos deseado
	salta una excepci�n. Acepta extraer strings, enteros, flotantes, 
	flotantes de doble precisi�n, booleanos o posiciones (�stas deben
	seguir el formato "(x,y,z)").

	@ingroup mapParserGroup
	@ingroup mapGroup

	@author David Llans�
	@date Agosto, 2010
	*/
	class CEntity 
	{
	public:

		/** 
		Constructor de la clase.
		*/
		CEntity(const std::string &name) : _type(""), _name(name) {}

		/**
		Destructor.
		*/
		~CEntity() {}

		/**
		A�ade un atributo a la lista de atributos de la entidad.

		@param attr Nombre del atributo a a�adir.
		@param value Valor del atributo.
		*/
		void setAttribute(const std::string &attr, const std::string &value);

		/**
		Dice si se ha a�adido un atributo.

		@param attr Nombre del atributo.
		@return true si contiene el atributo.
		*/
		bool hasAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente a�adido. Si no existe devuelve "".

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		const std::string &getStringAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente a�adido de tipo entero. Si no existe 
		salta una excepci�n.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		int getIntAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente a�adido de tipo flotante. Si no existe 
		salta una excepci�n.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		float getFloatAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente a�adido de tipo double. Si no existe 
		salta una excepci�n.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		double getDoubleAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente a�adido de tipo booleano. Si no existe 
		salta una excepci�n.

		@param attr Nombre del atributo a recuperar.
		@return Valor del atributo.
		*/
		bool getBoolAttribute(const std::string &attr) const;

		/**
		Recupera un atributo previamente a�adido de tipo posici�n. Si no existe 
		salta una excepci�n. Las posiciones deben tener el formato "(x,y,z)".

		@param attr Nombre del atributo a recuperar.
		@param x Valor del eje X.
		@param y Valor del eje Y.
		@param z Valor del eje Z.
		*/
		const Vector3 getVector3Attribute(const std::string &attr) const;

		/**
		Devuelve un string con el tipo de la entidad.

		@return Tipo de la entidad.
		*/
		const std::string &getType() const {return _type;}

		/**
		Establece el tipo de la entidad.

		@param type Tipo de la entidad.
		*/
		void setType(const std::string &type) {_type = type;}

		/**
		Devuelve un string con el nombre de la entidad.

		@return Nombre de la entidad.
		*/
		const std::string &getName() const {return _name;}

		/**
		Establece el nombre de la entidad.

		@param name Nombre de la entidad.
		*/
		void setName(const std::string &name) {_name = name;}

	protected:

		/**
		Tipo lista de CEntity donde guardaremos los pendientes de borrar.
		*/
		typedef std::map<std::string, std::string> TAttrList;

		/**
		Atributos de la entidad.
		*/
		TAttrList _attributes;

		/**
		Tipo de la entidad.
		*/
		std::string _type;

		/**
		Nombre de la entidad.
		*/
		std::string _name;

	}; // CEntity

} // namespace Map

#endif // __Map_Entity_H
