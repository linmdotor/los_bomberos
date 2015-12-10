//---------------------------------------------------------------------------
// MenuState.cpp
//---------------------------------------------------------------------------

/**
@file MenuState.cpp

Contiene la implementaci�n del estado de men�.

@see Application::CApplicationState
@see Application::CMenuState

@author David Llans�
@date Agosto, 2010
*/

#include "MenuState.h"

#include "GUI/Server.h"

#include <CEGUI/CEGUI.h>

namespace Application {

	CMenuState::~CMenuState() 
	{
	} // ~CMenuState

	//--------------------------------------------------------

	bool CMenuState::init() 
	{
		CApplicationState::init();

		// Cargamos la ventana que muestra el men�
		_menuWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("Menu.layout");
		_pauseMenuWindow = CEGUI::WindowManager::getSingletonPtr()->loadLayoutFromFile("PauseMenu.layout");
		
		// Asociamos los botones del men� con las funciones que se deben ejecutar.
		_menuWindow->getChildElement("Start")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
				CEGUI::SubscriberSlot(&CMenuState::startReleased, this));
		
		_menuWindow->getChildElement("Exit")->
			subscribeEvent(CEGUI::PushButton::EventClicked, 
				CEGUI::SubscriberSlot(&CMenuState::exitReleased, this));

		_pauseMenuWindow->getChildElement("Continue")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&CMenuState::continueReleased, this));

		_pauseMenuWindow->getChildElement("Exit")->
			subscribeEvent(CEGUI::PushButton::EventClicked,
			CEGUI::SubscriberSlot(&CMenuState::exitReleased, this));

		_pauseMenuWindow->deactivate();
		_pauseMenuWindow->setVisible(false);

	
		return true;

	} // init

	//--------------------------------------------------------

	void CMenuState::release() 
	{
		CApplicationState::release();

	} // release

	//--------------------------------------------------------

	void CMenuState::activate() 
	{
		CApplicationState::activate();

		if (m_mainMenu)
		{
			// Activamos la ventana que nos muestra el men� y activamos el rat�n.
			CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_menuWindow);
			_menuWindow->setVisible(true);
			_menuWindow->activate();
		}
		else
		{
			CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_pauseMenuWindow);
			_pauseMenuWindow->setVisible(true);
			_pauseMenuWindow->activate();
		}
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().show();

	} // activate

	//--------------------------------------------------------

	void CMenuState::deactivate() 
	{		
		// Desactivamos la ventana GUI con el men� y el rat�n.
		CEGUI::System::getSingletonPtr()->getDefaultGUIContext().getMouseCursor().hide();
		if (m_mainMenu)
		{
			_menuWindow->deactivate();
			_menuWindow->setVisible(false);
		}
		else
		{
			CEGUI::System::getSingletonPtr()->getDefaultGUIContext().setRootWindow(_pauseMenuWindow);
			_pauseMenuWindow->deactivate();
			_pauseMenuWindow->setVisible(false);
		}
		CApplicationState::deactivate();

	} // deactivate

	//--------------------------------------------------------

	void CMenuState::tick(unsigned int msecs) 
	{
		CApplicationState::tick(msecs);

	} // tick

	//--------------------------------------------------------

	bool CMenuState::keyPressed(GUI::TKey key)
	{
		return false;

	} // keyPressed

	//--------------------------------------------------------

	bool CMenuState::keyReleased(GUI::TKey key)
	{
		switch(key.keyId)
		{
		case GUI::Key::ESCAPE:
			_app->exitRequest();
			break;
		case GUI::Key::RETURN:
			if (m_mainMenu)
			{
				//@todo: código duplicado, mover a función
				_app->setState("loading");
				m_mainMenu = false;
				_menuWindow->deactivate();
				_menuWindow->setVisible(false);
			}
			else
			{
				_app->setState("game");
			}
			break;
		default:
			return false;
		}
		return true;

	} // keyReleased

	//--------------------------------------------------------
	
	bool CMenuState::mouseMoved(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseMoved

	//--------------------------------------------------------
		
	bool CMenuState::mousePressed(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mousePressed

	//--------------------------------------------------------


	bool CMenuState::mouseReleased(const GUI::CMouseState &mouseState)
	{
		return false;

	} // mouseReleased
			
	//--------------------------------------------------------
		
	bool CMenuState::startReleased(const CEGUI::EventArgs& e)
	{
		//_app->setState("game");
		_app->setState("loading");
		m_mainMenu = false;
		_menuWindow->deactivate();
		_menuWindow->setVisible(false);
		return true;

	} // startReleased

	bool CMenuState::continueReleased(const CEGUI::EventArgs& e)
	{
		_app->setState("game");
		//_app->setState("loading");
		return true;

	} // startReleased
			
	//--------------------------------------------------------

	bool CMenuState::exitReleased(const CEGUI::EventArgs& e)
	{
		_app->exitRequest();
		return true;

	} // exitReleased

} // namespace Application
