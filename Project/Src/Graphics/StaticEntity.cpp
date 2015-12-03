//---------------------------------------------------------------------------
// StaticEntity.cpp
//---------------------------------------------------------------------------

/**
@file StaticEntity.cpp

Contiene la implementaci�n de la clase que representa una entidad gr�fica 
est�tica.

@see Graphics::CStaticEntity
@see Graphics::CEntity

@author David Llans�
@date Julio, 2010
*/

#include "StaticEntity.h"
#include "Scene.h"

#include <assert.h>

#include <OgreSceneManager.h>
#include <OgreStaticGeometry.h>

namespace Graphics 
{
		
	bool CStaticEntity::addToStaticGeometry()
	{
		if(_entityNode)
		{
			_scene->getStaticGeometry()->addSceneNode(_entityNode);
			_entityNode->detachAllObjects();
			return true;
		}
		return false;

	} // addToStaticGeometry


} // namespace Graphics
