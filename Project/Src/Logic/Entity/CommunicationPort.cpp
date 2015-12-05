/**
@file CommunicationPort.cpp

Contiene la implementaci�n de la clase que se encarga del intercambio 
de los mensajes.

@see Logic::CCommunicationPort

@author David Llans� Garc�a
@date Julio, 2010
*/

#include "CommunicationPort.h"

namespace Logic {

	CCommunicationPort::~CCommunicationPort()
	{
		_messages.clear();

	} // ~CCommunicationPort
	
	//---------------------------------------------------------

	bool CCommunicationPort::set(Logic::ReferenceCounterPtr<Logic::IMessage> messagePtr)
	{
		// @todo Nos proponen un mensaje, con ayuda de accept()
		// evaluamos si lo encolamos o no

		return false;

	} // set
	
	//---------------------------------------------------------

	void CCommunicationPort::processMessages()
	{
		// @todo Debemos procesar todos los mensajes de la cola
		// con ayuda del m�todo process()

	} // processMessages

} // namespace Logic
