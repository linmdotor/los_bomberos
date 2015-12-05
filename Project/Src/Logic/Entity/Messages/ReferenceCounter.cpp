#include "ReferenceCounter.h"

namespace Logic
{
	ReferenceCounter::ReferenceCounter() : m_numReferences(0)
	{
	}
	ReferenceCounter::~ReferenceCounter()
	{
	}
	int ReferenceCounter::addRef()
	{
		return ++m_numReferences;
	}
	int ReferenceCounter::remRef()
	{
		return --m_numReferences;
	}
}