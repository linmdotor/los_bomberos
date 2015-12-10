//---------------------------------------------------------------------------
// MenuState.cpp
//---------------------------------------------------------------------------

/**
@file MenuState.cpp

Contiene la implementaci�n del estado de men�.

@see Application::CApplicationState
@see Application::CLoadingState

@author Daniel Parra L�pez
@date Diciembre, 2015
*/

#include "LoadingState.h"
#include "ExampleLoadingBar.h"
#include <OGRE\OgreResourceManager.h>


namespace Application {

	CLoadingState::~CLoadingState()
	{
	} // ~CLoadingState

	//--------------------------------------------------------

	bool CLoadingState::init()
	{
		CApplicationState::init();
	
		return true;

	} // init

	//--------------------------------------------------------

	void CLoadingState::release()
	{
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CLoadingState::activate()
	{
		CApplicationState::activate();
		ExampleLoadingBar *listener = new ExampleLoadingBar();
		Ogre::ResourceGroupManager::getSingleton().addResourceGroupListener(listener);
		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Scene");
		
		Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup("Scene");

		Ogre::ResourceGroupManager::getSingleton().removeResourceGroupListener(listener);

		
	} // activate

	//--------------------------------------------------------

	void CLoadingState::deactivate()
	{		
	
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CLoadingState::tick(unsigned int msecs)
	{
		CApplicationState::tick(msecs);

		_app->setState("game");

	} // tick


} // namespace Application
