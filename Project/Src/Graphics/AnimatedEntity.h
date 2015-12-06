//---------------------------------------------------------------------------
// AnimatedEntity.h
//---------------------------------------------------------------------------

/**
@file AnimatedEntity.h

Contiene la declaraci�n de la clase que representa una entidad gr�fica 
con animaciones.

@see Graphics::CAnimatedEntity
@see Graphics::CEntity

@author David Llans�
@date Julio, 2010
*/

#ifndef __Graphics_AnimatedEntity_H
#define __Graphics_AnimatedEntity_H

#include "Entity.h"

// Predeclaraci�n de clases para ahorrar tiempo de compilaci�n
namespace Ogre 
{
	class AnimationState;
}

namespace Graphics 
{
	class CScene;
}
	
namespace Graphics 
{
	/**
	Esta clase debe ser implementada por las clases que quieren
	registrarse en una entidad animada para enterarse de cuando
	terminan las animaciones de �sta.
	
	@ingroup graphicsGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CAnimatedEntityListener 
	{
	public:

		/**
		M�todo que ser� invocado siempre que se termine una animaci�n.
		Las animaciones en c�clicas no invocar�n nunca este m�todo.

		@param animation Nombre de la animaci�n terminada.
		*/
		virtual void animationFinished(const std::string &animation) {}

	}; // CAnimatedEntityListener

	/**
	Clase que representa una entidad gr�fica con animaciones. Especializa la clase
	Graphics::CEntity por lo que contiene una referencia a una entidad de 
	Ogre y al Nodo que la contiene. A�ade la posibilidad de activar una animaci�n 
	y reproducirla.
	<p>
	Esta clase es bastante sencilla y solo controlamos una animaci�n activa.
	Podr�a ser m�s sofisticada permitiendo interpolaci�n de animaciones o avisando
	mediante observers cuando una animaci�n termina de reproducirse.
	<p>
	Oculta los detalles escabrosos del motor gr�fico.
	
	@ingroup graphicsGroup

	@author David Llans�
	@date Julio, 2010
	*/
	class CAnimatedEntity : public CEntity
	{
	public:

		/**
		Constructor de la clase.

		@param name Nombre de la entidad.
		@param mesh Nombre del modelo que debe cargarse.
		*/
		CAnimatedEntity(const std::string &name, const std::string &mesh):
					CEntity(name,mesh), _currentAnimation(0) {}

		/**
		Destructor de la aplicaci�n.
		*/
		virtual ~CAnimatedEntity() {}

		/**
		Activa una animaci�n a partir de su nombre.

		@param anim Nombre de la animaci�n a activar.
		@param loop true si la animaci�n debe reproducirse c�clicamente.
		@return true si la animaci�n solicitada fue correctamente activada.
		*/
		bool setAnimation(const std::string &anim, bool loop);
		
		/**
		Desactiva una animaci�n a partir de su nombre.

		@param anim Nombre de la animaci�n a activar.
		@return true si la animaci�n solicitada fue correctamente desactivada.
		*/
		bool stopAnimation(const std::string &anim);
		
		/**
		Desactiva todas las animaciones de una entidad.
		*/
		void stopAllAnimations();

		/**
		Funci�n que registra al oyente de la entidad gr�fica. Por 
		simplicidad solo habr� un oyente por entidad.
		*/
		void setObserver(CAnimatedEntityListener *observer)
											{_observer = observer;}

		/**
		Funci�n que quita al oyente de la entidad gr�fica. Por 
		simplicidad solo habr� un oyente por entidad.
		*/
		void removeObserver(CAnimatedEntityListener *observer)
							{if(_observer = observer) _observer = 0;}

	protected:

		/**
		Objeto oyente que es informado de cambios en la entidad como 
		la terminaci�n de las animaciones. Por simplicidad solo habr�
		un oyente por entidad.
		*/
		CAnimatedEntityListener *_observer;

		// Cada entidad debe pertenecer a una escena. Solo permitimos
		// a la escena actualizar el estado.
		friend class CScene;
		
		/**
		Actualiza el estado de la entidad cada ciclo.
		
		@param secs N�mero de milisegundos transcurridos desde la �ltima 
		llamada.
		*/
		virtual void tick(float secs);

		/**
		Animaci�n que tiene la entidad activada.
		*/
		Ogre::AnimationState *_currentAnimation;

	}; // class CAnimatedEntity

} // namespace Graphics

#endif // __Graphics_AnimatedEntity_H
