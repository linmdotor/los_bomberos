/*
-----------------------------------------------------------------------------
This source file is part of OGRE
(Object-oriented Graphics Rendering Engine)
For the latest info, see http://www.ogre3d.org/

Copyright (c) 2000-2014 Torus Knot Software Ltd
Also see acknowledgements in Readme.html

You may use this sample code for anything you like, it is not covered by the
same license as the rest of the engine.
-----------------------------------------------------------------------------
*/
/*
-----------------------------------------------------------------------------
Filename:    ExampleLoadingBar.h
Description: Defines an example loading progress bar which you can use during 
startup, level changes etc to display loading progress. 
IMPORTANT: Note that this progress bar relies on you having the OgreCore.zip 
package already added to a resource group called 'Bootstrap' - this provides
the basic resources required for the progress bar and will be loaded automatically.
*/
#include "OgreResourceGroupManager.h"
#include "OgreException.h"
#include "OgreRenderWindow.h"

using namespace Ogre;

/** Defines an example loading progress bar which you can use during 
    startup, level changes etc to display loading progress. 
@remarks
    Basically you just need to create an instance of this class, call start()
    before loading and finish() afterwards. You may also need to stop areas of
    your scene rendering in between since this method will call 
    RenderWindow::update() to update the display of the bar - we advise using
    SceneManager's 'special case render queues' for this, see
    SceneManager::addSpecialCaseRenderQueue for details.
@note 
    This progress bar relies on you having the OgreCore.zip package already 
    added to a resource group called 'Bootstrap' - this provides the basic 
    resources required for the progress bar and will be loaded automatically.
*/
class ExampleLoadingBar : public ResourceGroupListener
{
protected:
	size_t scriptsSize;
	size_t resourcesSize;

	size_t currentScript;
	size_t currentResource;

public:
	ExampleLoadingBar() : scriptsSize(0), resourcesSize(0), currentScript(0), currentResource(0) {}
    virtual ~ExampleLoadingBar(){}


    /** Hide the loading bar and stop listening. 
    */
    virtual void finish(void)
    {

        // Unregister listener
        //ResourceGroupManager::getSingleton().removeResourceGroupListener(this);

    }


    // ResourceGroupListener callbacks
    void resourceGroupScriptingStarted(const String& groupName, size_t scriptCount)
    {
		scriptsSize = scriptCount;
		printf("Recursos totales de scripting: %d\n", scriptsSize);
    }
    void scriptParseStarted(const String& scriptName, bool &skipThisScript)
    {
		++currentScript;
		
    }
    void scriptParseEnded(const String& scriptName, bool skipped)
    {
		printf("Scripts cargados %d/%d\n", currentScript, scriptsSize);
    }
    void resourceGroupScriptingEnded(const String& groupName)
    {
		printf("Todos los scripts cargados\n");
    }
    void resourceGroupLoadStarted(const String& groupName, size_t resourceCount)
    {
		resourcesSize = resourceCount;
		printf("Recursos totales de load: %d\n", resourcesSize);
    }
    void resourceLoadStarted(const ResourcePtr& resource)
    {
		++currentResource;
    }
    void resourceLoadEnded(void)
    {
		printf("Recursos cargados %d/%d\n", currentResource, resourcesSize);
    }
    void worldGeometryStageStarted(const String& description)
    {
       
    }
    void worldGeometryStageEnded(void)
    {
        
    }
    void resourceGroupLoadEnded(const String& groupName)
    {
		printf("Todos los recursos cargados\n");
    }

    Ogre::DataStreamPtr resourceLoading(const String &name, const String &group, Resource *resource)
    {
        return Ogre::DataStreamPtr();
    }

    bool resourceCollision(ResourcePtr &resource, ResourceManager *resourceManager)
    {
        return false;
    }

};

