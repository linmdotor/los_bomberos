/**
@file CommunicationPort.h

Contiene la declaraci�n de la clase que se encarga del intercambio 
de los mensajes.

@see Logic::CCommunicationPort

@author David Llans� Garc�a
@date Julio, 2010
*/

#ifndef __Logic_CommunicationPort_H
#define __Logic_CommunicationPort_H

#include <list>

#include "Message.h"

// Declaraci�n de la clase
namespace Logic 
{

/**
	La clase CCommunicationPort se encarga de toda la gestion de 
	los mensajes que pueden ser enviados. la interfaz de componente
	heredar� de esta clase para delegar en ella toda la comunicaci�n
	entre componentes. 
	<p>
	En cualquier momento se puede enviar un mensaje mediante el 
	m�todo set() que ver� si el mensaje es aceptado y en ese caso
	lo meter� en una cola para que sea procesado posteriormente. Los 
	mensajes por tanto no se procesan autom�ticamente sino que se 
	guardan y posteriormente, generalmente una vez por frame, se
	procesan todos los mensajes recibidos invocando al m�todo
	processMessages().
	<p>
	Para que esto funcione correctamente, las clases hijas deber�n
	implementar los m�todos virtuales accept() y process().
	El m�todo accept() decidir� si el mensaje recibido es aceptado 
	o rechazado, mientras que el m�todo process() se encargar� de 
	procesar un mensaje concreto.

    @ingroup logicGroup
    @ingroup entityGroup

	@author David Llans�
	@date Julio, 2010
*/
	class CCommunicationPort 
	{
	public:

		/**
		Constructor por defecto; en la clase base no hace nada.
		*/
		CCommunicationPort() {}

		/**
		Destructor. Vac�a el vector de mensajes.
		*/
		virtual ~CCommunicationPort();

		/**
		M�todo que a�ade un mensaje a la cola si �ste es aceptado.

		@param message Mensaje a procesar.
		@return true si el mensaje ha sido admitido y puesto en cola.
		*/
		bool set(const TMessage &message);

		/**
		M�todo virtual que elige que mensajes son aceptados. Las clases
		que hereden del puerto de comunicaci�n deber�n reimplementar
		este m�todo si quieren aceptar alg�n mensaje ya que por defecto
		se rechazan todos.

		@param message Mensaje a chequear.
		@return true si el mensaje es aceptado.
		*/
		virtual bool accept(const TMessage &message) {return false;}

		/**
		M�todo virtual que procesa un mensaje.

		@param message Mensaje a procesar.
		*/
		virtual void process(const TMessage &message) {}

		/**
		M�todo que procesa la lista de mensajes que faltan por procesar.
		Simplemente invoca a process() con cada uno de los mensajes.
		*/
		void processMessages();

	protected:
		/**
		Tipo lista de CEntity donde guardaremos los pendientes de borrar.
		*/
		typedef std::list<TMessage> TMessageList;

		/**
		Lista de mensajes por procesar
		*/
		TMessageList _messages;

	}; // CCommunicationPort

} // namespace Logic

#endif // __Logic_CommunicationPort_H
