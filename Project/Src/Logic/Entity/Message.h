/**
@file Message.h

Contiene el tipo de datos de un mensaje.

@see Logic::TMessage

@author David Llans� Garc�a
*/
#ifndef __Logic_Message_H
#define __Logic_Message_H

#include <string>

#include "BaseSubsystems/Math.h"

namespace Logic
{
	/**
	Namespace para los tipos de mensajes posibles.
	*/
	namespace Message
	{
		enum TMessageType
		{
			UNASSIGNED = 0xFFFFFFFF,
			SET_TRANSFORM,
			SET_ANIMATION,
			STOP_ANIMATION,
			CONTROL
		};
	}

	/**
	Tipo copia para los mensajes. Por simplicidad.
	*/
	typedef Message::TMessageType TMessageType;

	/**
	Contiene el tipo de datos de un mensaje. Tiene una serie de
	atributos gen�ricos que se interpretar�n en funci�n del tipo 
	de mensaje.
	<p>
	@remarks <b>��ESTO NO ES ESCALABLE!!</b> En tu proyecto esto 
	deber�a ser cambiado.
	Lo suyo ser�a tener una clase CMesage base y luego clases que
	especializasen a �sta con los atributos necesarios para el 
	mensaje concreto en vez de tener una serie de atributos
	gen�ricos como es esta estructura que deben de ser interpretados
	externamente en funci�n del tipo de mensaje.
	
    @ingroup logicGroup
    @ingroup entityGroup

	@author David Llans� Garc�a
	@date Julio, 2010
    @ingroup grupoEntidad
	*/
	typedef struct
	{
		/**
		Tipo del mensaje.
		*/
		TMessageType _type;

		/**
		Atributo para almacenar una matriz de transformaci�n.
		*/
		Matrix4 _transform;
		
		/**
		Atributo para almacenar un valor float.
		*/
		float _float;
		
		/**
		Atributo para almacenar un valor booleano.
		*/
		bool _bool;
		
		/**
		Atributo para almacenar un string.
		*/
		std::string _string;

	} TMessage; 

} // namespace Logic

#endif // __Logic_Message_H
