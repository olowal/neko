/****************************************************************************
//	Filename: DArray.h
//	Description: A resizeable array.
*****************************************************************************/

#pragma once
#include "Engine/Common/Common.h"
#include <new.h>

namespace neko
{

template <class ElemType,bool NeedConstructor=true,int dwGranMask=0xf>
class DArray
{
public:
	typedef ElemType TElemType;

	DArray() : m_pxE(NULL), m_iCount(0) {};
	~DArray() {SetSize(0);};

	TElemType* GetPtr()const{return m_pxE;}
	void CopyFromMemory(TElemType* p_pElemType, int p_iSize)
	{
		if(p_iSize>m_iCount){return;}
		memcpy_s(m_pxE,m_iCount*sizeof(TElemType),p_pElemType,p_iSize*sizeof(TElemType));
	}

	void SetSize(int p_iNewSize)
	{
		if(m_iCount<p_iNewSize)
		{
			ReallocMemory(p_iNewSize);
			if(NeedConstructor)
			{
				Construct(m_iCount,p_iNewSize-m_iCount);
			};
			m_iCount=p_iNewSize;
		}
		else if(m_iCount>p_iNewSize)
		{
			if(NeedConstructor)
			{
				Destruct(p_iNewSize,m_iCount-p_iNewSize);
			};
			ReallocMemory(p_iNewSize);
			m_iCount=p_iNewSize;
		};
	};

	int Insert(int p_iIndex)
	{
		ReallocMemory(m_iCount+1);
		MoveElements(p_iIndex+1,p_iIndex,m_iCount-p_iIndex);
		m_iCount++;
		if(NeedConstructor){Construct(p_iIndex,1);};
	};

	void Pop()
	{
		if(m_iCount>0)
		{
			SetSize(m_iCount-1);
		}
	}

	void Remove(TElemType p_elemType)
	{
		int i,iC=m_iCount;
		for(i=0;i<iC;i++)
		{
			if(m_pxE[i]==p_elemType)
			{
				Delete(i);
				break;
			}
		}
	}

	void Delete(int p_iIndex)
	{
		if(NeedConstructor){Destruct(p_iIndex,1);};
		if(p_iIndex<m_iCount-1)
		{
			MoveElements(p_iIndex,p_iIndex+1,m_iCount-p_iIndex-1);
		};
		ReallocMemory(m_iCount-1);
		m_iCount--;
	};

	bool Exists(TElemType p_elemType)
	{
		int i,iC=m_iCount;
		for(i=0;i<iC;i++)
		{
			if(m_pxE[i]==p_elemType)
			{
				return true;
			}
		}
		return false;
	}

	TElemType& Back()
	{
		return m_pxE[m_iCount-1];
	}

	TElemType& Front()
	{
		return m_pxE[0];
	}

	int Add(const TElemType& p_xE)
	{
		SetSize(m_iCount+1);
		m_pxE[m_iCount-1]=p_xE;
		return m_iCount-1;
	};

	TElemType& NewRef()
	{
		SetSize(m_iCount+1);
		return m_pxE[m_iCount-1];
	};

	int GetSize() const
	{
		return m_iCount;
	};

	TElemType& operator[](int p_iIndex)
	{
		return m_pxE[p_iIndex];
	};

	const TElemType& operator[](int p_iIndex) const
	{
		return m_pxE[p_iIndex];
	};

	void QSortSub(int p_iLoP,int p_iHiP)
	{
		if(p_iLoP>=p_iHiP){return;};
		int iLo=p_iLoP,iHi=p_iHiP;
		if(iLo==iHi-1)
		{
			if(m_pxE[(iLo)]>m_pxE[(iHi)]){Swap(m_pxE[(iLo)],m_pxE[(iHi)]);};
			return;
		};
		TElemType xPivot=m_pxE[((iLo+iHi)/2)];
		m_pxE[((iLo+iHi)/2)]=m_pxE[(iHi)];m_pxE[(iHi)]=xPivot;
		while(iLo<iHi) 
		{
			while((!(m_pxE[(iLo)]>xPivot))&&(iLo<iHi)){++iLo;};
			while((!(xPivot>m_pxE[(iHi)]))&&(iLo<iHi)){--iHi;};
			if (iLo<iHi){Swap(m_pxE[(iLo)],m_pxE[(iHi)]);};
		};
		m_pxE[(p_iHiP)]=m_pxE[(iHi)];m_pxE[(iHi)]=xPivot;
		QSortSub(p_iLoP,iLo-1);QSortSub(iHi+1,p_iHiP);
	};

	void Sort()
	{
		int i,iC=GetSize();
		if(iC<2){return;};
		if(iC>20)
		{
			QSortSub(0,iC-1);
		}
		else
		{
			bool bDone=false;
			while(!bDone)
			{
				bDone=true;
				for(i=0;i<iC-1;i++)
				{
					if(m_pxE[i]>m_pxE[i+1])
					{
						Swap(m_pxE[i],m_pxE[i+1]);
						bDone=false;
					};
				};
			};
		};
	};

	void Clear(){SetSize(0);}
	bool Empty(){return m_iCount==0;}

protected:
	TElemType* m_pxE;
	int m_iCount;

	void Construct(int p_iStart,int p_iCount)
	{
		int i;
		for(i=p_iStart;i<p_iStart+p_iCount;i++)
		{
			new (&(m_pxE[i])) TElemType();
		};
	};
	void Destruct(int p_iStart,int p_iCount)
	{
		int i;
		for(i=p_iStart;i<p_iStart+p_iCount;i++)
		{
			m_pxE[i].~TElemType();
		};
	};
	void ReallocMemory(int p_iTotalCount)
	{
		if(m_iCount==p_iTotalCount){return;};
		if(p_iTotalCount==0)
		{
			free(m_pxE);
			m_pxE=NULL;
		}
		else
		{
			int iRealNewCnt=(p_iTotalCount+dwGranMask)&(~dwGranMask);
			int iRealHaveCnt=(m_iCount+dwGranMask)&(~dwGranMask);
			if(iRealHaveCnt!=iRealNewCnt)
			{
				m_pxE=(TElemType*)realloc(m_pxE,iRealNewCnt*sizeof(TElemType));
			};
		};
	};
	void MoveElements(int p_iDstIndex,int p_iSrcIndex,int p_iCount)
	{
		if((p_iDstIndex!=p_iSrcIndex)&&(p_iCount>0))
		{
			SDL_memmove(&(m_pxE[p_iDstIndex]),&(m_pxE[p_iSrcIndex]),sizeof(TElemType)*p_iCount);
		};
	};

};

}; // namespace neko
