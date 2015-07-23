/****************************************************************************
//	Filename: ObjectPool.h
//	Description: 
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/DArray.h"

#include <new>

namespace neko
{

template <class ElemType>
class ObjectPool
{
public:
	ObjectPool(uint32 uSize, bool bCanResize = true);
	~ObjectPool();

	ElemType* Alloc();
	void Free(ElemType* pData);
	uint32 GetSize() const { return m_uSize; }

private:
	PRIVATE_COPY(ObjectPool);

	struct Entry
	{
		Entry():
			m_pNext(NULL),
			m_pPrev(NULL){}
		Entry* m_pNext;
		Entry* m_pPrev;
		ElemType m_data;
	};

	Entry* GetHeaderFromData(ElemType* pData)
	{
		uint8* pHeader = (uint8*)pData;
		pHeader -= sizeof(Entry*) * 2;
		return (Entry*)pHeader;
	}
	// TODO: Remove DArray and exchange it with a similar class based on raw byte (uint8) memory so we dont call double constructors etc.
	DArray<Entry, false> m_pool;

	Entry* m_pFirst;
	Entry* m_pFirstFree;

	uint32 m_uSize;
	bool m_bCanResize;

public:
	class Iterator
	{
	public:
		Iterator(Entry* pEntry) : m_pCurrent(pEntry){}
		Iterator& operator++() { m_pCurrent = m_pCurrent->m_pNext; return *this; }
		Iterator& operator--() { m_pCurrent = m_pCurrent->m_pPrev; return *this; }

		const ElemType* operator*() const { return &m_pCurrent->m_data; }
		ElemType* operator*() { return &m_pCurrent->m_data; }
		bool IsEnd() const { return m_pCurrent == NULL; }

	private:
		Entry* m_pCurrent;
	};

	Iterator Begin() const { return Iterator(m_pFirst); }
};

template <class ElemType>
ObjectPool<ElemType>::ObjectPool(uint32 uSize, bool bCanResize)
{
	m_pool.SetSize(uSize);
	m_bCanResize = bCanResize;
	m_uSize = 0;
	m_pFirst = NULL;
	m_pFirstFree = &m_pool[0];
	m_pFirstFree->m_pPrev = NULL;

	Entry* pPrev = m_pFirstFree;
	for(uint32 i = 1; i < uSize; i++)
	{
		Entry* pCurrent = &m_pool[i];
		pPrev->m_pNext = pCurrent;
		pCurrent->m_pPrev = pPrev;
		pPrev = pCurrent;
	}
	pPrev->m_pNext = NULL;
}

template <class ElemType>
ObjectPool<ElemType>::~ObjectPool()
{
	m_pool.Clear();
}

template <class ElemType>
ElemType* ObjectPool<ElemType>::Alloc()
{
	if(m_pFirstFree == NULL)
	{
		//	resize here
	}

	Entry* pAlloc = m_pFirstFree;
	ASSERT(pAlloc != NULL);
	m_pFirstFree = pAlloc->m_pNext;
	if(m_pFirstFree)
	{
		m_pFirstFree->m_pPrev = NULL;
	}

	if(m_pFirst == NULL)
	{
		m_pFirst = pAlloc;
		m_pFirst->m_pNext = NULL;
		m_pFirst->m_pPrev = NULL;
	}
	else
	{
		m_pFirst->m_pPrev = pAlloc;
		pAlloc->m_pNext = m_pFirst;
		m_pFirst = pAlloc;
	}

	m_uSize++;
	new(&pAlloc->m_data) ElemType();
	return &pAlloc->m_data;
}

template <class ElemType>
void ObjectPool<ElemType>::Free(ElemType* pData)
{
	Entry* pEntry = GetHeaderFromData(pData);
	pEntry->m_data.~ElemType();
	Entry* pPrev = pEntry->m_pPrev;
	Entry* pNext = pEntry->m_pNext;
	m_uSize--;

	if(pPrev)
	{
		pPrev->m_pNext = pNext;
	}
	
	if(pNext)
	{
		pNext->m_pPrev = pPrev;
	}

	if(m_pFirstFree)
	{
		m_pFirstFree->m_pPrev = pEntry;
	}

	pEntry->m_pNext = m_pFirstFree;
	pEntry->m_pPrev = NULL;
	m_pFirstFree = pEntry;
}

}	//	namespace neko