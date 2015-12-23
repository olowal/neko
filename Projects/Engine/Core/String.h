/****************************************************************************
//	Filename: String.h
//	Description: String class for managing text etc
*****************************************************************************/
#pragma once
#include "Engine/Common/Common.h"

namespace neko
{

template <typename StrType>
class IString
{
public:
	IString():
	m_pzString(NULL),
	m_uLength(0){}
	IString(const StrType& pzStr){}
	IString(const StrType* szStr);
	~IString() { Clear(); }

	void Clear()
	{
		if(m_pzString != NULL)
		{
			free(m_pzString);
			m_pzString = NULL;
			m_uLength = 0;
		}
	}

	void Set(const IString sStr){ Set(sStr.m_pzString); }
	void Set(const StrType* pzStr);
	void Append(const StrType* pzStr);

	uint32 Length() const { return m_uLength; }
	bool Empty() const { return m_uLength == 0; }
	const StrType* CStr() const { return m_pzString; }

	StrType* Alloc(uint32 uNumChars)
	{
		Clear();
		m_pzString = (StrType*)malloc(sizeof(StrType) * uNumChars);
		return m_pzString;
	}

	bool Equals(const char* szString) const;

	bool operator == (const IString& sStr) const { return Compare(sStr) == 0; }
	bool operator != (const IString& sStr) const { return Compare(sStr) != 0; }
	bool operator >= (const IString& sStr) const { return Compare(sStr) >= 0; }
	bool operator <= (const IString& sStr) const { return Compare(sStr) <= 0; }
	bool operator > (const IString& sStr) const { return Compare(sStr) > 0; }
	bool operator < (const IString& sStr) const { return Compare(sStr) < 0; }

	IString& operator += (const IString& sStr) { Append(sStr.CStr()); return *this; }

private:
	int _Cmp(const StrType* pzString) const;
	int Compare(const IString& sStr) const
	{
		if(m_pzString == NULL && sStr.m_pzString == NULL) { return 0; }
		else if(m_pzString != NULL && sStr.m_pzString == NULL) { return 1; }
		else if(m_pzString == NULL && sStr.m_pzString != NULL) { return -1; }
		return _Cmp(sStr.m_pzString);
	}

	StrType* m_pzString;
	uint32 m_uLength;
};

typedef IString<char> U8String;
typedef IString<wchar_t> WString;
typedef U8String String;

}	//	namespace neko