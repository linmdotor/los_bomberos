/**
@file ReferenceCounterPtr.h

Template con logica de puntero inteligente

@see ReferenceCounter.h

@author Daniel Parra Lopez
@date Noviembre, 2015
*/
#ifndef __Logic_Reference_Counter_Ptr_H
#define __Logic_Reference_Counter_Ptr_H

//declaración de la clase
namespace Logic
{
	template <class T>
	class ReferenceCounterPtr
	{
	private:
		/**
		Puntero al dato que hereda de ReferenceCounter
		*/
		T *ptr;
	public:
		/**
		Constructor del puntero inteligente
		@param value Puntero con el dato
		*/
		ReferenceCounterPtr(T* value) : ptr(value)
		{
			ptr->addRef();
		}
		/**
		Constructor por copia del puntero inteligente
		@param rc puntero que se va a copiar
		*/
		ReferenceCounterPtr(const ReferenceCounterPtr<T>& rc) : ptr(rc.ptr)
		{
			ptr->addRef();
		}
		/**
		Destructor del puntero inteligente, si el conteo es 0 destruye el dato
		*/
		~ReferenceCounterPtr()
		{
			if (ptr->remRef() < 1)
			{
				delete ptr;
			}
		}
		/**
		Devuelve el contenido del dato
		@return contenido del dato
		*/
		T& operator*() const
		{
			return *ptr;
		}
		/**
		Devuelve un puntero al dato
		@return puntero al dato
		*/
		T *operator->() const
		{
			return ptr;
		}
		/**
		Devuelve un puntero al dato
		@return puntero al dato
		*/
		T *get() const
		{
			return ptr;
		}
		/**
		Operador igual, decrementa el conteo que tenia almacenado, asigna el nuevo y lo incrementa
		@return contenido del dato
		*/
		ReferenceCounterPtr<T>& operator = (const ReferenceCounterPtr<T>& sp)
		{
			// Assignment operator
			if (this != &sp) // Avoid self assignment
			{
				// Decrement the old reference count
				// if reference become zero delete the old data
				if (ptr->remRef() < 1)
				{
					delete ptr;
				}

				// Copy the data and reference pointer
				// and increment the reference count
				ptr = sp.ptr;
				ptr->addRef();
			}
			return *this;
		}

	}; //class ReferenceCounterPtr
} //namespace Logic
#endif //__Logic_Reference_Counter_Ptr_H
