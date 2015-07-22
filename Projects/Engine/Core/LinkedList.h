/****************************************************************************
//	Filename: LinkedList.h
//	Description: It is a linked list, from back to forward.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include "Engine/Core/ObjectPool.h"

namespace neko
{

template <class ElemType>
class LinkedList
{
	enum { DEFAULT_SIZE = 64 };
	struct Node
	{
		Node* pNext;
		Node* pPrev;
		ElemType* pData;
	};
public:
	LinkedList(uint32 uSize = DEFAULT_SIZE):
		m_nodes(uSize, true),
		m_pFirst(NULL),
		m_pLast(NULL){}
	~LinkedList(){}

	void AddToFirst(ElemType* pData);
	void AddToLast(ElemType* pData);
	void Remove(ElemType* pData);
	void Remove(const Node* pNode);
	void RemoveFirst();
	void RemoveLast();
	void Sort();

private:
	PRIVATE_COPY(LinkedList);

	bool InsertData(Node* pNode)
	{
		if(m_pFirst == NULL)
		{
			m_pFirst = pNode;
			return true;
		}
		else if(m_pLast == NULL)
		{
			m_pLast = pNode;
			m_pLast->pPrev = m_pFirst;
			m_pFirst->pNext = m_pLast;
			return true;
		}

		return false;
	}

	Node* AllocNode(ElemType* pData)
	{
		Node* pNode = m_nodes.Alloc();
		pNode->pData = pData;
		pNode->pPrev = NULL;
		pNode->pNext = NULL;
		return pNode;
	}

	ObjectPool<Node> m_nodes;

	Node* m_pFirst;
	Node* m_pLast;

public:
	class Iterator
	{
	public:
		Iterator(Node* pNode) : m_pCurrent(pNode) {}
		Iterator& operator++() { m_pCurrent = m_pCurrent->pNext; return *this; }
		Iterator& operator--() { m_pCurrent = m_pCurrent->pPrev; return *this; }

		const ElemType* operator*() const { return m_pCurrent->pData; }
		ElemType* operator*() const { return m_pCurrent->pData; }
		const Node* GetNode() const { return m_pCurrent; }
		bool IsEnd() const { return m_pCurrent == NULL; }

	private:
		Node* m_pCurrent;
	};

	Iterator Begin() const { return Iterator(m_pFirst); }
	Iterator End() const { return Iterator((m_pLast != NULL) ? m_pLast : m_pFirst ); }
};

template <class ElemType>
void LinkedList<ElemType>::AddToFirst(ElemType* pData)
{
	Node* pNode = AllocNode(pData);

	if(!InsertData(pNode))
	{
		pNode->pNext = m_pFirst;
		m_pFirst->pPrev = pNode;
		m_pFirst = pEntry;
	}
}

template <class ElemType>
void LinkedList<ElemType>::AddToLast(ElemType* pData)
{
	Node* pNode = AllocNode(pData);

	if(!InsertData(pNode))
	{
		pNode->pPrev = m_pLast;
		m_pLast->pNext = pNode;
		m_pLast = pNode;
	}
}

template <class ElemType>
void LinkedList<ElemType>::Remove(ElemType* pData)
{
	Node* pNode = m_pFirst;
	while(pNode != NULL)
	{
		if(pNode->pData == pData)
		{
			if(pNode == m_pFirst)
			{
				RemoveFirst();
			}
			else if(pNode == m_pLast)
			{
				RemoveLast();
			}
			else
			{
				Node* pNext = pNode->pNext;
				Node* pPrev = pNode->pPrev;
			
				if(pNext)
				{
					pNext->pPrev = pPrev;
				}

				if(pPrev)
				{
					pPrev->pNext = pNext;
				}

				m_nodes.Free(pNode);
			}

			pNode = NULL;
		}
	}
}

template <class ElemType>
void LinkedList<ElemType>::Remove(const Node* pData)
{
	// Not yet implemented
	ASSERT(false);
}

template <class ElemType>
void LinkedList<ElemType>::RemoveFirst()
{
	if(m_pFirst != NULL)
	{
		Node* pNext = m_pFirst->pNext;
		m_nodes.Free(m_pFirst);
		m_pFirst = pNext;

		if(m_pFirst != NULL)
		{
			m_pFirst->pPrev = NULL;

			if(m_pFirst == m_pLast)
			{
				m_pLast = NULL;
			}
		}
	}
}

template <class ElemType>
void LinkedList<ElemType>::RemoveLast()
{
	if(m_pLast != NULL)
	{
		Node* pPrev = m_pLast->pPrev;
		m_nodes.Free(m_pLast);
		m_pLast = pPrev;
		m_pLast->pNext = NULL;

		if(m_pLast == m_pFirst)
		{
			m_pLast = NULL;
		}
	}
	else
	{
		RemoveFirst();
	}
}

template <class ElemType>
void LinkedList<ElemType>::Sort()
{
	ElemType* pSwap = NULL;
	Node* pNode = NULL;
	Node* pNext = NULL;

	bool bSwapped = false;
	do
	{
		bSwapped = false;
		pNode = m_pFirst;

		while(pNode && pNode->pNext)
		{
			pNext = pNode->pNext;

			if(*pNext->pData < *pNode->pData)
			{
				pSwap = pNode->pData;
				pNode->pData = pNext->pData;
				pNext->pData = pSwap;
				bSwapped = true;
			}
			pNode = pNext;
		}
	} while(bSwapped)
}

}	//	namespace neko