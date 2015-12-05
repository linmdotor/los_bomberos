/**
@file PlayerController.cpp

Contiene la implementación de la clase CPlayerController. Se encarga de
recibir eventos del teclado y del ratón y de interpretarlos para
mover al jugador.

@see GUI::CPlayerController

@author David Llansó
@date Agosto, 2010
*/

#include "PlayerController.h"
#include "InputManager.h"

#include "Logic/Entity/Entity.h"
#include "Logic/Entity/Messages/IMessage.h"

#include <cassert>

#define TURN_FACTOR 0.001f

namespace GUI {

	CPlayerController::CPlayerController() : _controlledAvatar(0)
	{

	} // CPlayerController

	//--------------------------------------------------------

	CPlayerController::~CPlayerController()
	{
		deactivate();

	} // ~CPlayerController

	//--------------------------------------------------------

	void CPlayerController::activate()
	{		
		CInputManager::getSingletonPtr()->addKeyListener(this);
		CInputManager::getSingletonPtr()->addMouseListener(this);

	} // activate

	//--------------------------------------------------------

	void CPlayerController::deactivate()
	{
		CInputManager::getSingletonPtr()->removeKeyListener(this);
		CInputManager::getSingletonPtr()->removeMouseListener(this);

	} // deactivate

	//--------------------------------------------------------

	bool CPlayerController::keyPressed(TKey key)
	{
		if(_controlledAvatar)
		{
			//se almacenara en un puntero inteligente y se borrará más tarde
			Logic::MessageControl *message = new Logic::MessageControl();
			switch(key.keyId)
			{
			case GUI::Key::W:
				message->m_animation = "walk";
				break;
			case GUI::Key::S:
				message->m_animation = "walkBack";
				break;
			case GUI::Key::A:
				message->m_animation = "strafeLeft";
				break;
			case GUI::Key::D:
				message->m_animation = "strafeRight";
				break;
			default:
				return false;
			}
			_controlledAvatar->emitMessage(message);
			return true;
		}
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CPlayerController::keyReleased(TKey key)
	{
		if(_controlledAvatar)
		{
			//se almacenara en un puntero inteligente y se borrará más tarde
			Logic::MessageControl *m = new Logic::MessageControl();
			switch(key.keyId)
			{
			case GUI::Key::W:
			case GUI::Key::S:
				m->m_animation = "stopWalk";
				break;

			case GUI::Key::A:
			case GUI::Key::D:
				m->m_animation = "stopStrafe";
				break;

			default:
				return false;
			}
			_controlledAvatar->emitMessage(m);
			return true;
		}
		return false;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CPlayerController::mouseMoved(const CMouseState &mouseState)
	{
		if(_controlledAvatar)
		{
			//se almacenara en un puntero inteligente y se borrará más tarde
			Logic::MessageControl *m = new Logic::MessageControl();
			m->m_animation = "turn";
			m->m_turn = -(float)mouseState.movX * TURN_FACTOR;
			_controlledAvatar->emitMessage(m);
			return true;
		}
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CPlayerController::mousePressed(const CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------

	bool CPlayerController::mouseReleased(const CMouseState &mouseState)
	{
		return false;

	} // mouseReleased

} // namespace GUI
