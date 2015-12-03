//---------------------------------------------------------------------------
// OgreClock.cpp
//---------------------------------------------------------------------------

/**
@file OgreClock.cpp

Contiene la implementaci�n de un interfaz para un temporizador.

@see Application::COgreClock

@author David Llans�
@date Julio, 2010
*/

#include "OgreClock.h"
#include "BaseSubsystems/Server.h"

#include <OgreTimer.h>
#include <cassert>

namespace Application {

	COgreClock::COgreClock() : IClock() 
	{
		_timer = BaseSubsystems::CServer::getSingletonPtr()->getAppTimer();

	} // COgreClock

	//--------------------------------------------------------

	unsigned long COgreClock::getPhysicalTime()
	{
		assert(_timer);
		return _timer->getMilliseconds();
	} // getPhysicalTime


} // namespace Application
