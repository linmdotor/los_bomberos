/**
@file ReferenceCounter.h

Contador de referencias

@author Daniel Parra lopez
@date Noviembre, 2015
*/
#ifndef __Logic_Reference_Counter_H
#define __Logic_Reference_Counter_H


//declaración de la clase
namespace Logic
{
	class ReferenceCounter
	{
	protected:
		/**
		Almacena el numero de referencias que apuntan al puntero
		*/
		int m_numReferences;
	public:
		ReferenceCounter();
		~ReferenceCounter();

		/**
		Incrementa el numero de referencias
		@return numero de referencias actuales
		*/
		int addRef();
		/**
		Decrementa el numero de referencias
		@return numero de referencias actuales
		*/
		int remRef();
	}; //class ReferenceCounter
} //namespace Logic
#endif // __Logic_Reference_Counter_H