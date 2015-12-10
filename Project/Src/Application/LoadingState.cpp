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
#include "GameState.h"
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

		Ogre::ResourceGroupManager::getSingleton().addResourceGroupListener(this);
		Ogre::ResourceGroupManager::getSingletonPtr()->initialiseResourceGroup("Scene");
		
		Ogre::ResourceGroupManager::getSingletonPtr()->loadResourceGroup("Scene");

		Ogre::ResourceGroupManager::getSingleton().removeResourceGroupListener(this);

		_app->addState("game", new CGameState(_app));

		
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

	// ResourceGroupListener callbacks
	void CLoadingState::resourceGroupScriptingStarted(const Ogre::String& groupName, size_t scriptCount)
	{
		scriptsSize = scriptCount;
		printf("Recursos totales de scripting: %d\n", scriptsSize);
	}
	void CLoadingState::scriptParseStarted(const Ogre::String& scriptName, bool &skipThisScript)
	{
		++currentScript;
		printf("Recurso actual: %s\n", scriptName.c_str());
	}
	void CLoadingState::scriptParseEnded(const Ogre::String& scriptName, bool skipped)
	{
		printf("Scripts cargados %d/%d\n", currentScript, scriptsSize);
	}
	void CLoadingState::resourceGroupScriptingEnded(const Ogre::String& groupName)
	{
		printf("Todos los scripts cargados\n");
	}
	void CLoadingState::resourceGroupLoadStarted(const Ogre::String& groupName, size_t resourceCount)
	{
		resourcesSize = resourceCount;
		printf("Recursos totales de load: %d\n", resourcesSize);
	}
	void CLoadingState::resourceLoadStarted(const Ogre::ResourcePtr& resource)
	{
		++currentResource;
		printf("Recurso actual: %s\n", resource->getName().c_str());
	}
	void CLoadingState::resourceLoadEnded(void)
	{
		printf("Recursos cargados %d/%d\n", currentResource, resourcesSize);
	}
	void CLoadingState::worldGeometryStageStarted(const Ogre::String& description)
	{

	}
	void CLoadingState::worldGeometryStageEnded(void)
	{

	}
	void CLoadingState::resourceGroupLoadEnded(const Ogre::String& groupName)
	{
		printf("Todos los recursos cargados\n");
	}

} // namespace Application
