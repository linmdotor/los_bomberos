/**
@file IMessage.h

Contiene la declaraci�n de la clase base de los mensajes.

@author Daniel Parra
@date Noviembre, 2015
*/

#ifndef __Logic_IMessage_H
#define __Logic_IMessage_H

#include "BaseSubsystems/Math.h"
#include "ReferenceCounter.h"

//declaraci�n de la clase
namespace Logic
{
	class CComponent;
	class IMessage : public ReferenceCounter
	{
	public:
		enum MESSAGE_TYPE
		{
			MESSAGE_TYPE_UNASSIGNED = 0xFFFFFFFF,
			MESSAGE_TYPE_SET_POSITION,
			MESSAGE_TYPE_SET_CONTROL,
			MESSAGE_TYPE_SET_TRANSFORM,
			MESSAGE_TYPE_SET_ANIMATION,
			MESSAGE_TYPE_STOP_ANIMATION
		};
		/**
		Tipo del mensaje
		*/
		IMessage::MESSAGE_TYPE m_type;
		/**
		Componente que emite el mensaje
		*/
		CComponent* emitter;
		IMessage() : emitter(0) {}
		virtual ~IMessage(){}
	}; //IMessage

	class MessagePosition : public IMessage
	{
	public:
		MessagePosition() : IMessage(), m_position()
		{
			m_type = MESSAGE_TYPE_SET_POSITION;
		}
		virtual ~MessagePosition(){};
		/**
		Vector con la posicion a asignar
		*/
		Vector3 m_position;
	}; //MessagePosition
	
	class MessageControl : public IMessage
	{
	public:
		MessageControl() : IMessage(), m_animation(), m_turn(0)
		{
			m_type = MESSAGE_TYPE_SET_CONTROL;
		}
		virtual ~MessageControl(){};
		/**
		Nombre de la animacion
		*/
		std::string m_animation;
		/**
		Cantidad de giro
		*/
		float m_turn;
	}; //MessageControl

	class MessageTransform : public IMessage
	{
	public:
		MessageTransform() : IMessage(), m_transform()
		{
			m_type = MESSAGE_TYPE_SET_TRANSFORM;
		}
		virtual ~MessageTransform(){};
		/**
		Transformacion del objeto
		*/
		Matrix4 m_transform;
	}; //MessageControl
	class MessageSetAnimation : public IMessage
	{
	public:
		MessageSetAnimation() : IMessage(), m_animation(), m_loop(false)
		{
			m_type = MESSAGE_TYPE_SET_ANIMATION;
		}
		virtual ~MessageSetAnimation(){};
		/**
		Nombre de la animacion
		*/
		std::string m_animation;
		/**
		Controla si la animacion se reproduce en bucle
		*/
		bool m_loop;
	}; //MessageSetAnimation
	
}
#endif//__Logic_IMessage_H
