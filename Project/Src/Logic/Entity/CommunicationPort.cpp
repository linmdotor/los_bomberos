/**
@file CommunicationPort.cpp

Contiene la implementación de la clase que se encarga del intercambio 
de los mensajes.

@see Logic::CCommunicationPort

@author David Llansó García
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
		// Nos proponen un mensaje, con ayuda de accept()
		// evaluamos si lo encolamos o no
		if (accept(messagePtr))
		{
			_messages.push_back(messagePtr);
			return true;
		}
		return false;

	} // set
	
	//---------------------------------------------------------

	void CCommunicationPort::processMessages()
	{
		// Debemos procesar todos los mensajes de la cola
		// con ayuda del método process()
		TMessageList::iterator it = _messages.begin();
		TMessageList::iterator itEnd = _messages.end();
		for (; it != itEnd; ++it)
		{
			process((*it));
		}
		_messages.clear();

	} // processMessages

} // namespace Logic
